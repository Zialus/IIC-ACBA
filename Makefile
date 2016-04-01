# Executable name
EXEC_NAME=ANALYZE

# Compiler to use
CC=gcc

# More options Stuff
CFLAGS=-Wall -ansi -pedantic -D_DEFAULT_SOURCE
LDFLAGS=-lrt -lpthread -pthread
SAFEDIR=SafeExec/
OSDETECT=-DLINUX_HACK

SRC = analyzer.c    \
	$(SAFEDIR)error.c \
	$(SAFEDIR)safe.c \

OBJ =  $(SRC:.c=.o)


all: $(EXEC_NAME)
	
$(EXEC_NAME): $(OBJ) $(SAFEDIR)safeexec.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXEC_NAME) $(OBJ) $(SAFEDIR)safeexec.o

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $+

$(SAFEDIR)safeexec.o: $(SAFEDIR)safeexec.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SAFEDIR)safeexec.c $(OSDETECT) -o $(SAFEDIR)safeexec.o

clean:
	rm -rf *.o $(SAFEDIR)*.o $(EXEC_NAME)

test:
	cd tests && sudo sh execute.sh
