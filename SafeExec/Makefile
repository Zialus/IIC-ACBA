all:
	gcc -c main.c -Wall -ansi -pedantic
	gcc -c error.c -Wall -ansi -pedantic
	gcc -c safe.c -Wall -ansi -pedantic
	gcc -o os-detect os-detect.c -Wall -ansi -pedantic
	gcc -lrt -lpthread -pthread -c safeexec.c -DLINUX_HACK -Wall -ansi -pedantic -D_DEFAULT_SOURCE
	gcc -lrt -lpthread -pthread -o safeexec error.o safeexec.o safe.o main.o -Wall -ansi -pedantic

clean:
	rm -rf *.o os-detect
