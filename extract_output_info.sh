#!/bin/bash

FILE="ficheiro.out"

if [[ ! -f ${FILE} ]]; then
	touch ${FILE}
	for i in Output/b.out?? ; do
	    echo "$i" >> ${FILE}
	done
else
    echo "You shouldn't do that!"
fi
