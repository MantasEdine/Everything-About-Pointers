CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

prog: pointers.o utils.o
	$(CC) $(CFLAGS) pointers.o utils.o -o prog

pointers.o: pointers.c 
	$(CC) $(CFLAGS) -c pointers.c
utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c 
pointersChallenge.o: pointersChallenge.c 
	$(CC) $(CFLAGS) -c pointersChallenge.c 
clean:
	rm -rf *.o prog