#!/bin/bash


#temporary thing before the thing

CC=g++
CFLAGS="-Wall -ansi -pedantic"

$CC $CFLAGS short.c -o  PROGRAMA_1
$CC $CFLAGS medium.c -o PROGRAMA_2
$CC $CFLAGS long.c -o   PROGRAMA_3

i=1;

DATE=$(date +"%F_%H-%M-%S")

FILE=ficheiro"$DATE".out

touch "$FILE"
chmod 666 "$FILE"

while IFS=' ' read -r a b; do
    echo "Text read from file $i : $a | $b";

    echo "running the following command: ./ANALYZE -n $a -i $b -o $FILE"
    ./ANALYZE -n $a -i $b -o $FILE

    ((i++));
done < "$1"



 # country=$(echo "$line" | cut -d' ' -f1)
 #  if [ "US" = "$country" ]; then
 #        USCOUNTER=$(expr $USCOUNTER + 1)
 #        echo "US counter $USCOUNTER"
 #  fi