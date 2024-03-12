#!/bin/bash

rez=$(find -name "*.c")
count=0
for f in $rez
do
	line_count=$(cat "$f" | wc -l)
	if [[ $line_count -ge 500 ]]; then
		echo "$f"
		((count=count+1))
	fi
	if [[ $count -eq 2 ]]; then
		echo "MUIE"
		break
	fi
done

