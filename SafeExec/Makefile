all:
	gcc -o os-detect os-detect.c -Wall -ansi -pedantic
	g++ -c main.cpp -Wall -ansi -pedantic
	g++ -c error.cpp -Wall -ansi -pedantic
	g++ -c safe.cpp -Wall -ansi -pedantic
	g++ -lpthread -c -DLINUX_HACK -D_DEFAULT_SOURCE safeexec.cpp -Wall -ansi -pedantic
	g++ -lpthread -o safeexec error.o safeexec.o safe.o main.o -Wall -ansi -pedantic

clean:
	rm -rf *.o os-detect safeexec
