#!/usr/bin/make -f
# -*- makefile -*-
# ex: set tabstop=4 noexpandtab:
# -*- coding: utf-8 -*

default: help zpc/default
	@echo "$@: TODO: Support more than $^ by default"
	@date -u

SELF?=${CURDIR}/helper.mk

CMAKE_GENERATOR?=Ninja
export CMAKE_GENERATOR

build_dir?=build
sudo?=sudo

packages?=cmake ninja-build build-essential python3-full ruby clang
packages+=git-lfs unp time file
packages+=nlohmann-json3-dev
# TODO: remove for offline build
packages+=curl wget python3-pip
packages+=npm

RUST_VERSION?=1.64.0
export PATH := ${HOME}/.cargo/bin:${PATH}

zpc_exe?=${build_dir}/applications/zpc/zpc
exes+=${zpc_exe}

help: README.md
	@cat $<
	@echo ""
	@echo "# Available rules at your own risk:"
	@grep -o '^[^ ]*:' ${SELF} | grep -v '\$$' | grep -v '^#' | grep -v '^\.'
	@echo ""
	@echo "# Environment:"
	@echo "# PATH=${PATH}"
	@echo ""

setup/debian: docker/target_dependencies.apt
	cat /etc/debian_version
	-${sudo} apt update
	${sudo} apt install -y $(shell cat $<)
	${sudo} apt install -y ${packages}
	@echo "$@: TODO: Support debian stable rustc=1.63 https://tracker.debian.org/pkg/rustc"

setup/rust:
	@echo "$@: TODO: Support https://tracker.debian.org/pkg/rustup"
	curl https://sh.rustup.rs -sSf | bash -s -- -y --default-toolchain ${RUST_VERSION}
	cat $${HOME}/.cargo/env
	@echo '$@: info: You might like to add ". $${HOME}/.cargo/env" to "$${HOME}/.bashrc"'
	-which rustc
	rustc --version
	cargo --version
	@echo "$@: TODO: Support stable version from https://releases.rs/ or older"

setup/python:
	@echo "$@: TODO: https://github.com/wbond/pybars3/issues/82"
	pip3 --version || echo "warning: Please install pip"
	pip3 install --break-system-packages pybars3

setup/debian/12: setup/debian setup/rust setup/python
	date -u

setup: setup/debian/12
	date -u

git: .git/lfs
	git lfs version || echo "$@: warning: Please install git-lfs"
	git lfs status --porcelain || git lfs install
	time git lfs pull
	git lfs update || git lfs update --force
	git lfs status --porcelain

configure: ${build_dir}/CMakeCache.txt
	file -E $<

${build_dir}/CMakeCache.txt: CMakeLists.txt ${build_pre_list}
	cmake -B ${build_dir}

build: ${build_dir}/CMakeCache.txt
	cmake --build ${<D} \
		|| cat ${build_dir}/CMakeFiles/CMakeOutput.log
	cmake --build ${<D}
.PHONY: build

${build_dir}/%: build
	file -E "$<"

${exe}: build
	file -E $<

all: ${exes}
	file -E $<

test: ${build_dir}
	ctest --test-dir ${<}

all/default: configure build test
	@date -u

zpc/configure: CMakeLists.txt
	cmake \
		-B ${build_dir} \
		-DBUILD_AOXPC=ON \
		-DBUILD_CPCD=OFF \
		-DBUILD_DEV_GUI=ON \
		-DBUILD_EMD=OFF \
		-DBUILD_EPC=ON \
		-DBUILD_GMS=ON \
		-DBUILD_IMAGE_PROVIDER=ON \
		-DBUILD_NAL=ON \
		-DBUILD_OTBR=OFF \
		-DBUILD_POSITIONING=ON \
		-DBUILD_TESTING=ON \
		-DBUILD_UPTI_CAP=ON \
		-DBUILD_UPTI_WRITER=ON \
		-DBUILD_UPVL=ON \
		-DBUILD_ZIGBEED=OFF \
		-DBUILD_ZIGPC=OFF

zpc/build: zpc/configure build
	@date -u

zpc/test: ${build_dir}/applications/zpc/components/zwave_command_classes/test/
	ctest --test-dir ${<}

zpc/default: zpc/configure zpc/build
	@date -u
