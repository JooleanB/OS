#!/bin/bash

nr=2
while [[ $nr -le $# ]]
do
	if [[ ! -d "${!nr}" ]];then
		echo "NU ESTE DIRECTOR"
	else
		fisiere=$(find "${!nr}" -type f)
		for fisier in $fisiere
		do
			size=$( du -b "$fisier" | awk '{print $1}')
			if [[ "$fisier" = "${!nr}/$1" && "$size" -eq 0 ]];then
				echo "${!nr}"
			fi
		done
	fi
	((nr++))
done
