#!/bin/bash

read -r filenames

if [ -z "$filenames" ]; then
	echo "NO FILENAMES PROVIDED"
	exit 1
fi

for filename in $filenames
do
 	if [ ! -f "$filename" ]; then
		echo "$filename IS NOT A FILENAME"
		exit 1
	fi
	first_line=$(head -n 1 "$filename")
	word_count=$(echo "$first_line" | wc -w)
	size=$(stat -c "%s" "$filename")
	echo "FILE : $filename"
	echo "NR WORDS : $word_count"
	echo "SIZE : $size"
done
