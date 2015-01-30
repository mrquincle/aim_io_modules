#!/bin/bash

. ../local.sh
. ../local.mk

backend=$2

# Do not echo here, it will end up in the generated file
#@echo omniidl -p${RUR_BACKENDS} -b${backend} "$1"
omniidl -p${RUR_BACKENDS} -b${backend} "$1"

