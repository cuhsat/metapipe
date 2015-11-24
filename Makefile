CC=gcc
CFLAGS=-pedantic -ansi -std=c99 -Wall -Werror
SOURCES=metapipe.c
EXECUTABLE=metapipe

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

install:
	cp $(EXECUTABLE) /usr/bin/

clean:
	rm $(EXECUTABLE)
