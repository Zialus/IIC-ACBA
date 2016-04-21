#!/bin/bash

#temporary thing before the thing
 CC=g++
 CFLAGS="-Wall -ansi -pedantic"
# $CC $CFLAGS short.c -o  PROGRAMA_1
# $CC $CFLAGS medium.c -o PROGRAMA_2
# $CC $CFLAGS long.c -o   PROGRAMA_3


PROGRAM=bapp

$CC $CFLAGS good_solution_for_b.cpp -o PROGRAM

i=1;

if [ ! -d ./Results ]; then mkdir Results/; fi

DATE=$(date +"%F_%H-%M-%S")

FILETIME=Results/tempo"$DATE".out
FILEMEM=Results/memory"$DATE".out


touch "$FILETIME"
chmod 666 "$FILETIME"
echo "#X   Y" > "$FILETIME"

touch "$FILEMEM"
chmod 666 "$FILEMEM"
echo "#X   Y" > "$FILEMEM"

while IFS=' ' read -r n f; do

	echo "............................I'm ON THE BASH SCRIPT!!............................"

    echo "....................Text read from file $i : $n | $f............................"

    echo "I'm gonna run the following command: ./ANALYZE -n $n -i $f -p mergesort -o $FILETIME"
    ./ANALYZE -n "$n" -i "$f" -p "$PROGRAM" -o "$FILETIME"

    echo "........................Command has finished running............................"

    ((i++));

    echo "...............................Let's Go Again..................................."

done < "$1"

gnuplot -p -e "set terminal pngcairo size 1000,700 enhanced font 'Verdana,10'; \
				set output '$FILETIME.png' ; \
				plot '$FILETIME' with linespoints"


 # country=$(echo "$line" | cut -d' ' -f1)
 #  if [ "US" = "$country" ]; then
 #        USCOUNTER=$(expr $USCOUNTER + 1)
 #        echo "US counter $USCOUNTER"
 #  fi