CC = gcc
CFLAGS = -Wall

all: program

program: Palindrome.o lib_file.a
	$(CC) $(CFLAGS) $< -o $@ -L. -l_file

Palindrome.o: Palindrome.c lib_palindrome.h
	$(CC) $(CFLAGS) -c $< -o $@

lib_file.a:  lib_palindrome.o lib_rev.o
	ar rcs $@ $^

lib_palindrome.o: lib_palindrome.c lib_palindrome.h
	$(CC) $(CFLAGS) -c $< -o $@
	
lib_rev.o: lib_rev.c lib_palindrome.h
	$(CC) $(CFLAGS) -c $< -o $@
