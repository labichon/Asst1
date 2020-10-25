#include <stdio.h>
#include "mymalloc.h"

#ifndef DEBUG
#define DEBUG 0
#endif


int main(int argc, char *argv[]) {

	// Allocate 0 bytes error
	malloc(0);
	// Free non-pointer error
	int i = 1;
	free((int *) i);
	// Free pointer not allocated by malloc
	int *p = (char *)malloc(100);
        free(p+10);
	// Part 2
	int *x;
	free(x);	
	// Free same pointer
	free(p);
	free(p);

	// Test case A
	for (int i = 0; i < 1; i++) {
		char *temp = (char*) malloc(1);
		int *temp2 = (int*) malloc(sizeof(int));
		free((void *) temp);
		free(temp2);
	}

	return 0;
}
