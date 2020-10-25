BUILD := common

CC = gcc
# Regular
#CFLAGS = -Wall
# Debug
CFLAGS = -g -Wall -fsanitize=address,undefined -D DEBUG=1

memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) memgrind.o mymalloc.o -o memgrind

debug: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) memgrind.o mymalloc.o -o memgrind


# Implicit rules for memgrind.o and mymalloc.o have them depend on .c files
memgrind.o: mymalloc.h
mymalloc.o: mymalloc.h

clean:
	rm -f a.out memgrind *.o


