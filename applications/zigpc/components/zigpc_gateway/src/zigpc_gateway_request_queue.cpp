/******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 ******************************************************************************
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 *****************************************************************************/

#include <algorithm>
#include <cinttypes>
#include <iterator>
#include <memory>
#include <queue>
#include <string>

// Shared Unify includes
#include "../inc/sl_status.h"
#include <sl_log.h>


// Component includes
#include "zigpc_gateway.h"
#include "zigpc_gateway_int.h"
#include "zigpc_gateway_request_queue.hpp"

#define LOG_PREFIX_GATEWAY          "Gateway "
#define LOG_PREFIX_EUI64            "Eui64:%016" PRIX64 " "
#define LOG_PREFIX_EUI64_EP         "Eui64:%016" PRIX64 ",Ep:%u "
#define LOG_PREFIX_EUI64_EP_CLUSTER "Eui64:%016" PRIX64 ",Ep:%u,Cluster:0x%04X "
#define LOG_PREFIX_GROUP_CLUSTER    "Group:0x%04X,Cluster:0x%04X "

namespace zigpc::gateway
{
RequestQueue::Entry::Entry(const char *label) : label(label) {}

size_t RequestQueue::Entry::getSendAttempts(void) const
{
  return send_attempts;
}

void RequestQueue::Entry::incrementSendAttempt()
{
  this->send_attempts++;
}

const char *RequestQueue::Entry::getLabel(void) const
{
  return label;
}

RequestQueue::RequestQueue() {}

RequestQueue &RequestQueue::getInstance(void)
{
  static RequestQueue instance;
  return instance;
}
void RequestQueue::stopDispatching()
{
  this->dispatching_allowed = false;
  sl_log_info(LOG_TAG, "RequestQueue dispatching suspended");
}
void RequestQueue::startDispatching()
{
  sl_log_info(LOG_TAG, "RequestQueue dispatching resumed");
  this->dispatching_allowed = true;
  this->defer_cycles        = DEFER_CYCLES_START_BACKOFF;
}

void RequestQueue::enqueue(std::shared_ptr<Entry> call)
{
  this->queue.push(call);
}

sl_status_t RequestQueue::dispatch(void)
{
  sl_status_t status = SL_STATUS_OK;

  if (this->queue.empty()) {
    status = SL_STATUS_EMPTY;
  } else if (this->defer_cycles > 0) {
    // Skip sending any messages, only call tick loop
    this->defer_cycles--;
  } else if (this->dispatching_allowed == true) {
    const std::shared_ptr<Entry> &call = this->queue.front();
    sl_log_debug(LOG_TAG, "Request[%s] dequeued", call->getLabel());

    // Increase attempt count
    call->incrementSendAttempt();

    sl_status_t ember_status = call->invoke();

    sl_log_level_t log_level = sl_log_level_t::SL_LOG_DEBUG;
    if (ember_status == SL_STATUS_ZIGBEE_MAX_MESSAGE_LIMIT_REACHED) {
      // Handle case of too many in-flight messages
      log_level = sl_log_level_t::SL_LOG_WARNING;
      status    = SL_STATUS_TRANSMIT_BUSY;

      // Do not send any messages for a few cycles
      this->defer_cycles += DEFER_CYCLES_MESSAGE_LIMIT_REACHED;

    } else if (ember_status == SL_STATUS_OK) {
      log_level = sl_log_level_t::SL_LOG_INFO;
      status    = SL_STATUS_OK;
      this->defer_cycles += DEFER_CYCLES_DEFAULT;

    } else if ((ember_status == SL_STATUS_NETWORK_DOWN)
               || (ember_status == SL_ZIGBEE_EZSP_NOT_CONNECTED)
               || (ember_status == SL_ZIGBEE_EZSP_ERROR_VERSION_NOT_SET)) {
      // Do not send any messages for some cycles to see if an NCP reset is pending
      this->defer_cycles = DEFER_CYCLES_LOST_CONNECTION;
      log_level          = sl_log_level_t::SL_LOG_WARNING;
      status             = SL_STATUS_TRANSMIT_BUSY;

    } else {
      log_level = sl_log_level_t::SL_LOG_ERROR;
      status    = SL_STATUS_FAIL;
    }

    sl_log(LOG_TAG,
           log_level,
           "Request[%s] dispatch attempt[%u] status: 0x%X",
           call->getLabel(),
           call->getSendAttempts(),
           status);

    // Remove call if there was no problem sending it
    if (status != SL_STATUS_TRANSMIT_BUSY) {
      this->queue.pop();
    }
  }
  // Request EmberAf Tick loop even if there is no call to dispatch
  zigbeeHostTick();

  return status;
}

NetworkInitRequest::NetworkInitRequest(void) :
  RequestQueue::Entry("Network Init")
{}

sl_status_t NetworkInitRequest::invoke(void)
{
  

  const zigpc_config_t* config = zigpc_get_config();

  bool use_network_args = config->use_network_args;
  sl_status_t status = SL_STATUS_FAIL;

  if(use_network_args)
  {

    const zigpc_config_t *config = zigpc_get_config();

    status = zigbeeHostTrustCenterInitWithArgs(
            config->network_pan_id,
            config->network_radio_power,
            config->network_channel);
  }
  else
  {
    status = zigbeeHostTrustCenterInit();
  }

  sl_log(LOG_TAG,
         (status == SL_STATUS_OK) ? SL_LOG_INFO : SL_LOG_ERROR,
         LOG_PREFIX_GATEWAY "Network Init sl_zigbee_af_status_t: 0x%X",
         status);

  return status;
}

DiscoverDeviceRequest::DiscoverDeviceRequest(const zigbee_eui64_t eui64) :
  RequestQueue::Entry("Device Interview")
{
  std::copy(eui64, eui64 + sizeof(zigbee_eui64_t), this->eui64);
}

sl_status_t DiscoverDeviceRequest::invoke(void)
{
  zigbee_eui64_t eui64_le;
  zigbee_eui64_copy_switch_endian(eui64_le, this->eui64);
  sl_status_t status = zigbeeHostZdoActiveEndpointsRequest(eui64_le);

  sl_log(LOG_TAG,
         (status == SL_STATUS_OK) ? SL_LOG_INFO : SL_LOG_ERROR,
         LOG_PREFIX_EUI64 "Interview sl_zigbee_af_status_t: 0x%X",
         zigbee_eui64_to_uint(this->eui64),
         status);
  return status;
}

DiscoverEndpointRequest::DiscoverEndpointRequest(
  const zigbee_eui64_t eui64, zigbee_endpoint_id_t endpoint_id) :
  RequestQueue::Entry("Endpoint Discover"), endpoint_id(endpoint_id)
{
  std::copy(eui64, eui64 + sizeof(zigbee_eui64_t), this->eui64);
}

sl_status_t DiscoverEndpointRequest::invoke(void)
{
  zigbee_eui64_t eui64_le;
  zigbee_eui64_copy_switch_endian(eui64_le, this->eui64);
  sl_status_t status
    = zigbeeHostZdoSimpleDescriptorRequest(eui64_le, endpoint_id);

  sl_log(LOG_TAG,
         (status == SL_STATUS_OK) ? SL_LOG_INFO : SL_LOG_ERROR,
         LOG_PREFIX_EUI64_EP " Discover sl_zigbee_af_status_t: 0x%X",
         zigbee_eui64_to_uint(this->eui64),
         status);
  return status;
}

DeviceRemoveRequest::DeviceRemoveRequest(const zigbee_eui64_t eui64) :
  RequestQueue::Entry("Device Remove")
{
  std::copy(eui64, eui64 + sizeof(zigbee_eui64_t), this->eui64);
}

sl_status_t DeviceRemoveRequest::invoke(void)
{
  zigbee_eui64_t eui64_le;
  zigbee_eui64_copy_switch_endian(eui64_le, this->eui64);
  sl_status_t status = zigbeeHostNetworkDeviceLeaveRequest(eui64_le);

  sl_log(LOG_TAG,
         (status == SL_STATUS_OK) ? SL_LOG_INFO : SL_LOG_ERROR,
         LOG_PREFIX_EUI64 "Remove sl_zigbee_af_status_t: 0x%X",
         zigbee_eui64_to_uint(this->eui64),
         status);

  return status;
}

BindingRequestRequest::BindingRequestRequest(const zigbee_eui64_t source_eui64,
                                             zigbee_endpoint_id_t source_endpoint_id,
                                             zcl_cluster_id_t cluster_id,
                                             const zigbee_eui64_t dest_eui64,
                                             zigbee_endpoint_id_t dest_endpoint_id,
                                             bool is_binding_req) :
  RequestQueue::Entry("Binding Request"),
  source_endpoint_id(source_endpoint_id),
  cluster_id(cluster_id),
  dest_endpoint_id(dest_endpoint_id),
  is_binding_req(is_binding_req)
{
  std::copy(source_eui64, source_eui64 + sizeof(zigbee_eui64_t), this->source_eui64);
  std::copy(dest_eui64, dest_eui64 + sizeof(zigbee_eui64_t), this->dest_eui64);
}

sl_status_t BindingRequestRequest::invoke(void)
{
  zigbee_eui64_t source_eui64_le;
  zigbee_eui64_copy_switch_endian(source_eui64_le, this->source_eui64);
  
  zigbee_eui64_t dest_eui64_le;
  zigbee_eui64_copy_switch_endian(dest_eui64_le, this->dest_eui64);
  
  sl_status_t status
    = zigbeeHostInitBinding(source_eui64_le,
                            this->source_endpoint_id,
                            this->cluster_id,
                            0,
                            dest_eui64_le,
                            this->dest_endpoint_id,
                            this->is_binding_req);  //only unicast bindings for now

  sl_log(LOG_TAG,
         (status == SL_STATUS_OK) ? SL_LOG_INFO : SL_LOG_ERROR,
         LOG_PREFIX_EUI64_EP_CLUSTER "Binding Request " LOG_PREFIX_EUI64_EP "sl_zigbee_af_status_t: 0x%X",
         zigbee_eui64_to_uint(this->source_eui64),
         this->source_endpoint_id,
         this->cluster_id,
         zigbee_eui64_to_uint(this->dest_eui64),
         this->dest_endpoint_id,
         status);
  return status;
}

ZCLConfigureReportingRequest::ZCLConfigureReportingRequest(
  const zigbee_eui64_t eui64,
  zigbee_endpoint_id_t endpoint_id,
  zcl_cluster_id_t cluster_id,
  const uint8_t *report_record,
  unsigned int report_size) :
  RequestQueue::Entry("ZCL Configure Reporting"),
  endpoint_id(endpoint_id),
  cluster_id(cluster_id)
{
  std::copy(eui64, eui64 + sizeof(zigbee_eui64_t), this->eui64);

  // Copy report record into ZCL frame data
  this->frame.size = report_size;
  std::copy(report_record,
            report_record + this->frame.size,
            this->frame.buffer);
}

sl_status_t ZCLConfigureReportingRequest::invoke(void)
{
  zigbee_eui64_t eui64_le;
  zigbee_eui64_copy_switch_endian(eui64_le, this->eui64);

  unsigned int report_size = static_cast<unsigned int>(this->frame.size);
  sl_status_t status       = zigbeeHostInitReporting(eui64_le,
                                               this->endpoint_id,
                                               this->cluster_id,
                                               this->frame.buffer,
                                               report_size);

  sl_log(LOG_TAG,
         (status == SL_STATUS_OK) ? SL_LOG_INFO : SL_LOG_ERROR,
         LOG_PREFIX_EUI64_EP_CLUSTER
         "ZCL Configure Reporting sl_zigbee_af_status_t: 0x%X",
         zigbee_eui64_to_uint(this->eui64),
         this->endpoint_id,
         this->cluster_id,
         status);

  return status;
}

ZCLFrameUnicastRequest::ZCLFrameUnicastRequest(const zigbee_eui64_t eui64,
                                               zigbee_endpoint_id_t endpoint_id,
                                               zcl_cluster_id_t cluster_id,
                                               const zcl_frame_t &frame) :

  RequestQueue::Entry("ZCL Frame Unicast"),
  endpoint_id(endpoint_id),
  cluster_id(cluster_id),
  frame(frame)
{
  std::copy(eui64, eui64 + sizeof(zigbee_eui64_t), this->eui64);
}

sl_status_t ZCLFrameUnicastRequest::invoke(void)
{
  zigbee_eui64_t eui64_le;
  zigbee_eui64_copy_switch_endian(eui64_le, this->eui64);
  sl_status_t status = zigbeeHostFillZclFrame(this->frame.buffer,
                                              this->frame.size,
                                              this->frame.offset_sequence_id);

  if (status == SL_STATUS_OK) {
    status = zigbeeHostSendZclFrameUnicast(eui64_le,
                                           this->endpoint_id,
                                           this->cluster_id);

    sl_log(LOG_TAG,
           (status == SL_STATUS_OK) ? SL_LOG_INFO : SL_LOG_WARNING,
           LOG_PREFIX_EUI64_EP_CLUSTER "ZCL frame send sl_zigbee_af_status_t: 0x%X",
           zigbee_eui64_to_uint(this->eui64),
           this->endpoint_id,
           this->cluster_id,
           status);
  } else {
    sl_log_error(LOG_TAG,
                 "Failed to fill ZCL frame to send unicast sl_zigbee_af_status_t: 0x%X",
                 status);
  }

  return status;
}

ZCLFrameMulticastRequest::ZCLFrameMulticastRequest(zigbee_group_id_t group_id,
                                                   zcl_cluster_id_t cluster_id,
                                                   const zcl_frame_t &frame) :
  RequestQueue::Entry("ZCL Frame Multicast"),
  group_id(group_id),
  cluster_id(cluster_id),
  frame(frame)
{}

sl_status_t ZCLFrameMulticastRequest::invoke(void)
{
  sl_status_t status = zigbeeHostFillZclFrame(this->frame.buffer,
                                              this->frame.size,
                                              this->frame.offset_sequence_id);

  if (status == SL_STATUS_OK) {
    status = zigbeeHostSendZclFrameMulticast(this->group_id, this->cluster_id);

    sl_log(LOG_TAG,
           (status == SL_STATUS_OK) ? SL_LOG_INFO : SL_LOG_WARNING,
           LOG_PREFIX_GROUP_CLUSTER "ZCL frame send sl_zigbee_af_status_t: 0x%X",
           this->group_id,
           this->cluster_id,
           status);
  } else {
    sl_log_error(
      LOG_TAG,
      "Failed to fill ZCL frame to send as multicast sl_zigbee_af_status_t: 0x%X",
      status);
  }

  return status;
}

AddOTAImageRequest::AddOTAImageRequest(std::string &filename) :
  RequestQueue::Entry("Add OTA Image"), filename(filename)
{}

sl_status_t AddOTAImageRequest::invoke(void)
{
  sl_status_t status = zigbeeHostAddOtaImage(this->filename.c_str());

  sl_log(LOG_TAG,
         (status == SL_STATUS_OK) ? SL_LOG_INFO : SL_LOG_ERROR,
         LOG_PREFIX_GATEWAY "Add OTA Image [%s] sl_zigbee_af_status_t: 0x%X",
         this->filename.c_str(),
         status);

  return status;
}

}  // namespace zigpc::gateway
