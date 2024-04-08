CC = gcc
CFLAGS = -Wall
LDFLAGS = -L. -Wl,-rpath,/home/soundaryaa/Documents/Dynamic

all: program

program: Palindrome.o lib_all.so
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) -l_all

Palindrome.o: Palindrome.c lib_palindrome.h
	$(CC) $(CFLAGS) -c $< -o $@

lib_all.so: lib_palindrome.o lib_rev.o
	$(CC) $(CFLAGS) -shared -o $@ $^

lib_palindrome.o: lib_palindrome.c lib_palindrome.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

lib_rev.o: lib_rev.c lib_palindrome.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

run: program
	@LD_LIBRARY_PATH=. ./program

clean:
	rm -f program *.o *.so

