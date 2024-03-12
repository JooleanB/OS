#!/bin/bash
nr=0
linii=$(head -n "$1" "passwd.fake")
IFS=$'\n'
for linie in $linii
do
	echo "$linie" > "file_$nr"
	((nr++))
done
