#include<stdio.h>
#include<stddef.h>
#include "mymalloc.h"


void initialize(){ // giving values to metadata so it is not garbage data
 metadata->size=4096-sizeof(Node); //this is the amount of freespace left after allocating 1 metadata node = 4080
 metadata->inUse=0;
 metadata->next=NULL;
}

//if there is a free block with size greater than what you are trying to allocate
void split(Node *fit,size_t size){
  //fit=ptr to free block, size = size of mem being allocated,casting is so new can be memory of any type
 Node *new=(void*)((void*)fit+size+sizeof(Node));
 new->size=(fit->size)-size-sizeof(Node);
 new->inUse=0;
 new->next=fit->next; //insert new mem into metadata LL
 fit->size=size;
 fit->inUse=1;
 fit->next=new;
}

void *mymalloc(size_t noOfBytes, char* filename, int line){

 Node *curr,*prev;
 void *result;
 if(!(metadata->size)){  //if metadata is empty(nothing has been allocated yet), initialize
  initialize();

 }
 curr=metadata;

 //loop iterates until curr points to the 1st free block available (first fit)
 while((((curr->size)<noOfBytes)||((curr->inUse)==1))&&(curr->next!=NULL)){
  prev=curr;
  curr=curr->next;

 }
 if((curr->size)==noOfBytes){ //if the block is exactly the right size as the mem to be allocated
  curr->inUse=1;
  result=(void*)(++curr);

  return result;
 }

 /*if block is larger than mem to be allocated, the block needs to be split so the remaining memory of the
 block is still left free*/
 else if((curr->size)>(noOfBytes+sizeof(Node))){
  split(curr,noOfBytes);
  result=(void*)(++curr);
  return result;
 }
 else{
   fprintf(stderr,"Error: no available memory to allocate at %s, line %d\n", filename, line);
  result=NULL;//no available block to allocate
  return result;
 }
}

void myfree(void* ptr, char* filename, int line) {

  if (ptr == NULL) {

    fprintf(stderr, "Error: address is not a pointer at %s, line %d\n", filename, line) ;
    return ;

  }

  Node * p = ptr ;
  p-- ;

  if (isAllocated(p) == 0) {

    fprintf(stderr, "Error: pointer was not allocated by malloc at %s, line %d\n", filename, line) ;
    return ;

  } else if (isAllocated(p) == 1 && p->inUse == 0) {

    fprintf(stderr, "Error, redundant free()ing of the same pointer at %s, line %d\n", filename, line) ;
    return ;

  }

  p->inUse = 0 ;

  Node *point = metadata ;
  Node *prev = NULL ;

  while (point->next != NULL) {

    if (point->inUse == 0 && point->next->inUse == 0) {
        // Have to combine size into left node and not right, causes problems otherwise!
            point->size = point->next->size + point->size + sizeof(Node) ;
            point->next = point->next->next ;
            Node * temp = point->next ;
            while (temp != NULL && temp->inUse == 0) { // Need this to combine free blocks properly!
              point->size = point->size + temp->size + sizeof(Node) ;
              if (temp->next == NULL) {

                point->next = NULL ;
                break ;

              }else{
                point->next=temp->next;
              }

              temp = temp->next ;

            }

    }

    if (point->next == NULL) { // Avoiding segmentation fault

      break ;

    }

    prev = point ;
    point = point->next ;

  }

}

int isAllocated(Node * n) {

  Node * ptr = metadata ;

  while (ptr != NULL) {

    if (n == ptr) {

      return 1 ;

    }

    ptr = ptr->next ;

  }
  return 0 ;

}
