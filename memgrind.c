#include <stdio.h>
#include "mymalloc.h"

#ifndef DEBUG
#define DEBUG 0
#endif


int main(int argc, char *argv[]) {

	malloc(0);
	// Test case A
	for (int i = 0; i < 1; i++) {
		char *temp = (char*) malloc(1);
		int *temp2 = (int*) malloc(sizeof(int));
		free((void *) temp);
		free((void *) temp2);
	}

	return 0;
}
