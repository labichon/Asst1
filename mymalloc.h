// Malloc header file
#ifndef MALLOC_H
#define MALLOC_H

typedef struct metadata metadata;

void *mymalloc(size_t, char *, int);
void myfree(void *, char *, int);

#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x,__FILE__,__LINE__)

#endif
