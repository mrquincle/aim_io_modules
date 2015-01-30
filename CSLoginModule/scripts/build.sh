#!/bin/bash

# Check if we have at least the backend as argument
if [[ "$1" == "" ]]
then
	echo "No args supplied! Use backend as argument"
	exit 1
fi

backend=$1
backend_path=$2

. ../local.sh

echo "We will use backend \"$backend\""

IDL_FILE="../idl/CSLoginModule.idl"
RESULT="../inc/CSLoginModule.h"

./run.sh "${IDL_FILE}" "${backend}" "${backend_path}" > "${RESULT}" 


