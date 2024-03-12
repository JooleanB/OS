#!/bin/bash

rez=$(awk 'NR>1 {print $1}' ps.fake | sort | uniq)
for user in $rez
do
	linii_user=$(grep "$user" ps.fake)
	echo "$user"
	echo "$linii_user" | awk 'BEGIN {suma=0;nr=0} {suma+=$2; nr+=1} END {print suma/nr}'
done
