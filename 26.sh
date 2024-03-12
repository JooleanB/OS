#!/bin/bash

if [[ $# -ne 1 ]]; then
	echo "nu ati dat argument"
	exit 1
fi

while true
do
	read nr
	if [[ $nr -eq 0 ]]; then
		echo "s-a citit 0"
		break
	fi
	read filename
	touch "$filename"
	string=""
	linii=$(cat $1 | head -"$nr")
	IFS=$'\n'
	for linie in $linii
	do
		string+="$linie"
		string+=" "
	done
	echo "$string" > "$filename"
done
