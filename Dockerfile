#!/bin/echo docker build . -f
# -*- coding: utf-8 -*-

FROM debian:12

ENV DEBIAN_FRONTEND noninteractive
ENV LC_ALL en_US.UTF-8
ENV LANG ${LC_ALL}

RUN echo "# log: Configuring locales" \
  && set -x  \
  && apt-get update -y \
  && apt-get install -y locales \
  && echo "${LC_ALL} UTF-8" | tee /etc/locale.gen \
  && locale-gen ${LC_ALL} \
  && dpkg-reconfigure locales \
  && TZ=Etc/UTC apt-get -y install tzdata \
  && date -u
  
ENV project UnifySDK
ENV workdir /usr/local/opt/${project}
ADD . ${workdir}

WORKDIR ${workdir}

RUN echo "# log: Setup system" \
  && set -x  \
  && apt-get install -y make sudo \
  && ./helper.mk help setup/debian/12 \
  && date -u

RUN echo "# log: Build" \
  && set -x  \
  && ./helper.mk \
  && date -u
