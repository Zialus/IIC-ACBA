#!/bin/bash

FILE="ficheiro.out"

if [ ! -f $FILE ];
then

	touch $FILE
	for i in Output/b.out?? ;
	do head -n 1 "$i" | cut -d' ' -f1 >> $FILE;
	done

else

echo "You shouldn't do that!"

fi