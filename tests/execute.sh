#!/bin/bash

for input in *.c
do
  output=$(echo -en "$input" | sed s/\.c$//)
  echo -en "Running $input...\n"
  gcc -o $output $input -Wall -ansi -pedantic
  ../ANALYZE --exec $output > /dev/null
#  ../ANALYZE --exec $output
  rm -f "$output"
  echo -en "\n"
done
