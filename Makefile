# Executable name
EXEC_NAME=ANALYZE

# Extra Stuff
OTHER_EXEC_NAME=FUNCTION_ANALYZE
OTHERFLAGS=-std=c++11 -g -Wno-write-strings

# Compiler to use
CC=g++

# More options Stuff
CFLAGS=-Wall -pedantic -D_DEFAULT_SOURCE -Wno-write-strings -Wno-sign-compare -g
#CFLAGS=-Wall -pedantic -D_DEFAULT_SOURCE
LDFLAGS=-lrt -lpthread -pthread
SAFEDIR=SafeExec/
OSDETECT=-DLINUX_HACK
PARSERDIR=Parser/

SRC = analyzer.c      \
	$(SAFEDIR)error.c \
	$(SAFEDIR)safe.c  \
	$(PARSERDIR)cmdline.c \

OBJ =  $(SRC:.c=.o)

PSR = $(PARSERDIR)cmdline.h  \
	  $(PARSERDIR)cmdline.c

all: $(EXEC_NAME) $(OTHER_EXEC_NAME)

$(OTHER_EXEC_NAME):
	$(CC) $(OTHERFLAGS) doFunctions.c applyfunction.c pearson.c -o $(OTHER_EXEC_NAME)

$(EXEC_NAME): $(PSR) $(OBJ) $(SAFEDIR)safeexec.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXEC_NAME) $(OBJ) $(SAFEDIR)safeexec.o

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $+

$(SAFEDIR)safeexec.o: $(SAFEDIR)safeexec.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SAFEDIR)safeexec.c $(OSDETECT) -o $(SAFEDIR)safeexec.o

$(PSR): $(PARSERDIR)cmdline.ggo
	gengetopt --input=$(PARSERDIR)cmdline.ggo --include-getopt --output-dir=$(PARSERDIR)

clean:
	rm -rf *.o $(SAFEDIR)*.o $(EXEC_NAME) $(PSR) $(OTHER_EXEC_NAME)

test:
	sudo ./the_thing_that_does_the_thing.sh ficheiro.in ficheiro.out apps_to_test/b_75.cpp
