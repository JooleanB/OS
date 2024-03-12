#!/bin/bash
if [[ $# -ne 3 ]]; then
	echo "NU ATI DAT UN NUMAR CORECT DE ARGUMENTE"
	exit 1
fi

if [[ ! -d $1 ]]; then
	echo "PRIMUL ARGUMENT NU E UN DIRECTOR"
	exit 1
fi

verificare=$(echo $2 | grep '[1-9][0-9]*' | wc -l)
if [[ $verificare -ne 1 ]]; then
	echo "AL2LEA ARGUMENT NU ESTE NUMAR"
	exit 1
fi
rez=$(ls $1 -l | awk '{print $3,$5,$9}')
IFS=$'\n'
for linie in $rez
do
	owner=$(echo "$linie" | awk '{print $1}')
	size=$(echo "$linie" | awk '{print $2}')
	size=$((size))
	nume_fisier=$(echo "$linie" | awk '{print $3}')
	echo "$nume_fisier"
	if [[ "$owner"=="$3" && "$2" -lt "$size" ]]; then
		echo "TOP 10 CUVINTE PENTRU $nume_fisier"
		nr_aparitii=$(cat "$1/$nume_fisier" | grep -o -i '\b[aeiou][a-z]*\b' | sort | uniq -c)
		rez=$(echo "$nr_aparitii" | sort -k2 -n -r | head -10)
		echo "$rez"	
	fi
done
