#!/bin/bash

. ../local.sh
. ../local.mk

# Use a script argument
backend=${BACKEND,,}
echo "We will use backend \"$backend\""

IDL_FILE="../idl/EmailModule.idl"
RESULT="../inc/EmailModule.h"

./run.sh "${IDL_FILE}" "$backend" > "${RESULT}" 


