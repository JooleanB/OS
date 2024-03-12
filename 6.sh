#!/bin/bash
nr=1
if [[ $# -eq 1 ]]; then
	echo "NU EXISTA ARGUMENTE"
	exit 1
fi

while [[ $nr -le $# ]]
do
	if [ ! -f "${!nr}" ]; then
		echo "ARGUMENTUL ${!nr} nu este un fisier"
		exit 1
	fi
	prima_linie=$(head -n 1 "${!nr}")
	nr_cuvinte=$(echo "${!nr}" | wc -w)
	size=$(stat -c "%s" "${!nr}")
	echo "FISIERUL : ${!nr}"
	echo "NR CUVINTE : $nr_cuvinte"
	echo "SIZE : $size"  
	((nr++))
done
