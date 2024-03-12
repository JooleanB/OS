#!/bin/bash

rez=$(cat user.txt)
nr_linii=$(cat user.txt | wc -l)
string=""
nr=0
for user in $rez 
do
	((nr++))
	string+=${user}
	string+="@scs.ubbcluj.ro"
	if [[ $nr -lt  $nr_linii ]]; then
		string+=","
	fi
done
echo "$string"
