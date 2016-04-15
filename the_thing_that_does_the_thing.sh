#!/bin/bash


#temporary thing before the thing

CC=g++
CFLAGS="-Wall -ansi -pedantic"

$CC $CFLAGS short.c -o  PROGRAMA_1
$CC $CFLAGS medium.c -o PROGRAMA_2
$CC $CFLAGS long.c -o   PROGRAMA_3

i=1;

DATE=$(date +"%F_%H-%M-%S")

FILETIME=tempo"$DATE".out

touch "$FILETIME"
chmod 666 "$FILETIME"
echo "#X   Y" > "$FILETIME"

while IFS=' ' read -r n f; do
    echo "Text read from file $i : $n | $f";

    echo "running the following command: ./ANALYZE -n $n -i $f -p mergesort -o $FILETIME < $f"
    ./ANALYZE -n "$n" -i "$f" -p mergesort -o "$FILETIME" < "$f" > /dev/null

    ((i++));
done < "$1"



 # country=$(echo "$line" | cut -d' ' -f1)
 #  if [ "US" = "$country" ]; then
 #        USCOUNTER=$(expr $USCOUNTER + 1)
 #        echo "US counter $USCOUNTER"
 #  fi