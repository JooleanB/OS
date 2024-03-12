#!/bin/bash

if [[ $# -lt 1 ]];then
	echo "Numar insuficient de argumente."
	exit 1
fi

cuvant=""
nr=1
while [[ $nr -le $# ]]
do

	while true
	do
		read -p "Introduceti un cuvant sau stop: " cuvant
		if [[ "$cuvant" == "stop" ]]; then
			echo "S-A CITIT stop"
			break
		fi
		if [[ ! -f "${!nr}" ]]; then
			echo "Fisierul dat nu e de tip text." 
		else
			verif=$(file "${!nr}" | grep -i "text" | wc -l)
			if [[ $verif -ne 0 ]]; then
				echo "Fisier: ${!nr}"
				nr_linii=$(cat "${!nr}" | wc -l)
				echo "Total linii: $nr_linii"
				par=$((nr_linii%2))
				if [[ $par -eq 0 ]];then
					ultima_linie=$(cat "${!nr}" | grep "$cuvant" | tail -1)
					echo "$ultima_linie" >> "${!nr}"
					echo "Am adaugat o linie"
				fi
			else
				echo "Fisierul dat nu e de tip text."
			fi
		fi
	done
	((nr++))
done
