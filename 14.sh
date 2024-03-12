#!/bin/bash
if [[ $# -ne 1 ]]; then
	echo "NU ATI DAT UN ARGUMENT"
	exit 1
fi
if [[ ! -d $1 ]]; then
	echo "ARGUMENTUL NU ESTE UN DIRECTOR"
	exit 1
fi
suma=0
rez=$(find $1 -type f)
for f in $rez
do
	size=$(du -b "$f" | awk '{print $1}')
	suma=$((suma+size))
done
echo "$suma"
