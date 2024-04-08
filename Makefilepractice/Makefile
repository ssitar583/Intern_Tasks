CC = gcc
CFLAGS = -Wall

all: program

program: Palindrome.o dec.o method.o
	$(CC) $(CFLAGS) $^ -o $@

Palindrome.o: Palindrome.c
	$(CC) $(CFLAGS) -c $< -o $@

dec.o: dec.c
	$(CC) $(CFLAGS) -c $< -o $@

method.o: method.c
	$(CC) $(CFLAGS) -c $< -o $@

