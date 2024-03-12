#!/bin/bash

nr=1
IFS=$'\n'
while [[ $nr -le $# ]]
do
	if [[ -f "${!nr}" ]]; then
		rez=$(echo "${!nr}" | grep '\.c$' | wc -l)
		if [[ $rez -eq 1 ]]; then
			rez=$(cat "${!nr}" | grep "#include")
			echo "$rez"
			for linie in $rez
			do
				echo "$linie" >> "fisier.txt"
			done
		fi
	fi
	((nr++))
done
