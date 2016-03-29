#!/bin/sh

echo "Starting Configuration..."

CC=gcc
CFLAGS="-Wall -ansi -pedantic"
SAFEDIR=SafeExec/

echo "Compiling OSDETECT..."

$CC $CFLAGS "$SAFEDIR"os-detect.c -o os-detect

echo "Running OSDETECT..."

OSDETECT=$(./os-detect)

echo "----------------"
echo "The result is:"
echo "$OSDETECT"
echo "----------------"

echo "Preparing Makefile..."

sed -e "s/%{OSDETECT}/$OSDETECT/" Makefile.in > Makefile

echo "configuration done!"