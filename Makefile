# Executable name
EXEC_NAME=ANALYZE

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

all: .PHONY $(EXEC_NAME)

.PHONY:
	cd Parser && gengetopt --input=myApp.cmdline --include-getopt
	
$(EXEC_NAME): $(PARSER) $(OBJ) $(SAFEDIR)safeexec.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXEC_NAME) $(OBJ) $(SAFEDIR)safeexec.o

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $+

$(SAFEDIR)safeexec.o: $(SAFEDIR)safeexec.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SAFEDIR)safeexec.c $(OSDETECT) -o $(SAFEDIR)safeexec.o

clean:
	rm -rf *.o $(SAFEDIR)*.o $(EXEC_NAME)

test:
	sudo ./the_thing_that_does_the_thing.sh ficheiro.in
