#!/bin/make

# Author: Anne C. van Rossum
# Date: Aug. 04, 2011

# This include file should define BACKEND
-include $(HOME)/.rur/rur.mk
-include local.mk

CURRENT_MODULE_PATH:=$(CURDIR)
ROS_PACKAGE_PATH:=$(ROS_PACKAGE_PATH):$(CURRENT_MODULE_PATH)

ROS_FLAG=-DBUILD_ROS:bool=off
YARP_FLAG=-DBUILD_YARP:bool=off
FLAGS=$(ROS_FLAG) $(YARP_FLAG) -DBUILD_$(BACKEND):bool=on

MODULENAME=RandomModule

all: build
	@echo $(ROS_PACKAGE_PATH)
	@mkdir -p build
	cd build && cmake $(CMAKE_FLAGS) .. $(FLAGS)
	cd build && make

build: local.mk idl/$(MODULENAME).idl
	cd scripts && ./build.sh

clean:
	cd build && make clean
