BUILD := common

CC = gcc
CFLAGS = -Wall

memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) memgrind.o mymalloc.o -o memgrind

# For debugging
debug: CFLAGS = -Wall -g -fsanitize=address,undefined -D DEBUG=1
debug: memgrind

# Implicit rules for memgrind.o and mymalloc.o have them depend on .c files
memgrind.o: mymalloc.h
mymalloc.o: mymalloc.h

clean:
	rm -f a.out memgrind *.o


