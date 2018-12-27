#!/bin/bash

folder=BUNCHOFSUBMISSIONSN

for i in ${folder}/*/*;
do
	echo "I'm gonna execute: sudo ./the_thing_that_does_the_thing.sh ficheiro.in ficheiro.out ${i}"
	sudo ./the_thing_that_does_the_thing.sh ficheiro.in ficheiro.out ${i}
done
