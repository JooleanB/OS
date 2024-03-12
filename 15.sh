#!/bin/bash

filename=""
while true
do
	echo "INTRODUCETI UN NUME DE FISIER SAU STOP"
	read filename
	if [[ "$filename" = "stop" ]]; then
		exit 0
	fi
	if [[ ! -f "$filename" ]]; then
		echo "NU ESTE FISIER"
	else
		rez=$(head -1 "$filename" | wc -w)
		echo "$rez"
	fi
done
