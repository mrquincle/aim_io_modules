#!/bin/bash

. ../local.sh
. ../local.mk

# Use a script argument
backend=${BACKEND,,}
echo "We will use backend \"$backend\""

IDL_FILE="../idl/RandomModule.idl"
RESULT="../inc/RandomModule.h"

./run.sh "${IDL_FILE}" "$backend" > "${RESULT}" 


