CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

# Source files
SRCS = pointers.c utils.c heap.c
OBJS = $(SRCS:.c=.o)

# Executable names
PROG = prog
PROG2 = prog2

all: $(PROG) $(PROG2)

$(PROG): pointers.o utils.o
	$(CC) $(CFLAGS) pointers.o utils.o -o $(PROG)

$(PROG2): heap.o
	$(CC) $(CFLAGS) heap.o -o $(PROG2)

pointers.o: pointers.c
	$(CC) $(CFLAGS) -c pointers.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c

# Simple test target to run the programs
test: $(PROG) $(PROG2)
	./$(PROG)
	./$(PROG2)

clean:
	rm -rf *.o $(PROG) $(PROG2)