#!/bin/bash

nr=1
while [[ $nr -le $# ]]
do
	if [[ -f "${!nr}" ]]; then
		echo "${!nr}"
		cat "${!nr}" | wc -l
		cat "${!nr}" | wc -c
	fi
	if [[ -d "${!nr}" ]]; then
		echo "${!nr}"
		rez=$(find "${!nr}" -type f| wc -l)
		echo "$rez"
	fi
	((nr++))
done
