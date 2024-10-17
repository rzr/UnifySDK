/***************************************************************************//**
 * @file sl_cli_command_table.c
 * @brief Declarations of relevant command structs for cli framework.
 * @version x.y.z
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include <stdlib.h>

#include "sl_cli_config.h"
#include "sl_cli_command.h"
#include "sl_cli_arguments.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *****************************   TEMPLATED FILE   ******************************
 ******************************************************************************/

/*******************************************************************************
 * Example syntax (.slcc or .slcp) for populating this file:
 *
 *   template_contribution:
 *     - name: cli_command          # Register a command
 *       value:
 *         name: status             # Name of command
 *         handler: status_command  # Function to be called. Must be defined
 *         help: "Prints status"    # Optional help description
 *         shortcuts:               # Optional shorcut list
 *           - name: st
 *         argument:                # Argument list, if apliccable
 *           - type: uint8          # Variable type
 *             help: "Channel"      # Optional description
 *           - type: string
 *             help: "Text"
 *     - name: cli_group            # Register a group
 *       value:
 *         name: shell              # Group name
 *         help: "Shell commands"   # Optional help description
 *         shortcuts:               # Optional shorcuts
 *           - name: sh
 *     - name: cli_command
 *       value:
 *         name: repeat
 *         handler: repeat_cmd
 *         help: "Repeat commands"
 *         shortcuts:
 *           - name: r
 *           - name: rep
 *         group: shell            # Associate command with group
 *         argument:
 *           - type: string
 *             help: "Text"
 *           - type: additional
 *             help: "More text"
 *
 * For subgroups, an optional unique id can be used to allow a particular name to
 * be used more than once. In the following case, from the command line the
 * following commands are available:
 *
 * >  root_1 shell status
 * >  root_2 shell status
 *
 *     - name: cli_group            # Register a group
 *       value:
 *         name: root_1             # Group name
 *
 *     - name: cli_group            # Register a group
 *       value:
 *         name: root_2             # Group name
 *
 *    - name: cli_group             # Register a group
 *       value:
 *         name: shell              # Group name
 *         id: shell_root_1         # Optional unique id for group
 *         group: root_1            # Add group to root_1 group
 *
 *    - name: cli_group             # Register a group
 *       value:
 *         name: shell              # Group name
 *         id: shell_root_2         # Optional unique id for group
 *         group: root_2            # Add group to root_1 group
 *
 *    - name: cli_command           # Register a command
 *       value:
 *         name: status
 *         handler: status_1
 *         group: shell_root_1      # id of subgroup
 *
 *    - name: cli_command           # Register a command
 *       value:
 *         name: status
 *         handler: status_2
 *         group: shell_root_2      # id of subgroup
 *
 ******************************************************************************/

// Provide function declarations
void sl_zigbee_af_address_table_add_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_address_table_set_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_address_table_remove_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_address_table_lookup_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_address_table_print_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_concentrator_status(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_concentrator_start_discovery_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_concentrator_stop_discovery_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_concentrator_aggregation_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_concentrator_print_source_route_table(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_concentrator_set_router_behavior_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_counters_print_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_counters_print_counters_type_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_counters_simple_print_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_counters_clear(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_counters_print_thresholds_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_counters_set_threshold_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_counters_reset_thresholds(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_counters_send_request_command(sl_cli_command_arg_t *arguments);
void sli_zigbee_debug_print_enable_stack_type_command(sl_cli_command_arg_t *arguments);
void sli_zigbee_debug_print_enable_core_type_command(sl_cli_command_arg_t *arguments);
void sli_zigbee_debug_print_enable_app_type_command(sl_cli_command_arg_t *arguments);
void sli_zigbee_debug_print_enable_zcl_type_command(sl_cli_command_arg_t *arguments);
void sli_zigbee_debug_print_enable_legacy_af_debug_type_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_gateway_support_time_sync_local(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_network_creator_start_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_network_creator_stop(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_network_creator_form_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_network_creator_channel_mask_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_network_creator_channel_mask_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_network_creator_channel_mask_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_network_creator_status_command(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_network_creator_security_set_joining_link_key_command(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_network_creator_security_clear_joining_link_key_command(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_network_creator_security_open_or_close_network_command(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_network_creator_security_open_or_close_network_command(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_network_creator_security_open_network_with_key_command(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_network_creator_security_configure_distributed_key(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_network_steering_status_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_network_steering_start_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_network_steering_stop_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_network_steering_set_preconfigured_key_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_network_steering_channel_set_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_network_steering_channel_add_or_subtract_command(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_network_steering_channel_add_or_subtract_command(sl_cli_command_arg_t *arguments);
void otaImageNotifyCommand(sl_cli_command_arg_t *arguments);
void otaSendUpgradeCommand(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_ota_server_policy_print(sl_cli_command_arg_t *arguments);
void setPolicy(sl_cli_command_arg_t *arguments);
void setPolicy(sl_cli_command_arg_t *arguments);
void setPolicy(sl_cli_command_arg_t *arguments);
void setPolicy(sl_cli_command_arg_t *arguments);
void setPolicy(sl_cli_command_arg_t *arguments);
void setPolicy(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_ota_print_all_images(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_ota_image_delete(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_ota_reload_storage_device(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_ota_storage_info_print(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_ota_storage_data_print(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_reporting_cli_print(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_reporting_cli_clear(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_reporting_cli_remove(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_reporting_cli_add(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_reporting_cli_clear_last_report_time(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_reporting_cli_test_timing(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_set_t_c_link_key_update_timer_command(sl_cli_command_arg_t *arguments);
void networkFormCommand(sl_cli_command_arg_t *arguments);
void networkJoinCommand(sl_cli_command_arg_t *arguments);
void networkPermitJoinCommand(sl_cli_command_arg_t *arguments);
void networkLeaveCommand(sl_cli_command_arg_t *arguments);
void networkRejoinCommand(sl_cli_command_arg_t *arguments);
void networkRejoinDiffDeviceTypeCommand(sl_cli_command_arg_t *arguments);
void networkExtendedPanIdCommand(sl_cli_command_arg_t *arguments);
void networkCheckPjoinCommand(sl_cli_command_arg_t *arguments);
void networkPermitJoinCommand(sl_cli_command_arg_t *arguments);
void findJoinableNetworkCommand(sl_cli_command_arg_t *arguments);
void findUnusedPanIdCommand(sl_cli_command_arg_t *arguments);
void networkChangeChannelCommand(sl_cli_command_arg_t *arguments);
void networkSetCommand(sl_cli_command_arg_t *arguments);
void networkInitCommand(sl_cli_command_arg_t *arguments);
void networkIdCommand(sl_cli_command_arg_t *arguments);
void changeKeepAliveModeCommand(sl_cli_command_arg_t *arguments);
void networkChangeChildTimeoutOptionMaskCommand(sl_cli_command_arg_t *arguments);
void networkMultiPhyStartCommand(sl_cli_command_arg_t *arguments);
void networkMultiPhyStopCommand(sl_cli_command_arg_t *arguments);
void keysPrintCommand(sl_cli_command_arg_t *arguments);
void keysDeleteCommand(sl_cli_command_arg_t *arguments);
void keysClearCommand(sl_cli_command_arg_t *arguments);
void optionBindingTablePrintCommand(sl_cli_command_arg_t *arguments);
void optionBindingTableClearCommand(sl_cli_command_arg_t *arguments);
void optionBindingTableSetCommand(sl_cli_command_arg_t *arguments);
void optionPrintRxCommand(sl_cli_command_arg_t *arguments);
void optionPrintRxCommand(sl_cli_command_arg_t *arguments);
void optionRegisterCommand(sl_cli_command_arg_t *arguments);
void optionDiscoveryTargetCommand(sl_cli_command_arg_t *arguments);
void optionDiscoverCommand(sl_cli_command_arg_t *arguments);
void optionApsRetryCommand(sl_cli_command_arg_t *arguments);
void optionApsRetryCommand(sl_cli_command_arg_t *arguments);
void optionApsRetryCommand(sl_cli_command_arg_t *arguments);
void optionApsSecurityCommand(sl_cli_command_arg_t *arguments);
void optionApsSecurityCommand(sl_cli_command_arg_t *arguments);
void optionSecurityAllowTrustCenterRejoinUsingWellKnownKey(sl_cli_command_arg_t *arguments);
void optionSecurityAllowTrustCenterRejoinUsingWellKnownKeyTimeout(sl_cli_command_arg_t *arguments);
void optionSecuritySetKeyRequestPolicy(sl_cli_command_arg_t *arguments);
void changeKeyCommand(sl_cli_command_arg_t *arguments);
void changeKeyCommand(sl_cli_command_arg_t *arguments);
void optionLinkCommand(sl_cli_command_arg_t *arguments);
void optionInstallCodeCommand(sl_cli_command_arg_t *arguments);
void zdoRouteRequestCommand(sl_cli_command_arg_t *arguments);
void zdoPowerDescriptorRequestCommand(sl_cli_command_arg_t *arguments);
void zdoMgmtLqiCommand(sl_cli_command_arg_t *arguments);
void zdoMgmtBindCommand(sl_cli_command_arg_t *arguments);
void zdoLeaveRequestCommand(sl_cli_command_arg_t *arguments);
void zdoUnbindGroupCommand(sl_cli_command_arg_t *arguments);
void zdoUnbindUnicastCommand(sl_cli_command_arg_t *arguments);
void zdoActiveEpCommand(sl_cli_command_arg_t *arguments);
void zdoBindCommand(sl_cli_command_arg_t *arguments);
void zdoNodeCommand(sl_cli_command_arg_t *arguments);
void zdoMatchCommand(sl_cli_command_arg_t *arguments);
void zdoSimpleCommand(sl_cli_command_arg_t *arguments);
void zdoIeeeAddressRequestCommand(sl_cli_command_arg_t *arguments);
void zdoNwkAddressRequestCommand(sl_cli_command_arg_t *arguments);
void zdoNetworkUpdateScanCommand(sl_cli_command_arg_t *arguments);
void zdoNetworkUpdateSetCommand(sl_cli_command_arg_t *arguments);
void zdoNetworkUpdateScanCommand(sl_cli_command_arg_t *arguments);
void zdoNetworkUpdateChannelCommand(sl_cli_command_arg_t *arguments);
void zdoNetworkUpdateChannelCommand(sl_cli_command_arg_t *arguments);
void zdoAddClusterCommand(sl_cli_command_arg_t *arguments);
void zdoClearClusterCommand(sl_cli_command_arg_t *arguments);
void zdoAddClusterCommand(sl_cli_command_arg_t *arguments);
void zdoClearClusterCommand(sl_cli_command_arg_t *arguments);
void sl_zigbee_af_print_attribute_table(sl_cli_command_arg_t *arguments);
void printTimeCommand(sl_cli_command_arg_t *arguments);

// Command structs. Names are in the format : cli_cmd_{command group name}_{command name}
// In order to support hyphen in command and group name, every occurence of it while
// building struct names will be replaced by "_hyphen_"
static const sl_cli_command_info_t cli_cmd_address_hyphen_table_add = \
  SL_CLI_COMMAND(sl_zigbee_af_address_table_add_command,
                 "",
                  "Entry to be added" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_HEX, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_address_hyphen_table_set = \
  SL_CLI_COMMAND(sl_zigbee_af_address_table_set_command,
                 "Sets an entry in the address table according to the arguments specified.",
                  "" SL_CLI_UNIT_SEPARATOR "" SL_CLI_UNIT_SEPARATOR "" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_HEX, SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_address_hyphen_table_remove = \
  SL_CLI_COMMAND(sl_zigbee_af_address_table_remove_command,
                 "Removes an entry from the address table.",
                  "Entry to be removed" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_HEX, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_address_hyphen_table_lookup = \
  SL_CLI_COMMAND(sl_zigbee_af_address_table_lookup_command,
                 "Looks up an entry in the address table.",
                  "Entry to be looked up" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_HEX, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_address_hyphen_table_print = \
  SL_CLI_COMMAND(sl_zigbee_af_address_table_print_command,
                 "Prints the address table.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_concentrator_status = \
  SL_CLI_COMMAND(sl_zigbee_af_concentrator_status,
                 "Prints current status and configured parameters of the concentrator.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_concentrator_start = \
  SL_CLI_COMMAND(sl_zigbee_af_concentrator_start_discovery_command,
                 "Starts the periodic broadcast of MTORRs.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_concentrator_stop = \
  SL_CLI_COMMAND(sl_zigbee_af_concentrator_stop_discovery_command,
                 "Stops the periodic broadcast of MTORRs.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_concentrator_agg = \
  SL_CLI_COMMAND(sl_zigbee_af_concentrator_aggregation_command,
                 "(Requires Concentrator Support to be enabled on this device.) Schedules a Zigbee PRO Many-To-One Route Request (MTORR) to be sent out at the next opportunity, which will cause aggregation (many-to-one) routes to be created towards this concentrator.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_concentrator_print_hyphen_table = \
  SL_CLI_COMMAND(sl_zigbee_af_concentrator_print_source_route_table,
                 "Prints the SoC/NCP source route table.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_concentrator_set_hyphen_router_hyphen_behavior = \
  SL_CLI_COMMAND(sl_zigbee_af_concentrator_set_router_behavior_command,
                 "This command allows the user to set the router behavior for this component. The argument values come from concentrator-support.h in the enum with members starting with EMBER_AF_PLUGIN_CONCENTRATOR_ROUTER_BEHAVIOR_.",
                  "The value of an EMBER_AF_PLUGIN_CONCENTRATOR_ROUTER_BEHAVIOR_ enum member" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_counters_print = \
  SL_CLI_COMMAND(sl_zigbee_af_counters_print_command,
                 "Prints all counter values and clears them.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_counters_print_hyphen_counter_hyphen_type = \
  SL_CLI_COMMAND(sl_zigbee_af_counters_print_counters_type_command,
                 "Prints the value of this particular counter.",
                  "The counter type to print" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_counters_simple_hyphen_print = \
  SL_CLI_COMMAND(sl_zigbee_af_counters_simple_print_command,
                 "Prints all counter values.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_counters_clear = \
  SL_CLI_COMMAND(sl_zigbee_af_counters_clear,
                 "Clears all counter values.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_counters_print_hyphen_thresholds = \
  SL_CLI_COMMAND(sl_zigbee_af_counters_print_thresholds_command,
                 "Prints the thresholds of all the counters.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_counters_set_hyphen_threshold = \
  SL_CLI_COMMAND(sl_zigbee_af_counters_set_threshold_command,
                 "Sets a threshold value for a particular type of counter.",
                  "Type of counter" SL_CLI_UNIT_SEPARATOR "Threshold Value" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_counters_reset_hyphen_thresholds = \
  SL_CLI_COMMAND(sl_zigbee_af_counters_reset_thresholds,
                 "Resets all thresholds values to 0xFFFF.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_counters_send_hyphen_request = \
  SL_CLI_COMMAND(sl_zigbee_af_counters_send_request_command,
                 "Sends a request for OTA counters.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_enable_type_stack = \
  SL_CLI_COMMAND(sli_zigbee_debug_print_enable_stack_type_command,
                 "Enable/disable debug `stack` print type.",
                  "Enable/disable" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_enable_type_core = \
  SL_CLI_COMMAND(sli_zigbee_debug_print_enable_core_type_command,
                 "Enable/disable debug `core` print type.",
                  "Enable/disable" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_enable_type_app = \
  SL_CLI_COMMAND(sli_zigbee_debug_print_enable_app_type_command,
                 "Enable/disable debug `app` print type.",
                  "Enable/disable" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_enable_type_zcl = \
  SL_CLI_COMMAND(sli_zigbee_debug_print_enable_zcl_type_command,
                 "Enable/disable debug `zcl` print type.",
                  "Enable/disable" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_enable_type_legacy_af_debug = \
  SL_CLI_COMMAND(sli_zigbee_debug_print_enable_legacy_af_debug_type_command,
                 "Enable/disable debug `legacy app framework debug` print type.",
                  "Enable/disable" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_gateway_time_hyphen_sync_hyphen_local = \
  SL_CLI_COMMAND(sl_zigbee_af_gateway_support_time_sync_local,
                 "",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_hyphen_creator_start = \
  SL_CLI_COMMAND(sl_zigbee_af_network_creator_start_command,
                 "Starts the network formation process.",
                  "Whether or not to form a centralized network. If this value is false, the device will attempt to join a distributed network." SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_INT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_hyphen_creator_stop = \
  SL_CLI_COMMAND(sl_zigbee_af_network_creator_stop,
                 "Stops the network formation process.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_hyphen_creator_form = \
  SL_CLI_COMMAND(sl_zigbee_af_network_creator_form_command,
                 "Forms a network with specified parameters.",
                  "Whether or not to form a centralized network. If this value is false, the device will attempt to join a distributed network." SL_CLI_UNIT_SEPARATOR "PanID of the network to be formed" SL_CLI_UNIT_SEPARATOR "Tx power of the network to be formed" SL_CLI_UNIT_SEPARATOR "Channel of the network to be formed" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_INT8, SL_CLI_ARG_UINT16, SL_CLI_ARG_INT8, SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_mask_add = \
  SL_CLI_COMMAND(sl_zigbee_af_network_creator_channel_mask_command,
                 "Adds a channel to the channel mask of choice.",
                  "The mask to which to add the channel. 1 chooses the primary channel mask, any other argument chooses the secondary channel mask." SL_CLI_UNIT_SEPARATOR "The channel to add to the channel mask" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT32, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_mask_subtract = \
  SL_CLI_COMMAND(sl_zigbee_af_network_creator_channel_mask_command,
                 "Subtracts a channel from the channel mask of choice.",
                  "The mask from which to subtract the channel. 1 chooses the primary channel mask. Any other argument chooses the secondary channel mask." SL_CLI_UNIT_SEPARATOR "The channel to subtract from the channel mask" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT32, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_mask_set = \
  SL_CLI_COMMAND(sl_zigbee_af_network_creator_channel_mask_command,
                 "Sets a channel mask.",
                  "The mask  to set. 1 chooses the primary channel mask. Any other argument chooses the secondary channel mask." SL_CLI_UNIT_SEPARATOR "The bit mask to which to set the chosen channel mask." SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT32, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_hyphen_creator_status = \
  SL_CLI_COMMAND(sl_zigbee_af_network_creator_status_command,
                 "Prints the status of the network-creator component.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_hyphen_creator_hyphen_security_set_hyphen_joining_hyphen_link_hyphen_key = \
  SL_CLI_COMMAND(sli_zigbee_af_network_creator_security_set_joining_link_key_command,
                 "Sets the link key that a specific joining device will use when joining the network. This command can be also be used to add install code-derived link keys. If all FFs are entered for the EUI64 for the joining device, then this link key will be used for all joining devices without a joining key entry.",
                  "The EUI64 of the joining device" SL_CLI_UNIT_SEPARATOR "The link key that the joining device will use to enter the network" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_HEX, SL_CLI_ARG_HEX, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_hyphen_creator_hyphen_security_clear_hyphen_joining_hyphen_link_hyphen_keys = \
  SL_CLI_COMMAND(sli_zigbee_af_network_creator_security_clear_joining_link_key_command,
                 "Clears all of the joining link keys stored in the stack.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_hyphen_creator_hyphen_security_open_hyphen_network = \
  SL_CLI_COMMAND(sli_zigbee_af_network_creator_security_open_or_close_network_command,
                 "Opens the network for joining.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_hyphen_creator_hyphen_security_close_hyphen_network = \
  SL_CLI_COMMAND(sli_zigbee_af_network_creator_security_open_or_close_network_command,
                 "Closes the network for joining.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_hyphen_creator_hyphen_security_open_hyphen_with_hyphen_key = \
  SL_CLI_COMMAND(sli_zigbee_af_network_creator_security_open_network_with_key_command,
                 "Opens the network that would only allow the node with the specified EUI and link key pair to join.",
                  "The EUI64 of the joining device" SL_CLI_UNIT_SEPARATOR "The link key that the joining device will use to enter the network" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_HEX, SL_CLI_ARG_HEX, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_hyphen_creator_hyphen_security_set_hyphen_distributed_hyphen_key = \
  SL_CLI_COMMAND(sli_zigbee_af_network_creator_security_configure_distributed_key,
                 "Sets the TC Link key for a distributed network.",
                  "The pre-configured distributed key that the joining device will use to enter the network" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_HEX, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_hyphen_steering_status = \
  SL_CLI_COMMAND(sl_zigbee_af_network_steering_status_command,
                 "Displays the current status of the network steering process.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_hyphen_steering_start = \
  SL_CLI_COMMAND(sl_zigbee_af_network_steering_start_command,
                 "Starts the network steering process.",
                  "A mask of options for indicating specific behavior within the network-steering process." SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_hyphen_steering_stop = \
  SL_CLI_COMMAND(sl_zigbee_af_network_steering_stop_command,
                 "Stops the network steering process.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_hyphen_steering_pre_hyphen_configured_hyphen_key_hyphen_set = \
  SL_CLI_COMMAND(sl_zigbee_af_network_steering_set_preconfigured_key_command,
                 "Sets the pre-configured key so that the joining device can enter the network.",
                  "Sets the preconfigured key" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_HEX, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_shell_mask_1_set = \
  SL_CLI_COMMAND(sl_zigbee_af_network_steering_channel_set_command,
                 "Sets either the primary or secondary channel mask.",
                  "The channel mask to subtract the channel from" SL_CLI_UNIT_SEPARATOR "The value to set the channel mask to." SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT32, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_shell_mask_1_add = \
  SL_CLI_COMMAND(sl_zigbee_af_network_steering_channel_add_or_subtract_command,
                 "Adds a channel to either the primary or secondary channel mask of the network-steering component.",
                  "The channel mask to add a channel to" SL_CLI_UNIT_SEPARATOR "The channel to add to the mask" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_shell_mask_1_subtract = \
  SL_CLI_COMMAND(sl_zigbee_af_network_steering_channel_add_or_subtract_command,
                 "Subtracts a channel from either the primary or secondary channel mask of the network-steering component.",
                  "The channel mask to subtract the channel from" SL_CLI_UNIT_SEPARATOR "The channel to subtract the mask from" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_ota_hyphen_server_notify = \
  SL_CLI_COMMAND(otaImageNotifyCommand,
                 "Sends an OTA Image Notify message to the specified destination indicating a new version of an image is available for download.",
                  "The node ID (can be a broadcast address) to which this OTA Notify message should be sent" SL_CLI_UNIT_SEPARATOR "Target endpoint for the OTA Notify message (only meaningful for non-broadcast target destination)" SL_CLI_UNIT_SEPARATOR "Specifies which parameters to include in the OTA Notify cluster command payload (0 = jitter value only; 1 = jitter and manufacturer id; 2 = jitter, mfr id, and device id; 3 = jitter, mfr id, device id, and firmware version)" SL_CLI_UNIT_SEPARATOR "Corresponds to QueryJitter parameter in the OTA Upgrade cluster specification. Indicates whether the client receiving Image Notify Command should send in Query Next Image Request command or not." SL_CLI_UNIT_SEPARATOR "Manufacturer ID for the image being advertised (should match the mfr ID in the OTA files header)" SL_CLI_UNIT_SEPARATOR "Image type ID for the image being advertised (should match the image type ID from the OTA files header)" SL_CLI_UNIT_SEPARATOR "Firmware version of the image being advertised (should match the version from the OTA files header)" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT32, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_ota_hyphen_server_upgrade = \
  SL_CLI_COMMAND(otaSendUpgradeCommand,
                 "Instructs a device to upgrade now.",
                  "Short destination to send message" SL_CLI_UNIT_SEPARATOR "Endpoint destination to send message" SL_CLI_UNIT_SEPARATOR "Manufacturer ID for the image (0xFFFF for wildcard)" SL_CLI_UNIT_SEPARATOR "Image type for the image (0xFFFF for wildcard)" SL_CLI_UNIT_SEPARATOR "File version for the image (0xFFFFFFFF for wildcard)" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT32, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_policy_print = \
  SL_CLI_COMMAND(sli_zigbee_af_ota_server_policy_print,
                 "Prints the polices used by the OTA Server Policy component.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_policy_query = \
  SL_CLI_COMMAND(setPolicy,
                 "Sets the policy used by the OTA Server Policy component when it receives a query request from the client.",
                  "0 Upgrade if server has newer (default), 1 Downgrade if server has older, 2       Reinstall if server has same, 3 No next version (no next image is available for download)" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_policy_upgrade = \
  SL_CLI_COMMAND(setPolicy,
                 "Sets the policy used by the OTA Server Policy component when it receives an upgrade end request.",
                  "0 Upgrade Now (default), 1 Upgrade in 2       minutes, 2 Ask me later to upgrade, 3 Abort Upgrade (send default response)" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_policy_page_hyphen_req_hyphen_miss = \
  SL_CLI_COMMAND(setPolicy,
                 "Sets the modulus number of blocks not to respond to. This is used in testing to simulate a device that fails to receive certain blocks from an Image Page Request message.",
                  "The block modulus number to skip sending when responding to an Image Page Request. E.g. if 2, every other block will not be sent. 0 turns the feature off." SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_policy_page_hyphen_req_hyphen_sup = \
  SL_CLI_COMMAND(setPolicy,
                 "Sets whether the Page Request feature is supported or not.",
                  "1 if Page Request is supported, 0 if unsupported" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_policy_block_hyphen_request = \
  SL_CLI_COMMAND(setPolicy,
                 "Sets the policy used by the ota-server Policy component when it receives an image block request.",
                  "0 Send block (default), 1 Delay download once for 2 minutes, 2 Always abort download after first block" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_policy_image_hyphen_req_hyphen_min_hyphen_period = \
  SL_CLI_COMMAND(setPolicy,
                 "Sets the Minimum Block Period.",
                  "The minimum block period in milliseconds" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_ota_hyphen_storage_hyphen_common_printImages = \
  SL_CLI_COMMAND(sli_zigbee_af_ota_print_all_images,
                 "Prints the images.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_ota_hyphen_storage_hyphen_common_delete = \
  SL_CLI_COMMAND(sli_zigbee_af_ota_image_delete,
                 "Deletes the image at the specified index.",
                  "The index at which to begin deleting the image" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_ota_hyphen_storage_hyphen_common_reload = \
  SL_CLI_COMMAND(sli_zigbee_af_ota_reload_storage_device,
                 "Reload the storage device.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_ota_hyphen_storage_hyphen_common_storage_hyphen_info = \
  SL_CLI_COMMAND(sli_zigbee_af_ota_storage_info_print,
                 "Prints information about the storage device.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_ota_hyphen_storage_hyphen_common_data_hyphen_print = \
  SL_CLI_COMMAND(sli_zigbee_af_ota_storage_data_print,
                 "Prints arbitrary bytes of the OTA image on disk.",
                  "The index of the image to print its data" SL_CLI_UNIT_SEPARATOR "The offset into the OTA image that will be printed" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT32, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_reporting_print = \
  SL_CLI_COMMAND(sli_zigbee_af_reporting_cli_print,
                 "Prints the report table.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_reporting_clear = \
  SL_CLI_COMMAND(sli_zigbee_af_reporting_cli_clear,
                 "Clears all entries from the report table.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_reporting_remove = \
  SL_CLI_COMMAND(sli_zigbee_af_reporting_cli_remove,
                 "Removes an entry from the report table.",
                  "The index of the report to be removed" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_reporting_add = \
  SL_CLI_COMMAND(sli_zigbee_af_reporting_cli_add,
                 "Adds a new entry to the report table.",
                  "The local endpoint from which the attribute is reported" SL_CLI_UNIT_SEPARATOR "The cluster where the attribute is located" SL_CLI_UNIT_SEPARATOR "The ID of the attribute being reported" SL_CLI_UNIT_SEPARATOR "0 for client-side attributes or 1 for server-side attributes" SL_CLI_UNIT_SEPARATOR "The minimum reporting interval, measured in seconds." SL_CLI_UNIT_SEPARATOR "The maximum reporting interval, measured in seconds." SL_CLI_UNIT_SEPARATOR "The minimum change to the attribute that will result in a report being sent." SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT32, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_reporting_clear_hyphen_last_hyphen_report_hyphen_time = \
  SL_CLI_COMMAND(sli_zigbee_af_reporting_cli_clear_last_report_time,
                 "Clears the last report time of attributes.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_reporting_test_hyphen_timing = \
  SL_CLI_COMMAND(sli_zigbee_af_reporting_cli_test_timing,
                 "FOR TESTING PURPOSES - gather timing metrics for reporting table operations.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_update_hyphen_tc_hyphen_link_hyphen_key_timer = \
  SL_CLI_COMMAND(sl_zigbee_af_set_t_c_link_key_update_timer_command,
                 "This sets the the amount of time between subsequent trust center link key updates in milliseconds.",
                  "The amount of time between subsequent trust center link key updates in milliseconds" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT32, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_form = \
  SL_CLI_COMMAND(networkFormCommand,
                 "Forms a network on a given channel, with a given TX Power and PAN ID.",
                  "The channel on which to form the network" SL_CLI_UNIT_SEPARATOR "One-byte signed value indicating the TX Power that the radio should be set to" SL_CLI_UNIT_SEPARATOR "The PAN ID on which to form the network" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_INT8, SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_join = \
  SL_CLI_COMMAND(networkJoinCommand,
                 "Joins a network on a given channel, with a given TX Power and PAN ID.",
                  "The channel on which to join the network" SL_CLI_UNIT_SEPARATOR "One-byte signed value indicating the TX Power that the radio should be set to" SL_CLI_UNIT_SEPARATOR "The PAN ID on which to join the network" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_INT8, SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_pjoin = \
  SL_CLI_COMMAND(networkPermitJoinCommand,
                 "Turns permit joining on for the amount of time indicated.",
                  "A single byte indicating how long the device should have permit joining turn on for. A value of 0xff turns permit join indefinitely." SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_leave = \
  SL_CLI_COMMAND(networkLeaveCommand,
                 "Leaves a network.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_rejoin = \
  SL_CLI_COMMAND(networkRejoinCommand,
                 "ReJoins a network.",
                  "Boolean network key availability" SL_CLI_UNIT_SEPARATOR "Channel mask" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT32, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_rejoin_hyphen_diff_hyphen_device_hyphen_type = \
  SL_CLI_COMMAND(networkRejoinDiffDeviceTypeCommand,
                 "Rejoins an existing network in a secure or insecure manner with a different device type.",
                  "Boolean network key availability" SL_CLI_UNIT_SEPARATOR "Channel mask" SL_CLI_UNIT_SEPARATOR "An enumeration indicating the device type to rejoin as.The stack only accepts SL_ZIGBEE_END_DEVICE and SL_ZIGBEE_SLEEPY_END_DEVICE." SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_INT32, SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_extpanid = \
  SL_CLI_COMMAND(networkExtendedPanIdCommand,
                 "Writes the extended pan ID for the device.",
                  "extpanid" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_HEX, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_isopen = \
  SL_CLI_COMMAND(networkCheckPjoinCommand,
                 "Checks network pjoin status.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_broad_hyphen_pjoin = \
  SL_CLI_COMMAND(networkPermitJoinCommand,
                 "Permits joining on the network for a given number of seconds AND broadcasts a ZDO Mgmt Permit Joining request to all routers.",
                  "A single byte indicating how long the device should have permit joining turned on for. A value of 0xff turns on permit join indefinitely." SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_find_joinable = \
  SL_CLI_COMMAND(findJoinableNetworkCommand,
                 "findJoinableNetwork",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_find_unused = \
  SL_CLI_COMMAND(findUnusedPanIdCommand,
                 "findUnusedPanId",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_change_hyphen_channel = \
  SL_CLI_COMMAND(networkChangeChannelCommand,
                 "Attempts to change device over to a different channel given in the channel argument.",
                  "The channel to change to" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_set = \
  SL_CLI_COMMAND(networkSetCommand,
                 "Sets the network index used by all future CLI commands.  Before executing a CLI command, the framework switches to this network.  After the command finishes executing, the framework switches back to the previous network.  The CLI uses the same network index until the device resets or it is changed through this command.",
                  "index" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_init = \
  SL_CLI_COMMAND(networkInitCommand,
                 "Initializes a network; this is a test command used for tc-swap-out testing.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_id = \
  SL_CLI_COMMAND(networkIdCommand,
                 "Prints the current Node ID, EUI64, and Pan ID.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_change_hyphen_keep_hyphen_alive_hyphen_mode = \
  SL_CLI_COMMAND(changeKeepAliveModeCommand,
                 "Switches between different keep alive modes supported by a router.",
                  "Keep alive mode" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_timeout_hyphen_option_hyphen_mask = \
  SL_CLI_COMMAND(networkChangeChildTimeoutOptionMaskCommand,
                 "Attempts to change the child timeout option mask to filter out undesirable values (e.g. no more than 3 days).",
                  "timeout option mask" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_multi_hyphen_phy_hyphen_start = \
  SL_CLI_COMMAND(networkMultiPhyStartCommand,
                 "Used to start multi-PHY interface other than native and form the network. The stack uses same PanId as native radio network.",
                  "page" SL_CLI_UNIT_SEPARATOR "channel" SL_CLI_UNIT_SEPARATOR "power" SL_CLI_UNIT_SEPARATOR "optionsMask (Bit 0 = Routers allowed, Bit 1 = Broadcast allowed)" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT8, SL_CLI_ARG_INT8, SL_CLI_ARG_UINT8OPT, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_network_multi_hyphen_phy_hyphen_stop = \
  SL_CLI_COMMAND(networkMultiPhyStopCommand,
                 "Terminates the multi-PHY interface",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_keys_print = \
  SL_CLI_COMMAND(keysPrintCommand,
                 "Prints all security keys.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_keys_delete = \
  SL_CLI_COMMAND(keysDeleteCommand,
                 "Delete the specified link key index.",
                  "index" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_keys_clear = \
  SL_CLI_COMMAND(keysClearCommand,
                 "Clears all security keys.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_binding_hyphen_table_print = \
  SL_CLI_COMMAND(optionBindingTablePrintCommand,
                 "Prints the binding table to the command line.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_binding_hyphen_table_clear = \
  SL_CLI_COMMAND(optionBindingTableClearCommand,
                 "Clears the binding table.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_binding_hyphen_table_set = \
  SL_CLI_COMMAND(optionBindingTableSetCommand,
                 "Sets the binding table",
                  "index" SL_CLI_UNIT_SEPARATOR "cluster" SL_CLI_UNIT_SEPARATOR "localEp" SL_CLI_UNIT_SEPARATOR "remoteEp" SL_CLI_UNIT_SEPARATOR "eui64" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT8, SL_CLI_ARG_HEX, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_print_hyphen_rx_hyphen_msgs_enable = \
  SL_CLI_COMMAND(optionPrintRxCommand,
                 "Enables printing of Rx messages.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_print_hyphen_rx_hyphen_msgs_disable = \
  SL_CLI_COMMAND(optionPrintRxCommand,
                 "Disables printing of Rx messages.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_option_register = \
  SL_CLI_COMMAND(optionRegisterCommand,
                 "",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_option_target = \
  SL_CLI_COMMAND(optionDiscoveryTargetCommand,
                 "",
                  "targetId" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_option_disc = \
  SL_CLI_COMMAND(optionDiscoverCommand,
                 "",
                  "profileId" SL_CLI_UNIT_SEPARATOR "clusterId" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_apsretry_on = \
  SL_CLI_COMMAND(optionApsRetryCommand,
                 "",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_apsretry_off = \
  SL_CLI_COMMAND(optionApsRetryCommand,
                 "",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_apsretry_default = \
  SL_CLI_COMMAND(optionApsRetryCommand,
                 "",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_aps_on = \
  SL_CLI_COMMAND(optionApsSecurityCommand,
                 "",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_aps_off = \
  SL_CLI_COMMAND(optionApsSecurityCommand,
                 "",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_security_set_hyphen_allow_hyphen_trust_hyphen_center_hyphen_rejoin_hyphen_using_hyphen_well_hyphen_known_hyphen_key = \
  SL_CLI_COMMAND(optionSecurityAllowTrustCenterRejoinUsingWellKnownKey,
                 "",
                  "Bool: allow trust center rejoin using well-known key" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_security_set_hyphen_allow_hyphen_trust_hyphen_center_hyphen_rejoin_hyphen_using_hyphen_well_hyphen_known_hyphen_key_hyphen_timeout = \
  SL_CLI_COMMAND(optionSecurityAllowTrustCenterRejoinUsingWellKnownKeyTimeout,
                 "",
                  "timeout" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_security_set_hyphen_key_hyphen_request_hyphen_policy = \
  SL_CLI_COMMAND(optionSecuritySetKeyRequestPolicy,
                 "",
                  "TC link key request policy" SL_CLI_UNIT_SEPARATOR "App link key request policy" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_changekey_link = \
  SL_CLI_COMMAND(changeKeyCommand,
                 "",
                  "key" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_HEX, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_changekey_network = \
  SL_CLI_COMMAND(changeKeyCommand,
                 "",
                  "key" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_HEX, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_option_link = \
  SL_CLI_COMMAND(optionLinkCommand,
                 "",
                  "index" SL_CLI_UNIT_SEPARATOR "eui64" SL_CLI_UNIT_SEPARATOR "key" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_HEX, SL_CLI_ARG_HEX, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_option_install_hyphen_code = \
  SL_CLI_COMMAND(optionInstallCodeCommand,
                 "",
                  "index" SL_CLI_UNIT_SEPARATOR "eui64" SL_CLI_UNIT_SEPARATOR "installCode" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_HEX, SL_CLI_ARG_HEX, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_zdo_route = \
  SL_CLI_COMMAND(zdoRouteRequestCommand,
                 "Sends a ZDO route request command to the target.",
                  "target" SL_CLI_UNIT_SEPARATOR "index" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_zdo_power = \
  SL_CLI_COMMAND(zdoPowerDescriptorRequestCommand,
                 "Sends a ZDO Power Descriptor Request to the target device.",
                  "target" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_zdo_mgmt_hyphen_lqi = \
  SL_CLI_COMMAND(zdoMgmtLqiCommand,
                 "Sends a ZDO MGMT-LQI (LQI Table) Request to the target device.",
                  "target" SL_CLI_UNIT_SEPARATOR "startIndex" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_zdo_mgmt_hyphen_bind = \
  SL_CLI_COMMAND(zdoMgmtBindCommand,
                 "Sends a ZDO MGMT-Bind (Binding Table) Request to the target device.",
                  "target" SL_CLI_UNIT_SEPARATOR "startIndex" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_zdo_leave = \
  SL_CLI_COMMAND(zdoLeaveRequestCommand,
                 "Sends a ZDO Management Leave command to the target device.",
                  "target" SL_CLI_UNIT_SEPARATOR "removeChildren" SL_CLI_UNIT_SEPARATOR "rejoin" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_unbind_group = \
  SL_CLI_COMMAND(zdoUnbindGroupCommand,
                 "Sends an unbind request for a multicast binding to the target device.",
                  "target" SL_CLI_UNIT_SEPARATOR "source eui64" SL_CLI_UNIT_SEPARATOR "source endpoint" SL_CLI_UNIT_SEPARATOR "clusterID" SL_CLI_UNIT_SEPARATOR "groupAddress" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_HEX, SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_unbind_unicast = \
  SL_CLI_COMMAND(zdoUnbindUnicastCommand,
                 "Sends an unbind request for a unicast binding to the target device.",
                  "target" SL_CLI_UNIT_SEPARATOR "source eui64" SL_CLI_UNIT_SEPARATOR "source endpoint" SL_CLI_UNIT_SEPARATOR "clusterID" SL_CLI_UNIT_SEPARATOR "destinationEUI64" SL_CLI_UNIT_SEPARATOR "destination endpoint" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_HEX, SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT16, SL_CLI_ARG_HEX, SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_zdo_active = \
  SL_CLI_COMMAND(zdoActiveEpCommand,
                 "Sends an active endpoint request to the device with the given short ID.",
                  "nodeId" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_zdo_bind = \
  SL_CLI_COMMAND(zdoBindCommand,
                 "Sends a ZDO Bind command to a device specified in the command arguments.",
                  "Destination" SL_CLI_UNIT_SEPARATOR "Source endpoint" SL_CLI_UNIT_SEPARATOR "Destination endpoint" SL_CLI_UNIT_SEPARATOR "clusterID" SL_CLI_UNIT_SEPARATOR "remoteEUI64" SL_CLI_UNIT_SEPARATOR "destEUI64" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT16, SL_CLI_ARG_HEX, SL_CLI_ARG_HEX, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_zdo_node = \
  SL_CLI_COMMAND(zdoNodeCommand,
                 "Sends a node descriptor request to a given target device.",
                  "target" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_zdo_match = \
  SL_CLI_COMMAND(zdoMatchCommand,
                 "Sends a matchDescriptorsRequest to the given destination with the given profile.",
                  "nodeId" SL_CLI_UNIT_SEPARATOR "profile" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_zdo_simple = \
  SL_CLI_COMMAND(zdoSimpleCommand,
                 "Sends a simple descriptor request for the short address and endpoint specified.",
                  "dest" SL_CLI_UNIT_SEPARATOR "targetEndpoint" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_zdo_ieee = \
  SL_CLI_COMMAND(zdoIeeeAddressRequestCommand,
                 "Requests an IEEE address based on a given node ID.",
                  "nodeId" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_zdo_nwk = \
  SL_CLI_COMMAND(zdoNwkAddressRequestCommand,
                 "Sends a network address request for the given IEEE address.",
                  "ieee" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_HEX, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_nwk_hyphen_upd_scan_hyphen_chan_hyphen_mask = \
  SL_CLI_COMMAND(zdoNetworkUpdateScanCommand,
                 "Performs an energy scan on given channel mask.",
                  "targetNodeId" SL_CLI_UNIT_SEPARATOR "scanDuration" SL_CLI_UNIT_SEPARATOR "scanCount" SL_CLI_UNIT_SEPARATOR "channelMask" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT32, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_nwk_hyphen_upd_set = \
  SL_CLI_COMMAND(zdoNetworkUpdateSetCommand,
                 "Broadcasts the ID of the new network manager and active channels.",
                  "nwkMgeId" SL_CLI_UNIT_SEPARATOR "channelMask" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT32, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_nwk_hyphen_upd_scan = \
  SL_CLI_COMMAND(zdoNetworkUpdateScanCommand,
                 "Performs an energy scan.",
                  "targetNodeId" SL_CLI_UNIT_SEPARATOR "scanDuration" SL_CLI_UNIT_SEPARATOR "scanCount" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_nwk_hyphen_upd_chanPg = \
  SL_CLI_COMMAND(zdoNetworkUpdateChannelCommand,
                 "Sends an update channel page req. The stack sends nwk enhanced update req for non-zero page.",
                  "channel" SL_CLI_UNIT_SEPARATOR "page" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_nwk_hyphen_upd_chan = \
  SL_CLI_COMMAND(zdoNetworkUpdateChannelCommand,
                 "Sends an update channel request.",
                  "channel" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT8, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_out_hyphen_cl_hyphen_list_add = \
  SL_CLI_COMMAND(zdoAddClusterCommand,
                 "Adds clusters to the known client (out) clusters on this device.",
                  "clusterId" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_out_hyphen_cl_hyphen_list_clear = \
  SL_CLI_COMMAND(zdoClearClusterCommand,
                 "Clears the ZDO list of client (out) clusters.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_in_hyphen_cl_hyphen_list_add = \
  SL_CLI_COMMAND(zdoAddClusterCommand,
                 "Adds clusters to the known client (in) clusters on this device.",
                  "clusterId" SL_CLI_UNIT_SEPARATOR,
                 {SL_CLI_ARG_UINT16, SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_in_hyphen_cl_hyphen_list_clear = \
  SL_CLI_COMMAND(zdoClearClusterCommand,
                 "Clears the ZDO list of client (in) clusters.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_print_attr = \
  SL_CLI_COMMAND(sl_zigbee_af_print_attribute_table,
                 "Prints attribute.",
                  "",
                 {SL_CLI_ARG_END, });

static const sl_cli_command_info_t cli_cmd_print_time = \
  SL_CLI_COMMAND(printTimeCommand,
                 "Prints time.",
                  "",
                 {SL_CLI_ARG_END, });


// Create group command tables and structs if cli_groups given
// in template. Group name is suffixed with _group_table for tables
// and group commands are cli_cmd_grp_( group name )
static const sl_cli_command_entry_t address_hyphen_table_group_table[] = {
  { "add", &cli_cmd_address_hyphen_table_add, false },
  { "set", &cli_cmd_address_hyphen_table_set, false },
  { "remove", &cli_cmd_address_hyphen_table_remove, false },
  { "lookup", &cli_cmd_address_hyphen_table_lookup, false },
  { "print", &cli_cmd_address_hyphen_table_print, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_address_hyphen_table = \
  SL_CLI_COMMAND_GROUP(address_hyphen_table_group_table, "");

static const sl_cli_command_entry_t concentrator_group_table[] = {
  { "status", &cli_cmd_concentrator_status, false },
  { "start", &cli_cmd_concentrator_start, false },
  { "stop", &cli_cmd_concentrator_stop, false },
  { "agg", &cli_cmd_concentrator_agg, false },
  { "print-table", &cli_cmd_concentrator_print_hyphen_table, false },
  { "set-router-behavior", &cli_cmd_concentrator_set_hyphen_router_hyphen_behavior, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_concentrator = \
  SL_CLI_COMMAND_GROUP(concentrator_group_table, "concentrator related commands.");

static const sl_cli_command_entry_t counters_group_table[] = {
  { "print", &cli_cmd_counters_print, false },
  { "print-counter-type", &cli_cmd_counters_print_hyphen_counter_hyphen_type, false },
  { "simple-print", &cli_cmd_counters_simple_hyphen_print, false },
  { "clear", &cli_cmd_counters_clear, false },
  { "print-thresholds", &cli_cmd_counters_print_hyphen_thresholds, false },
  { "set-threshold", &cli_cmd_counters_set_hyphen_threshold, false },
  { "reset-thresholds", &cli_cmd_counters_reset_hyphen_thresholds, false },
  { "send-request", &cli_cmd_counters_send_hyphen_request, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_counters = \
  SL_CLI_COMMAND_GROUP(counters_group_table, "counters related commands.");

static const sl_cli_command_entry_t enable_type_group_table[] = {
  { "stack", &cli_cmd_enable_type_stack, false },
  { "core", &cli_cmd_enable_type_core, false },
  { "app", &cli_cmd_enable_type_app, false },
  { "zcl", &cli_cmd_enable_type_zcl, false },
  { "legacy_af_debug", &cli_cmd_enable_type_legacy_af_debug, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_enable_type = \
  SL_CLI_COMMAND_GROUP(enable_type_group_table, "");

static const sl_cli_command_entry_t zigbee_print_group_table[] = {
  { "enable_type", &cli_cmd_grp_enable_type, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_zigbee_print = \
  SL_CLI_COMMAND_GROUP(zigbee_print_group_table, "");

static const sl_cli_command_entry_t gateway_group_table[] = {
  { "time-sync-local", &cli_cmd_gateway_time_hyphen_sync_hyphen_local, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_gateway = \
  SL_CLI_COMMAND_GROUP(gateway_group_table, "gateway related commands");

static const sl_cli_command_entry_t mask_group_table[] = {
  { "add", &cli_cmd_mask_add, false },
  { "subtract", &cli_cmd_mask_subtract, false },
  { "set", &cli_cmd_mask_set, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_mask = \
  SL_CLI_COMMAND_GROUP(mask_group_table, "mask related commands");

static const sl_cli_command_entry_t network_hyphen_creator_group_table[] = {
  { "start", &cli_cmd_network_hyphen_creator_start, false },
  { "stop", &cli_cmd_network_hyphen_creator_stop, false },
  { "form", &cli_cmd_network_hyphen_creator_form, false },
  { "status", &cli_cmd_network_hyphen_creator_status, false },
  { "mask", &cli_cmd_grp_mask, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_network_hyphen_creator = \
  SL_CLI_COMMAND_GROUP(network_hyphen_creator_group_table, "network-creator related commands.");

static const sl_cli_command_entry_t network_hyphen_creator_hyphen_security_group_table[] = {
  { "set-joining-link-key", &cli_cmd_network_hyphen_creator_hyphen_security_set_hyphen_joining_hyphen_link_hyphen_key, false },
  { "clear-joining-link-keys", &cli_cmd_network_hyphen_creator_hyphen_security_clear_hyphen_joining_hyphen_link_hyphen_keys, false },
  { "open-network", &cli_cmd_network_hyphen_creator_hyphen_security_open_hyphen_network, false },
  { "close-network", &cli_cmd_network_hyphen_creator_hyphen_security_close_hyphen_network, false },
  { "open-with-key", &cli_cmd_network_hyphen_creator_hyphen_security_open_hyphen_with_hyphen_key, false },
  { "set-distributed-key", &cli_cmd_network_hyphen_creator_hyphen_security_set_hyphen_distributed_hyphen_key, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_network_hyphen_creator_hyphen_security = \
  SL_CLI_COMMAND_GROUP(network_hyphen_creator_hyphen_security_group_table, "network-creator-security related commands.");

static const sl_cli_command_entry_t shell_mask_1_group_table[] = {
  { "set", &cli_cmd_shell_mask_1_set, false },
  { "add", &cli_cmd_shell_mask_1_add, false },
  { "subtract", &cli_cmd_shell_mask_1_subtract, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_shell_mask_1 = \
  SL_CLI_COMMAND_GROUP(shell_mask_1_group_table, "mask related command.");

static const sl_cli_command_entry_t network_hyphen_steering_group_table[] = {
  { "status", &cli_cmd_network_hyphen_steering_status, false },
  { "start", &cli_cmd_network_hyphen_steering_start, false },
  { "stop", &cli_cmd_network_hyphen_steering_stop, false },
  { "pre-configured-key-set", &cli_cmd_network_hyphen_steering_pre_hyphen_configured_hyphen_key_hyphen_set, false },
  { "mask", &cli_cmd_grp_shell_mask_1, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_network_hyphen_steering = \
  SL_CLI_COMMAND_GROUP(network_hyphen_steering_group_table, "network-steering related commands.");

static const sl_cli_command_entry_t policy_group_table[] = {
  { "print", &cli_cmd_policy_print, false },
  { "query", &cli_cmd_policy_query, false },
  { "upgrade", &cli_cmd_policy_upgrade, false },
  { "page-req-miss", &cli_cmd_policy_page_hyphen_req_hyphen_miss, false },
  { "page-req-sup", &cli_cmd_policy_page_hyphen_req_hyphen_sup, false },
  { "block-request", &cli_cmd_policy_block_hyphen_request, false },
  { "image-req-min-period", &cli_cmd_policy_image_hyphen_req_hyphen_min_hyphen_period, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_policy = \
  SL_CLI_COMMAND_GROUP(policy_group_table, "policy related commands");

static const sl_cli_command_entry_t ota_hyphen_server_group_table[] = {
  { "notify", &cli_cmd_ota_hyphen_server_notify, false },
  { "upgrade", &cli_cmd_ota_hyphen_server_upgrade, false },
  { "policy", &cli_cmd_grp_policy, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_ota_hyphen_server = \
  SL_CLI_COMMAND_GROUP(ota_hyphen_server_group_table, "ota-server related commands.");

static const sl_cli_command_entry_t ota_hyphen_storage_hyphen_common_group_table[] = {
  { "printImages", &cli_cmd_ota_hyphen_storage_hyphen_common_printImages, false },
  { "delete", &cli_cmd_ota_hyphen_storage_hyphen_common_delete, false },
  { "reload", &cli_cmd_ota_hyphen_storage_hyphen_common_reload, false },
  { "storage-info", &cli_cmd_ota_hyphen_storage_hyphen_common_storage_hyphen_info, false },
  { "data-print", &cli_cmd_ota_hyphen_storage_hyphen_common_data_hyphen_print, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_ota_hyphen_storage_hyphen_common = \
  SL_CLI_COMMAND_GROUP(ota_hyphen_storage_hyphen_common_group_table, "ota-storage-common related commands");

static const sl_cli_command_entry_t reporting_group_table[] = {
  { "print", &cli_cmd_reporting_print, false },
  { "clear", &cli_cmd_reporting_clear, false },
  { "remove", &cli_cmd_reporting_remove, false },
  { "add", &cli_cmd_reporting_add, false },
  { "clear-last-report-time", &cli_cmd_reporting_clear_hyphen_last_hyphen_report_hyphen_time, false },
  { "test-timing", &cli_cmd_reporting_test_hyphen_timing, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_reporting = \
  SL_CLI_COMMAND_GROUP(reporting_group_table, "reporting related commands.");

static const sl_cli_command_entry_t update_hyphen_tc_hyphen_link_hyphen_key_group_table[] = {
  { "timer", &cli_cmd_update_hyphen_tc_hyphen_link_hyphen_key_timer, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_update_hyphen_tc_hyphen_link_hyphen_key = \
  SL_CLI_COMMAND_GROUP(update_hyphen_tc_hyphen_link_hyphen_key_group_table, "update-tc-link-key related commands");

static const sl_cli_command_entry_t plugin_group_table[] = {
  { "address-table", &cli_cmd_grp_address_hyphen_table, false },
  { "concentrator", &cli_cmd_grp_concentrator, false },
  { "counters", &cli_cmd_grp_counters, false },
  { "gateway", &cli_cmd_grp_gateway, false },
  { "network-creator", &cli_cmd_grp_network_hyphen_creator, false },
  { "network-creator-security", &cli_cmd_grp_network_hyphen_creator_hyphen_security, false },
  { "network-steering", &cli_cmd_grp_network_hyphen_steering, false },
  { "ota-server", &cli_cmd_grp_ota_hyphen_server, false },
  { "ota-storage-common", &cli_cmd_grp_ota_hyphen_storage_hyphen_common, false },
  { "reporting", &cli_cmd_grp_reporting, false },
  { "update-tc-link-key", &cli_cmd_grp_update_hyphen_tc_hyphen_link_hyphen_key, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_plugin = \
  SL_CLI_COMMAND_GROUP(plugin_group_table, "");

static const sl_cli_command_entry_t find_group_table[] = {
  { "joinable", &cli_cmd_find_joinable, false },
  { "unused", &cli_cmd_find_unused, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_find = \
  SL_CLI_COMMAND_GROUP(find_group_table, "network find commands.");

static const sl_cli_command_entry_t network_group_table[] = {
  { "form", &cli_cmd_network_form, false },
  { "join", &cli_cmd_network_join, false },
  { "pjoin", &cli_cmd_network_pjoin, false },
  { "leave", &cli_cmd_network_leave, false },
  { "rejoin", &cli_cmd_network_rejoin, false },
  { "rejoin-diff-device-type", &cli_cmd_network_rejoin_hyphen_diff_hyphen_device_hyphen_type, false },
  { "extpanid", &cli_cmd_network_extpanid, false },
  { "isopen", &cli_cmd_network_isopen, false },
  { "broad-pjoin", &cli_cmd_network_broad_hyphen_pjoin, false },
  { "change-channel", &cli_cmd_network_change_hyphen_channel, false },
  { "set", &cli_cmd_network_set, false },
  { "init", &cli_cmd_network_init, false },
  { "id", &cli_cmd_network_id, false },
  { "change-keep-alive-mode", &cli_cmd_network_change_hyphen_keep_hyphen_alive_hyphen_mode, false },
  { "timeout-option-mask", &cli_cmd_network_timeout_hyphen_option_hyphen_mask, false },
  { "multi-phy-start", &cli_cmd_network_multi_hyphen_phy_hyphen_start, false },
  { "multi-phy-stop", &cli_cmd_network_multi_hyphen_phy_hyphen_stop, false },
  { "find", &cli_cmd_grp_find, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_network = \
  SL_CLI_COMMAND_GROUP(network_group_table, "Network related commands.");

static const sl_cli_command_entry_t keys_group_table[] = {
  { "print", &cli_cmd_keys_print, false },
  { "delete", &cli_cmd_keys_delete, false },
  { "clear", &cli_cmd_keys_clear, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_keys = \
  SL_CLI_COMMAND_GROUP(keys_group_table, "Security keys related commands.");

static const sl_cli_command_entry_t binding_hyphen_table_group_table[] = {
  { "print", &cli_cmd_binding_hyphen_table_print, false },
  { "clear", &cli_cmd_binding_hyphen_table_clear, false },
  { "set", &cli_cmd_binding_hyphen_table_set, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_binding_hyphen_table = \
  SL_CLI_COMMAND_GROUP(binding_hyphen_table_group_table, "Binding table related commands.");

static const sl_cli_command_entry_t print_hyphen_rx_hyphen_msgs_group_table[] = {
  { "enable", &cli_cmd_print_hyphen_rx_hyphen_msgs_enable, false },
  { "disable", &cli_cmd_print_hyphen_rx_hyphen_msgs_disable, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_print_hyphen_rx_hyphen_msgs = \
  SL_CLI_COMMAND_GROUP(print_hyphen_rx_hyphen_msgs_group_table, "Enables/Disables printing of Rx messages.");

static const sl_cli_command_entry_t apsretry_group_table[] = {
  { "on", &cli_cmd_apsretry_on, false },
  { "off", &cli_cmd_apsretry_off, false },
  { "default", &cli_cmd_apsretry_default, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_apsretry = \
  SL_CLI_COMMAND_GROUP(apsretry_group_table, "APS retry flag force commands");

static const sl_cli_command_entry_t aps_group_table[] = {
  { "on", &cli_cmd_aps_on, false },
  { "off", &cli_cmd_aps_off, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_aps = \
  SL_CLI_COMMAND_GROUP(aps_group_table, "Security aps related commands.");

static const sl_cli_command_entry_t security_group_table[] = {
  { "set-allow-trust-center-rejoin-using-well-known-key", &cli_cmd_security_set_hyphen_allow_hyphen_trust_hyphen_center_hyphen_rejoin_hyphen_using_hyphen_well_hyphen_known_hyphen_key, false },
  { "set-allow-trust-center-rejoin-using-well-known-key-timeout", &cli_cmd_security_set_hyphen_allow_hyphen_trust_hyphen_center_hyphen_rejoin_hyphen_using_hyphen_well_hyphen_known_hyphen_key_hyphen_timeout, false },
  { "set-key-request-policy", &cli_cmd_security_set_hyphen_key_hyphen_request_hyphen_policy, false },
  { "aps", &cli_cmd_grp_aps, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_security = \
  SL_CLI_COMMAND_GROUP(security_group_table, "Security related commands.");

static const sl_cli_command_entry_t option_group_table[] = {
  { "register", &cli_cmd_option_register, false },
  { "target", &cli_cmd_option_target, false },
  { "disc", &cli_cmd_option_disc, false },
  { "link", &cli_cmd_option_link, false },
  { "install-code", &cli_cmd_option_install_hyphen_code, false },
  { "binding-table", &cli_cmd_grp_binding_hyphen_table, false },
  { "print-rx-msgs", &cli_cmd_grp_print_hyphen_rx_hyphen_msgs, false },
  { "apsretry", &cli_cmd_grp_apsretry, false },
  { "security", &cli_cmd_grp_security, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_option = \
  SL_CLI_COMMAND_GROUP(option_group_table, "Option related commands.");

static const sl_cli_command_entry_t changekey_group_table[] = {
  { "link", &cli_cmd_changekey_link, false },
  { "network", &cli_cmd_changekey_network, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_changekey = \
  SL_CLI_COMMAND_GROUP(changekey_group_table, "changekey related commands.");

static const sl_cli_command_entry_t unbind_group_table[] = {
  { "group", &cli_cmd_unbind_group, false },
  { "unicast", &cli_cmd_unbind_unicast, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_unbind = \
  SL_CLI_COMMAND_GROUP(unbind_group_table, "Zdo unbind related commands.");

static const sl_cli_command_entry_t nwk_hyphen_upd_group_table[] = {
  { "scan-chan-mask", &cli_cmd_nwk_hyphen_upd_scan_hyphen_chan_hyphen_mask, false },
  { "set", &cli_cmd_nwk_hyphen_upd_set, false },
  { "scan", &cli_cmd_nwk_hyphen_upd_scan, false },
  { "chanPg", &cli_cmd_nwk_hyphen_upd_chanPg, false },
  { "chan", &cli_cmd_nwk_hyphen_upd_chan, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_nwk_hyphen_upd = \
  SL_CLI_COMMAND_GROUP(nwk_hyphen_upd_group_table, "Zdo nwk-upd related commands.");

static const sl_cli_command_entry_t out_hyphen_cl_hyphen_list_group_table[] = {
  { "add", &cli_cmd_out_hyphen_cl_hyphen_list_add, false },
  { "clear", &cli_cmd_out_hyphen_cl_hyphen_list_clear, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_out_hyphen_cl_hyphen_list = \
  SL_CLI_COMMAND_GROUP(out_hyphen_cl_hyphen_list_group_table, "Zdo out-cl-list related commands.");

static const sl_cli_command_entry_t in_hyphen_cl_hyphen_list_group_table[] = {
  { "add", &cli_cmd_in_hyphen_cl_hyphen_list_add, false },
  { "clear", &cli_cmd_in_hyphen_cl_hyphen_list_clear, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_in_hyphen_cl_hyphen_list = \
  SL_CLI_COMMAND_GROUP(in_hyphen_cl_hyphen_list_group_table, "Zdo in-cl-list related commands.");

static const sl_cli_command_entry_t zdo_group_table[] = {
  { "route", &cli_cmd_zdo_route, false },
  { "power", &cli_cmd_zdo_power, false },
  { "mgmt-lqi", &cli_cmd_zdo_mgmt_hyphen_lqi, false },
  { "mgmt-bind", &cli_cmd_zdo_mgmt_hyphen_bind, false },
  { "leave", &cli_cmd_zdo_leave, false },
  { "active", &cli_cmd_zdo_active, false },
  { "bind", &cli_cmd_zdo_bind, false },
  { "node", &cli_cmd_zdo_node, false },
  { "match", &cli_cmd_zdo_match, false },
  { "simple", &cli_cmd_zdo_simple, false },
  { "ieee", &cli_cmd_zdo_ieee, false },
  { "nwk", &cli_cmd_zdo_nwk, false },
  { "unbind", &cli_cmd_grp_unbind, false },
  { "nwk-upd", &cli_cmd_grp_nwk_hyphen_upd, false },
  { "out-cl-list", &cli_cmd_grp_out_hyphen_cl_hyphen_list, false },
  { "in-cl-list", &cli_cmd_grp_in_hyphen_cl_hyphen_list, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_zdo = \
  SL_CLI_COMMAND_GROUP(zdo_group_table, "Zdo related commands.");

static const sl_cli_command_entry_t print_group_table[] = {
  { "attr", &cli_cmd_print_attr, false },
  { "time", &cli_cmd_print_time, false },
  { NULL, NULL, false },
};
static const sl_cli_command_info_t cli_cmd_grp_print = \
  SL_CLI_COMMAND_GROUP(print_group_table, "print related commands.");

// Create root command table
const sl_cli_command_entry_t sl_cli_default_command_table[] = {
  { "zigbee_print", &cli_cmd_grp_zigbee_print, false },
  { "plugin", &cli_cmd_grp_plugin, false },
  { "network", &cli_cmd_grp_network, false },
  { "net", &cli_cmd_grp_network, true },
  { "keys", &cli_cmd_grp_keys, false },
  { "option", &cli_cmd_grp_option, false },
  { "opt", &cli_cmd_grp_option, true },
  { "plugin", &cli_cmd_grp_plugin, false },
  { "plug", &cli_cmd_grp_plugin, true },
  { "changekey", &cli_cmd_grp_changekey, false },
  { "changek", &cli_cmd_grp_changekey, true },
  { "zdo", &cli_cmd_grp_zdo, false },
  { "print", &cli_cmd_grp_print, false },
  { NULL, NULL, false },
};


#ifdef __cplusplus
}
#endif
