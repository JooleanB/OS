#/bin/bash

if [[ $# -ne 1 ]]; then
	echo "NU ATI DAT ARGUMENT"
	exit 1
fi
if [[ -d $1 ]]; then
	nr_linii=0
	rez=$(find $1 -type f | grep '\.c$')
	for f in $rez
	do
		n=$( cat "$f" | grep -v '^$' | wc -l )
		nr_linii=$(( nr_linii+n ))
	done
	echo "NR DE LINII ESTE : $nr_linii"
else
	echo "ARGUMENTUL NU ESTE UN DIRECTOR"
fi

