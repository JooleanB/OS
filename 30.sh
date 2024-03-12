#!/bin/bash

if [[ $# -lt 1 ]]; then
	echo "Numar insuficient de argumente."
	exit 1
fi

nr=1
while [[ $nr -le $# ]]
do
	read -p "Introduceti primul cuvant: " prim
	read -p "Introduceti al2lea cuvant: " second
	rez=$(file "${!nr}" | grep -i 'text' | wc -l)
	if [[ $rez -eq 1 ]]; then
		echo "Fisier: ${!nr}"
		nr_vocale=$(cat "${!nr}" | grep -o '[aeiou]' | wc -l)
		nr_consoane=$(cat "${!nr}" | grep -i -o '[qwrtypsdfghjklzxcvbnm]' | wc -l)
		echo "Vocale/Consoane: $nr_vocale/$nr_consoane"
		indice=1
		nr_linii=$(cat "${!nr}" | wc -l)
		temporar="temporar.txt"
		touch "$temporar"
		nr_linie=1
		linii=$(cat "${!nr}")
		IFS=$'\n'
		for linie in $linii
		do
			verif=$(($nr_linie%2))
			if [[ $verif -eq 0 ]]; then
				output=$(echo "$linie" | sed "s/$prim/$second/")
				echo "$output"
				echo "$output" >> "$temporar"
			else
				echo "$linie" >> "$temporar"
			fi
			((nr_linie++))
		done
		mv "$temporar" "${!nr}"
	fi
	((nr++))
done
