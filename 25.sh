#!/bin/bash

if [[ $# -lt 2 ]]; then
	echo "NU ATI DAT SUFICIENTE ARGUMENTE"
	exit 1
fi
IFS=$'\n'
nr=2
while [[ $nr -le $# ]]
do
	if [[ ! -d "${!nr}" ]]; then
		echo "${!nr} nu este director"
		exit 1
	else
		permisiuni_nume=$(ls "${!nr}" -l | awk '{print $1,$9}')
		for permisiune in $permisiuni_nume
		do
			perm=$(echo "$permisiune" | awk '{print $1}')
			nume_fisier=$(echo "$permisiune" | awk '{print $2}')
			if [[ "$perm" == "$1" ]]; then
				echo "$perm"
				echo "$1"
				echo " "		
				cat "${!nr}/$nume_fisier" >  "${!nr}/$nume_fisier.bak"
				chmod 400 "${!nr}/$nume_fisier.bak"
				echo "PERMISIUNI $perm"
				echo "DIRECTOR ${!nr}"
				echo  "FISIER ${!nr}/$nume_fisier"
				echo "COPIE ${!nr}/$nume_fisier.bak"
				echo ''
			fi
		done
	fi
	((nr++))
done
