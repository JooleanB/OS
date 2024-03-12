#!/bin/bash

IFS=$'\n'
nr_linii=$(wc -l "text.txt" | awk '{print $1}')
nr=0
rez=$(cat "text.txt")
string=""
for linie in $rez
do
	((nr++))
	string+="$linie"
	string+="@scs.ubbcluj.ro"
	if [[ $nr -lt $nr_linii ]]; then
		string+=","
	fi
done
echo "$string"
