#ifndef _MYMALLOC_H
#define _MYMALLOC_H
#include <stdio.h>
#include <stdlib.h>
#include<stddef.h>
#include<time.h>

#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x,__FILE__,__LINE__)

static char myblock[4096];

typedef struct LL{
 size_t size;
 int inUse;
 struct LL *next;
}Node;



static Node *metadata=(void*)myblock;

void initialize();
void split(Node *fitting_slot,size_t size);
void *mymalloc(size_t noOfBytes, char* fileName, int line);
void myfree(void* ptr, char* filename, int line);
int isAllocated(Node * n);

#endif
