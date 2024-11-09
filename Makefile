CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

prog: pointers.o utils.o
	$(CC) $(CFLAGS) pointers.o utils.o -o prog

prog2: heap.o
	$(CC) $(CFLAGS) heap.o -o prog2

pointers.o: pointers.c
	$(CC) $(CFLAGS) -c pointers.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c

clean:
	rm -rf *.o prog prog2
