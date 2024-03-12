#!/bin/bash

if [[ $# -lt 1 ]]; then
	echo "NU EXISTA ARGUMENT"
	exit 1
fi

if [[ -d $1 ]]; then
	rez=$( find $1 -type f |grep '\.c$' | wc -l )
	echo "NUMARUL DE FISIERE ESTE : $rez"
else
	echo "ARGUMENTUL NU E DIRECTOR"
fi
