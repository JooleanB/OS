#!/bin/bash

fisiere=$(find -type f | grep '.log$')
for fisier in $fisiere
do
	cat "$fisier" | sort > "sortat.txt"
	mv "sortat.txt" "$fisier"
done
