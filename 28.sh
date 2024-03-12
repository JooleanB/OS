#!/bin/bash

if [[ $# -ne 1 ]];then
	echo "nu este director"
	exit 1
fi

rez=$(find "$1" -type f)
for fisier in $rez
do
	verif=$(echo "$fisier" | grep '.c$' | wc -l)
	if [[ $verif -eq 1 ]];then
		echo "$fisier are extensia .c"
	else
		nr_linii=$(cat "$fisier" | wc -l)
		echo "$fisier nu are extensia .c si are $nr_linii linii"
	fi
done
