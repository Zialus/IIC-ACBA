#!/bin/bash

FILE="ficheiro.in"

if [ ! -f $FILE ];
then

	touch $FILE
	for i in Input/b.in?? ;
	do echo "$( head -n 1 "$i" | cut -d' ' -f1 )  $i">> $FILE;
	done

else
echo "You shouldn't do that!"
fi