#!/bin/bash

FILE="ficheiro.in"
touch $FILE

for i in Input/b.in?? ;
do echo "$( head -n 1 "$i" | cut -d' ' -f1 )  $i">> $FILE;
done