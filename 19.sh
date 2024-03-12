#!/bin/bash

if [[ $# -ne 1 ]]; then
	echo "NU ATI DAT DOAR UN ARGUMENT"
	exit 1
fi

if [[ ! -d $1 ]]; then
	echo "argumentul nu este director"
fi

rez=$(find "$1" -type f | awk -F/ '{print $NF}' | sort | uniq -c)
echo "$rez"
