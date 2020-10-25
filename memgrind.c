#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mymalloc.h"

#ifndef DEBUG
#define DEBUG 0
#endif


int main(int argc, char *argv[]) {

/*
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
*/

	int i, j;
	int *testarray[1000];
	struct timeval begin, end;
	int timeA = 0;
       	int timeB = 0;
       	int timeC = 0;
      	int timeD = 0;
       	int timeE = 0;


	// Test Case A: Mallocing 1 byte then immediately freeing it
	// We loop through the workload 50 times
	for (i = 0; i < 50; i++) {
		gettimeofday(&begin, 0);
		// Mallocing and freeing 120 times
		for (j = 0; j < 120; j++){
			testarray[j] = (int *) malloc(1);
			free(testarray[j]);
			testarray[j] = NULL;
		}
		gettimeofday(&end, 0);
		timeA = timeA + ((end.tv_sec - begin.tv_sec)*1000000 + (end.tv_usec - begin.tv_usec));
	}



	// Test Case B: Mallocing 120 times, then freeing 120 times
	// We loop through the workload 50 times
	for (i = 0; i < 50; i++) {
		gettimeofday(&begin, 0);
		// 120 Mallocs
		for(j = 0; j < 120; j++) {
			testarray[j] = (int *) malloc(1);
		}
		// 120 Frees
		for(j = 0; j < 120; j++) {
			free(testarray[j]);
			testarray[j] = NULL;
		}
		gettimeofday(&end, 0);
		timeB = timeB + ((end.tv_sec - begin.tv_sec)*1000000 + (end.tv_usec - begin.tv_usec));;
	}
	
	// Test Case C: randomly choose between a 1 byte malloc() 
	// or free()ing one of the malloc()ed pointers
	// We loop through the workload 50 times
	for (i = 0; i < 50; i++) {
		gettimeofday(&begin, 0);
		int MallocCounter = 0;
		int numberOfMallocs = 0;
		int numberOfFrees = 0;
		srand(time(NULL));
		// if random is 0, then we malloc
		// if random is 1, then we free
		int random = rand() % 2;
		while (MallocCounter < 240) {
			// Making sure we don't allocate over 120 bytes of memory
			if ((numberOfMallocs < 120) && (random == 0)) {
				testarray[numberOfMallocs] = (int *) malloc(1);
				numberOfMallocs++;
				MallocCounter++;
			} else {
				// if nothing has been allocated, we must allocate
				// before freeing anything
				if(testarray[numberOfFrees] == NULL) {
					testarray[numberOfMallocs] = (int *) malloc(1);
                                	numberOfMallocs++;
                                	MallocCounter++;
				} else {
					free(testarray[numberOfFrees]);
					testarray[numberOfFrees] = NULL;
					numberOfFrees++;
				}
			}
			random = rand() % 2;
		}
		// Freeing the rest of the pointers
		for(j = numberOfFrees; j < 240; j++){
			free(testarray[j]);
			testarray[j] = NULL;
		}
		gettimeofday(&end, 0);	
		timeC = timeC + ((end.tv_sec - begin.tv_sec)*1000000 + (end.tv_usec - begin.tv_usec));
	}


	// Test Case D: allocating and freeing memory in a reverse order
	// We loop through the workload 50 times
	for (i = 0; i < 50; i++) {
		gettimeofday(&begin, 0);
		// Allocating backwards
                for (j = 100; j > 0; j--){
                        testarray[j] = (int *) malloc(1);
                }
		// Freeing backwards
		for (j = 100; j > 0; j--){
			free(testarray[j]);
			testarray[j] = NULL;
		}
                gettimeofday(&end, 0);
                timeD = timeD + ((end.tv_sec - begin.tv_sec)*1000000 + (end.tv_usec - begin.tv_usec));
	}

	
	// Test Case E: allocate 50 bytes of memory
	// then free every other entry, then reallocate
	// those entries, then free everything
	// We loop through the workload 50 times
	for (i = 0; i < 50; i++) {
		gettimeofday(&begin, 0);
		// Allocate 50 bytes normally
		for (j = 0; j < 50; j++) {
			testarray[j] = (int *) malloc(1);
		}
		// Free every other byte
		for (j = 0; j < 50; j += 2) {
			free(testarray[j]);
			testarray[j] = NULL;
		}
		// Reallocate those freed bytes
		for (j = 0; j < 50; j += 2) {
			testarray[j] = (int *) malloc(1);
		}
		// Free the entire List
		for (j = 0; j < 50; j++) {
			free(testarray[j]);
			testarray[j] = NULL;
		}
		gettimeofday(&end, 0);
		timeE = timeE + ((end.tv_sec - begin.tv_sec)*1000000 + (end.tv_usec - begin.tv_usec));
	}	

	// The Time/50 is the average of each Case
	printf("Average time to execute Case A: %d microseconds\n", timeA/50);
	printf("Average time to execute Case B: %d microseconds\n", timeB/50);
	printf("Average time to execute Case C: %d microseconds\n", timeC/50);
	printf("Average time to execute Case D: %d microseconds\n", timeD/50);
	printf("Average time to execute Case E: %d microseconds\n", timeE/50);


	return 0;
}
