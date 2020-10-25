CC = gcc
#CFLAGS = -Wall
CFLAGS = -Wall -fsanitize=address,undefined -g

memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) memgrind.o mymalloc.o -o memgrind

# Implicit rules for memgrind.o and mymalloc.o have them depend on .c files
memgrind.o: mymalloc.h
mymalloc.o: mymalloc.h

clean:
	rm -f a.out memgrind *.o


