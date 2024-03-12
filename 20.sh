#!/bin/bash

if [[ $# -ne 1 ]]; then
	echo "nu ati dat doar un argument"
	exit 1
fi

if [[ ! -d $1 ]]; then
	echo "argumentul nu este un director"
	exit 1
fi
rez=$(find "$1" -type f | grep '\.c$')
#echo "$rez"
for i in $rez
do
	rm "$i"
done
 
rez=$(find "$1" -type f | sort)
echo "$rez"
