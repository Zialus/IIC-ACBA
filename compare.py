#!/usr/bin/env python

import sys

file1 = sys.argv[1]; file2 = sys.argv[2]
try:
    outfile = sys.argv[3]
except IndexError:
    outfile = None

def readfile(file):
    with open(file) as compare:
        return [item.replace("\n", "").split(" ") for item in compare.readlines()]

data1 = readfile(file1); data2 = readfile(file2)
mismatch = [index for (index,item) in enumerate(data1) if not (index,item) in enumerate(data2)]

if outfile != None:
        with open(outfile, "wt") as out:
            for line in mismatch:
                out.write(line+" has changed"+"\n")
else:
    for line in mismatch:
        print "example " + str(line) + " gives incorrect output"