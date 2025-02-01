CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -D_POSIX_C_SOURCE=200809L

all: main

main: main.o autocomplete.o
	$(CC) $(CFLAGS) -o main main.o autocomplete.o

main.o: main.c autocomplete.h
	$(CC) $(CFLAGS) -c main.c

autocomplete.o: autocomplete.c autocomplete.h
	$(CC) $(CFLAGS) -c autocomplete.c

clean:
	rm -f *.o main

