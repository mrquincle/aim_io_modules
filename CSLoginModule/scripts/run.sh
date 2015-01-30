#!/bin/bash

# Check if we have at least the backend as argument
if [[ "$1" == "" ]]
then
	echo "No args supplied! Use idl file + backend as argument"
	exit 1
fi

# set paths basically
. ../local.sh

idl_file=$1
backend=$2
backend_path=$3

# Do not echo here, it will end up in the generated file
omniidl -p${backend_path} -b${backend} "${idl_file}"
