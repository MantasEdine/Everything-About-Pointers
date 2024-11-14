CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

# Source files
SRCS = pointers.c utils.c heap.c perfect_memory_allocation.c
OBJS = $(SRCS:.c=.o)

# Executable names
PROG = prog
PROG2 = prog2
PROG3 = prog3
all: $(PROG) $(PROG2)

$(PROG): pointers.o utils.o
	$(CC) $(CFLAGS) pointers.o utils.o -o $(PROG)

$(PROG3): perfect_memory_allocation.o
	$(CC) $(CFLAGS) perfect_memory_allocation.o -o $(PROG3)
$(PROG2): heap.o
	$(CC) $(CFLAGS) heap.o -o $(PROG2)

pointers.o: pointers.c
	$(CC) $(CFLAGS) -c pointers.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c
perfect_memory_allocation.o: perfect_memory_allocation.c
	$(CC) $(CFLAGS) -c perfect_memory_allocation.c

# Simple test target to run the programs
test: $(PROG) $(PROG2) $(PROG3)
	./$(PROG)
	./$(PROG2)
	./$(PROG3)

clean:
	rm -rf *.o $(PROG) $(PROG2)