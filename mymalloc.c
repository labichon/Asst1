#include <stdio.h>
#include "mymalloc.h"

#define MEM_LEN 4096

#ifndef DEBUG
#define DEBUG 0
#endif

static char memory[MEM_LEN];

//if free = 1, structure is free; if free = 0, structure is not free
typedef struct metadata {
	char free;
	unsigned short size;
	struct metadata *next;
} metadata;


//initialize List
void initialize (){
	metadata *head = (metadata *) memory;
	head->size = MEM_LEN - sizeof(metadata);
	head->free = 1;
	head->next = NULL;
}


//actual malloc function
void *mymalloc (size_t reqBytes, char *file, int line){
	if (DEBUG) {
		printf("\nSize of metadata: %lu\n", sizeof(metadata));
		printf("Size of char: %lu\n", sizeof(char)); //Should be 1
	}

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
		// Cannot alloc
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
	return (void *) (curr + sizeof(metadata));

	/*
	//if the metadata block cannot be used, we traverse until we find one that can be used
	while((((curr->size)<reqBytes)||((curr->free) == 0)) && (curr->next != NULL)) {
		prev = curr;
		curr = curr->next;
	}

	//metadata block is exactly the size needed
        if((curr->size)==reqBytes){
		curr->size = 0;
		result = (void*)(++curr);
		return result;
	} else if ((curr->size) > (reqBytes + sizeof(metadata))){
		//we need a function that finds a free block
		//result = (void*)(++curr);
		//return result;
	} else { //no sufficient data
		result = NULL;
		return result;
	}
	*/

}

void myfree(void* ptr, char* file, int line){
	if(((void*)memory<=ptr) && (ptr <= (void*)(memory+MEM_LEN))){
		metadata* curr = ptr;
		--curr;
		curr->free = 1;	
	}
}

