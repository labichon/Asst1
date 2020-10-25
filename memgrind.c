#include <stdio.h>
#include "mymalloc.h"

#ifndef DEBUG
#define DEBUG 0
#endif


int main(int argc, char *argv[]) {

	malloc(0);
	// Test case A
	for (int i = 0; i < 120; i++) {
		char *temp = (char*) malloc(1);
		//free(temp);
	}

	return 0;
}
