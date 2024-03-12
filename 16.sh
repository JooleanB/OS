#!/bin/bash

rez=$(($#%2))
if [[ $rez -eq 1 || $# -lt 1 ]]; then
	echo "NU ATI DAT PERECHI DE ARGUMENTE"
	exit 1
fi
nr=1
while [[ $nr -le $# ]]
do
	fisier="${!nr}"
	if [[ ! -f "$fisier" ]]; then
		echo "$fisier NU ESTE FISIER"
		exit 1
	fi
	((nr++))
	cuvant="${!nr}"
	aparitii=$(cat "$fisier" | grep -o "\b$cuvant\b" | wc -l)
	if [[ $aparitii -eq 3 ]]; then
		echo "In $fisier cuvantul $cuvant apare de 3 ori"
	fi
	((nr++))	
done
