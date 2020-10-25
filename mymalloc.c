#include <stdio.h>
#include "mymalloc.h"

#define MEM_LEN 4096

#ifndef DEBUG
#define DEBUG 0
#endif

static char memory[MEM_LEN];

// Our metadata struct
// if free = 1, structure is free
// if free = 0, structure is not free
typedef struct metadata {
	char free;
	unsigned short size;
	struct metadata *next;
} metadata;


// This function initializes the List in order to
// be traversed and used by mymalloc and myfree
// by crerating the first block of metaddata.
// It should only be called when malloc has not
// been called before
void initialize (){
	metadata *head = (metadata *) memory;
	head->size = MEM_LEN - sizeof(metadata);
	head->free = 1;
	head->next = NULL;
}

/* mymalloc(size_t, char *, int)
 * INPUTS: required bytes (size_t), char* (file name), line (int)
 * OUTPUT: void pointer to malloced space
 * ERRORS: requesting 0 bytes, finding no free space
 * (both returned as NULL)
 * We loop throughout the list looking for free space such that 
 * can fit the sizeof(metadata) and the required bytes
*/ 
void *mymalloc (size_t reqBytes, char *file, int line){
	
	if (DEBUG) {
		printf("\n=====MALLOC=====\n");
		printf("Size of metadata: %lu\n", sizeof(metadata));
		printf("Size of char: %lu\n", sizeof(char)); //Should be 1
	}
	
	//invalid entry into mymalloc
	if (reqBytes == 0) { 
		printf("%s:%d : Cannot request %lu bytes, returning NULL\n", file, line, reqBytes);
		return NULL;
	}

	metadata *curr = (metadata *)memory;

	// Since all global memory gets initialized to 0,
	// we use this to check if the list is initialized
        if (curr->size == 0) initialize();
	

	size_t totalBlockSize = reqBytes+sizeof(metadata);

	// Loop through each block
	while(curr != NULL) {
		if (DEBUG) {
			printf("Metadata: (size: %u, free: %d, next: %p, totalSize: %lu)\n", 
				curr->size, curr->free, (void *)curr->next, totalBlockSize);
		}
		
		// Break out if we find a valid block
		if(curr->free && (curr->size == reqBytes || curr->size >= totalBlockSize)) {
			break;
		}
		curr = curr->next;
	}
	
	if(curr == NULL) {
		// If there is no valid block, we exit
		printf("%s:%d : Cannot allocate %lu requested bytes, returning NULL\n", 
			file, line, reqBytes);
		return NULL;
	} else if(curr->size == reqBytes) {
		// Just change free bit
		curr->free = 0;	
	} else {
		// Allocate space and add new metadata
		metadata *toInsert = (metadata *) (curr + reqBytes);
		toInsert->size = curr->size - totalBlockSize;
		toInsert->free = 1;
		toInsert->next = curr->next;

		curr->size = reqBytes;
		curr->free = 0;
		curr->next = toInsert;
	}

	if (DEBUG) {
		printf("Allocated %lu requested bytes\n", reqBytes);
		printf("Metadata: (size: %u, free: %d, next: %p)\n", 
			curr->size, curr->free, (void *)curr->next);
		printf("Next Metadata: (size: %u, free: %d, next: %p)\n", 
                        curr->next->size, curr->next->free, (void *)curr->next->next);
	}
	return (void *)curr + sizeof(metadata);

}

/* myfree(void *, char *, int)
 * INPUTS: ptr to malloced memory (void *), file name (char *), line number (int)
 * OUTPUTS: n/a
 * ERRORS: ptr not a valid pointer, ptr outside memory array, ptr already freed,
 * ptr not allocated by malloc (invalid)
 * We loop through the List looking for a metadata struct such that
 * the address of the struct + the sizeof(metadata) matches the passed
 * ptr exactly
*/
void myfree(void* ptr, char* file, int line){

	if (DEBUG) printf("\n=====FREE=====\n");

	if(ptr < ((void *)memory) || ptr >= ((void *)(memory+MEM_LEN))) {
		// Pointer invalid or out of bounds of memory array
		printf("%s:%d : Pointer %p invalid or outside memory array\n",
                        file, line, ptr);
		return;
	}

	// Pointers to traverse the List
	metadata *curr = (metadata *)memory;
	metadata *prev = NULL;

	// While our pointer is still inbounds and hasn't passed the ptr, we traverse the List
	while (curr != NULL && ((void *)curr) < ptr) {
		// We found our match
		if (((void *)curr) + sizeof(metadata) == ptr) {
			if (curr->free == 1) {
				// Already freed memory
				printf("%s:%d : Pointer %p already freed\n",
                        		file, line, ptr);
				return;
			}
			
			if (DEBUG) printf("Freeing %p\n", ptr);

			// Free block of memory
			curr->free = 1;

			if (DEBUG) {
				printf("Metadata: (size: %u, free: %d, next: %p)\n",
                        		curr->size, curr->free, (void *)curr->next);
			}

			// Coalesce if neighbors are free
			// Coalesces with the next metadata
			if (curr->next != NULL && curr->next->free == 1) {
				curr->size += sizeof(metadata) + curr->next->size;
				curr->next = curr->next->next;
				if (DEBUG) {
					printf("Coalescing with next\n");
                                	printf("Metadata: (size: %u, free: %d, next: %p)\n",
                                        	curr->size, curr->free, (void *)curr->next);
                        	}
			}

			//Coalesces with the previous metadata
			if (prev != NULL && prev->free == 1) {
				prev->size += sizeof(metadata) + curr->size;
				prev->next = curr->next;
				if (DEBUG) {
                                        printf("Coalescing with prev\n");
                                        printf("Metadata: (size: %u, free: %d, next: %p)\n",
                                                prev->size, prev->free, (void *)prev->next);
                                }
			}
			return;
		}
		prev = curr;
		curr = curr->next;
	}

	// Pointer not allocated
	printf("%s:%d : Pointer  %p not allocated\n",
                file, line, ptr);
}

