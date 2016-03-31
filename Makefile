# Executable name
EXEC_NAME=ANALYZE

# Compiler to use
CC=gcc

# More options Stuff
CFLAGS=-Wall -ansi -pedantic
LDFLAGS=-lrt -lpthread -pthread
SAFEDIR=SafeExec/
OSDETECT=-DLINUX_HACK

SRC =     \
	analyzer.c \
	$(SAFEDIR)error.c \
	$(SAFEDIR)safe.c \
	$(SAFEDIR)safeexec.c

OBJ =  $(SRC:.c=.o)

all: $(EXEC_NAME)
	
$(EXEC_NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXEC_NAME) $(OBJ)

analyzer.o: analyzer.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c analyzer.c

error.o: error.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SAFEDIR)error.c

safe.o: safe.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SAFEDIR)safe.c

safeexec.o: safeexec.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SAFEDIR)safeexec.c $(OSDETECT)

clean:
	rm -rf *.o $(SAFEDIR)*.o $(EXEC_NAME)

test:
	sh ../tests/execute.sh