#!/bin/bash

nr=1
while [[ $nr -le $# ]]
do
	if [[ -f "${!nr}" ]]; then
		du -b "${!nr}" | awk '{print $1}'
	fi
	((nr++))
done | sort -r -n
