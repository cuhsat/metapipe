CC=gcc
CFLAGS=-std=gnu99 -pedantic -Wall -Werror
SOURCES=metapipe.c
EXECUTABLE=metapipe

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

install:
	cp $(EXECUTABLE) /usr/bin/
	gzip -c $(EXECUTABLE).man > /usr/share/man/man1/$(EXECUTABLE).1.gz

clean:
	rm $(EXECUTABLE)
