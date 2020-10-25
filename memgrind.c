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

	// Test case A
	for (i = 0; i < 50; i++) {
		gettimeofday(&begin, 0);
		for (j = 0; j < 120; j++){
			testarray[j] = (int *) malloc(1);
			free(testarray[j]);
			testarray[j] = NULL;
		}
		gettimeofday(&end, 0);
		timeA = timeA + ((end.tv_sec - begin.tv_sec)*1000000 + (end.tv_usec - begin.tv_usec));
	}

	//Test Case B
	for (i = 0; i < 50; i++) {
		gettimeofday(&begin, 0);
		for(j = 0; j < 120; j++) {
			testarray[j] = (int *) malloc(1);
		}
		for(j = 0; j < 120; j++) {
			free(testarray[j]);
			testarray[j] = NULL;
		}
		gettimeofday(&end, 0);
		timeB = timeB + ((end.tv_sec - begin.tv_sec)*1000000 + (end.tv_usec - begin.tv_usec));;
	}
	
	//Test Case C
	for (i = 0; i < 50; i++) {
		gettimeofday(&begin, 0);
		int MallocCounter = 0;
		int numberOfMallocs = 0;
		int numberOfFrees = 0;
		srand(time(NULL));
		int random = rand() % 2;
		while (MallocCounter < 240) {
			if ((numberOfMallocs < 120) && (random == 0)) {
				testarray[numberOfMallocs] = (int *) malloc(1);
				numberOfMallocs++;
				MallocCounter++;
			} else {
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
	
			/*
			if(random == 0) {
				testarray[numberOfMallocs] = (int *) malloc(1);
				MallocCounter++;
				if(!(testarray[numberOfMallocs] == NULL)) {
					numberOfMallocs++;
					MallocCounter++;
				} else {
					free(testarray[numberOfFrees]);
					testarray[numberOfFrees] = NULL;
					numberOfFrees++;
				}
			if(random == 1){
				free(testarray[numberOfFrees]);
				if((testarray[numberOfFrees]) == NULL) {
					testarray[numberOfMallocs] = (int *) malloc(1);
					numberOfMallocs++;
					MallocCounter++;
				} else {
					testarray[numberOfFrees] = NULL;
				       	numberOfFrees++;	
				}

			}
			}*/
			random = rand() % 2;
		}
		
		for(j = numberOfFrees; j < 240; j++){
			free(testarray[j]);
			testarray[j] = NULL;
		}
		gettimeofday(&end, 0);	
		timeC = timeC + ((end.tv_sec - begin.tv_sec)*1000000 + (end.tv_usec - begin.tv_usec));
	}

	//Test Case D
	for (i = 0; i < 50; i++) {
		gettimeofday(&begin, 0);
                for (j = 0; j < 500; j++){
                        testarray[j] = (int *) malloc(1);
                        free(testarray[j]);
                        testarray[j] = NULL;
                }
		int k;
		for(k = 0; k < 100; k++) {
                        testarray[k] = (int *) malloc(1);
                }
                for(k = 0; k < 100; k++) {
                        free(testarray[k]);
                        testarray[k] = NULL;
                }
                gettimeofday(&end, 0);
                timeD = timeD + ((end.tv_sec - begin.tv_sec)*1000000 + (end.tv_usec - begin.tv_usec));
	}

	
	//Test Case E
	for (i = 0; i < 50; i++) {
		gettimeofday(&begin, 0);
		for (j = 0; j < 50; j++) {
			testarray[j] = (int *) malloc(1);
		}
		for (j = 0; j < 50; j += 2) {
			free(testarray[j]);
			testarray[j] = NULL;
		}
		for (j = 0; j < 50; j += 2) {
			testarray[j] = (int *) malloc(1);
		}
		for (j = 0; j < 50; j++) {
			free(testarray[j]);
			testarray[j] = NULL;
		}
		gettimeofday(&end, 0);
		timeE = timeE + ((end.tv_sec - begin.tv_sec)*1000000 + (end.tv_usec - begin.tv_usec));
	}	

	printf("Mean time to execute Case A: %d milliseconds\n", timeA/50);
	printf("Mean time to execute Case B: %d milliseconds\n", timeB/50);
	printf("Mean time to execute Case C: %d milliseconds\n", timeC/50);
	printf("Mean time to execute Case D: %d milliseconds\n", timeD/50);
	printf("Mean time to execute Case E: %d milliseconds\n", timeE/50);


	return 0;
}
