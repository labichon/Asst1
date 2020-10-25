#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
//#include "mymalloc.h"

char memory[4096];

//if free = 1, structure is free; if free = 0, structure is not free
typedef struct block {
	size_t size;
	int free;
	struct block *next;
} Block;

Block *List = (void*)memory;

//initialize List
void initialize (){

	List->size = 4096 - sizeof(Block);
	List->free = 1;
	List->next = NULL;
}


//actual malloc function
void *mymalloc (size_t numberOfBytes){

	//pointers to track linked list
	Block *curr;
	Block *prev;
	//pointer to track start of address of allocated memory
	void *result;

	//if List is not initialized, then it becomes initialized
        if(!(List->size)){
		initialize();
	}
	//set pointer
	curr = List;

	//if the metadata block cannot be used, we traverse until we find one that can be used
	while((((curr->size)<numberOfBytes)||((curr->free) == 0)) && (curr->next != NULL)) {
		prev = curr;
		curr = curr->next;
	}

	//metadata block is exactly the size needed
        if((curr->size)==numberOfBytes){
		List->size = 0;
		result = (void*)(++curr);
		return result;
	} else if ((curr->size) > (numberOfBytes + sizeof(Block))){
		//we need a function that finds a free block
		//result = (void*)(++curr);
		//return result;
	} else { //no sufficient data
		result = NULL;
		return result;
	}


}

void free(void* ptr){
	if(((void*)memory<=ptr) && (ptr <= (void*)(memory+4096))){
		Block* curr = ptr;
		--curr;
		curr->free = 1;	
	}
}

