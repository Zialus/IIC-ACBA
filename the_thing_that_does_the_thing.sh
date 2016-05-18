#!/bin/bash

# Store array of args
args=("$@")
SOURCE="${args[2]}"

# Compiler flags stuff
CC=g++
CFLAGS="-Wall -ansi -pedantic"

PROGRAM=app

echo "Compiling User Code"
echo "$CC $CFLAGS $SOURCE -o $PROGRAM"
$CC $CFLAGS $SOURCE -o $PROGRAM
echo "Done"

# sleep 10

if [ ! -d ./Results ]; then mkdir Results/; fi

DATE=$(date +"%F_%H-%M-%S")

FILETIME=Results/tempo"$DATE".out
FILEMEM=Results/memory"$DATE".out
ANSWERSOUT=Results/answers"$DATE".out

touch "$FILETIME"
chmod 666 "$FILETIME"
echo "#X   Y" > "$FILETIME"

touch "$FILEMEM"
chmod 666 "$FILEMEM"
echo "#X   Y" > "$FILEMEM"

touch "$ANSWERSOUT"
chmod 666 "$ANSWERSOUT"

i=1;

while IFS=' ' read -r n fin fout; do

	echo ".................................I'm ON THE BASH SCRIPT!!.........................................."

    echo "....................Text read from file $i : $n | $fin | $fout ............................"

	echo ""

    echo "I'm gonna run the following command:"
    echo "./ANALYZE -n $n -i $fin -o $fout --answers $ANSWERSOUT -p $PROGRAM --fileout_time $FILETIME --fileout_mem $FILEMEM"

	# sleep 10

    ./ANALYZE -n "$n" -i "$fin" -o "$fout" --answers "$ANSWERSOUT" -p "$PROGRAM" --fileout_time "$FILETIME" --fileout_mem "$FILEMEM"

    echo "........................Command has finished running......................................."

    ((i++));

    echo "...............................Lets Go Again..............................................."

done < <(paste -d ' ' "$1" "$2")


echo "Gnuploting"
gnuplot -p -e "set terminal pngcairo size 1000,700 enhanced font 'Verdana,10'; \
				set output '$FILETIME.png' ; \
				plot '$FILETIME' with linespoints"

gnuplot -p -e "set terminal pngcairo size 1000,700 enhanced font 'Verdana,10'; \
				set output '$FILEMEM.png' ; \
				plot '$FILEMEM' with linespoints"
echo "Done"

echo "Do the Pearson thing"
./FUNCTION_ANALYZE "$FILETIME"
echo "DONE!!"

echo ""
echo "--------------"
