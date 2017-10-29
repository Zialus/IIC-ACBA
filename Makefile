# Compiler to use
CC=g++

# Executable name
EXEC_NAME=ANALYZE

# Flags Stuff
CFLAGS=-std=c++11 -Wall -Wextra -pedantic -D_DEFAULT_SOURCE -g -Wno-write-strings -Wno-sign-compare
#CFLAGS=-std=c++11 -Wall -Wextra -pedantic -D_DEFAULT_SOURCE

# Other Exec Stuff
OTHER_EXEC_NAME=FUNCTION_ANALYZE
OTHER_EXEC_FLAGS=-std=c++11 -Wall -Wextra -pedantic -g -Wno-write-strings
#OTHER_EXEC_FLAGS=-std=c++11 -Wall -Wextra -pedantic

# Extra config
LDFLAGS=-lpthread
SAFEDIR=SafeExec/
OSDETECT=-DLINUX_HACK
PARSERDIR=Parser/

SRC = analyzer.cpp    \
	$(SAFEDIR)error.cpp \
	$(SAFEDIR)safe.cpp \
	$(PARSERDIR)cmdline.c \

OBJ = $(SRC:.c=.o)

PSR = $(PARSERDIR)cmdline.h  \
	  $(PARSERDIR)cmdline.c

all: $(EXEC_NAME) $(OTHER_EXEC_NAME)

$(OTHER_EXEC_NAME): doFunctions.cpp applyfunction.cpp pearson.cpp
	$(CC) $(OTHER_EXEC_FLAGS) doFunctions.cpp applyfunction.cpp pearson.cpp -o $(OTHER_EXEC_NAME)

$(EXEC_NAME): $(PSR) $(OBJ) $(SAFEDIR)safeexec.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXEC_NAME) $(OBJ) $(SAFEDIR)safeexec.o

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $+ -o $@

$(SAFEDIR)%.o: $(SAFEDIR)%.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c $+ $(OSDETECT) -o $@

$(PSR): $(PARSERDIR)cmdline.ggo
	gengetopt --input=$(PARSERDIR)cmdline.ggo --include-getopt --output-dir=$(PARSERDIR)

clean:
	rm -rf *.o $(SAFEDIR)*.o $(PARSERDIR)*.o $(PSR) $(EXEC_NAME) $(OTHER_EXEC_NAME)

test: test1 test2 test3 test4

test1:
	@echo ""
	@echo ""
	@echo "--------------------------------> TEST 1 <------------------------------------"
	@echo ""
	@echo ""
	sudo ./the_thing_that_does_the_thing.sh ficheiro.in ficheiro.out apps_to_test/b_25.cpp
test2:
	@echo ""
	@echo ""
	@echo "--------------------------------> TEST 2 <------------------------------------"
	@echo ""
	@echo ""
	sudo ./the_thing_that_does_the_thing.sh ficheiro.in ficheiro.out apps_to_test/b_75.cpp
test3:
	@echo ""
	@echo ""
	@echo "--------------------------------> TEST 3 <------------------------------------"
	@echo ""
	@echo ""
	sudo ./the_thing_that_does_the_thing.sh ficheiro.in ficheiro.out apps_to_test/b_greedy.cpp
test4:
	@echo ""
	@echo ""
	@echo "--------------------------------> TEST 4 <------------------------------------"
	@echo ""
	@echo ""
	sudo ./the_thing_that_does_the_thing.sh ficheiro.in ficheiro.out apps_to_test/good_solution_for_b.cpp
