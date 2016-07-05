# IIC-ACEBFA

Trying to build an Automatic Complexity Evalutator By Function Aproximation, one step at a time.

[![Build Status](https://travis-ci.org/Zialus/IIC-ACEBFA.svg?branch=master)](https://travis-ci.org/Zialus/IIC-ACEBFA)

## Instructions

### Requirements

- gengetopt
- gnuplot

If you are on Ubuntu running the following command works fine

``` bash
sudo apt-get install gengetopt gnuplot
```

### How To Build

``` bash
./configure && make
```

### How To Use

``` bash
./the_thing_that_does_the_thing.sh <ficheiro.in> <ficheiro.out> <app.c>
```

- `<ficheiro.in>` - file that describes the various inputs
- `<ficheiro.out>` - file that describes the various corresponding outputs
- `<app.c>` - any C program
