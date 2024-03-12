#!/bin/bash

nume_fisiere=""
continut=""
while true
do
	read citit
	if [[ ! -f "$citit" ]]; then
		echo "NU ESTE FISIER"
	else
	nume_fisier+=" "
	nume_fisiere+="$citit"
	continut+=$(cat "$citit")
	nr=1
	nr_cuvinte_gasite=0
	while [[ $nr -le $# ]]
	do
		rez=$(echo "$continut" | grep "${!nr}" | wc -l)
		if [[ $rez -ne 0 ]]; then
			((nr_cuvinte_gasite++))
		fi
		((nr++))	
	done
	if [[ $nr_cuvinte_gasite -eq $# ]]; then
		break
	fi
	fi
done
