#!/bin/bash
if [[ $#%3 -ne 0 ]]; then
	echo "DOMNE NU ATI DAT TRIPLETE"
	exit 1
fi

nr=1
IFS=$'\n'
while [[ $nr -le $# ]] 
do
	if [[ ! -f "${!nr}" ]]; then
		echo "NU ESTE FISIER"
		exit 1
	fi
	fisier="${!nr}"
	((nr++))
	rez=$(echo "${!nr}" | grep '^[1-9][0-9]\+$' | wc -l)
	if [[ $rez -eq 1 ]]; then
		echo "NU ESTE NUMAR"
		exit 1
	fi
	numar="${!nr}"
	((nr++))
	cuvant="${!nr}"
	continut_fisier=$(cat "$fisier")
	for linie in $continut_fisier
	do
		aparitii=$(echo "$linie" | grep -o "$cuvant" | wc -l)
		#echo "$linie"
		#echo "$aparitii"
		#echo "$numar"
		if [[ $numar -eq $aparitii ]]; then
			echo "$linie"
		fi
	done
	((nr++))
done


