# Executable name
EXEC_NAME=ANALYZE

# Compiler to use
CC=gcc

CFLAGS=-Wall -ansi -pedantic
LDFLAGS=-lrt -lpthread -pthread
SAFEDIR=SafeExec/
OSDETECT=-DLINUX_HACK

all:
	$(CC) $(CFLAGS) -c $(SAFEDIR)error.c
	$(CC) $(CFLAGS) -c $(SAFEDIR)safe.c
#	$(CC) $(CFLAGS) $(SAFEDIR)os-detect.c -o os-detect
#	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SAFEDIR)safeexec.c `./os-detect`
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SAFEDIR)safeexec.c $(OSDETECT)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXEC_NAME) analyzer.c error.o safeexec.o safe.o

clean:
	rm -rf *.o os-detect $(EXEC_NAME)
