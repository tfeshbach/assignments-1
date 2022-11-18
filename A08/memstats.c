#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "rand.h"

#define ROUNDS 3
#define BUFFER 5
#define LOOP 10

struct chunk {
  int size;
  int used;
  struct chunk *next;
};

void memstats(struct chunk* freelist, void* buffer[], int len) {
  //freelist is freed memory, buffer list is current memory, len is buffer size (5)
  //variable setup below
  int totalMem = 0;
  int usedMem = 0; 
  int freeMem = 0;

  int totalBlocks = 0;
  int usedBlocks = 0; 
  int freeBlocks = 0;
  int under = 0;

  for (int i = 0; i < len; i++) { //for every spot in buffer
    if (buffer[i] != NULL){ //if there's something there
      struct chunk *block = (struct chunk*) ((struct chunk*) buffer[i] - 1 ); //retrieve its block
      totalMem = totalMem + (block->size); //add the block's size to total memory
      usedMem = usedMem + (block->size); //add the block's usage to used memory
      under = under + ((block->size) - (block->used));
      totalBlocks += 1; //count total blocks up
      usedBlocks += 1; //count used blocks up
    }
  }

  struct chunk *next = freelist; //get first item of freelist

  while (next != NULL) { //while list isn't empty
    totalMem += next->size; //add freed block's size to total memory
    freeMem += next->size; //add freed block's size to freed memory
    totalBlocks += 1; //count total blocks up
    freeBlocks += 1; //count free blocks up
    next = next->next; //go to next item in list
  }

  printf("Underutilized memory: %d\n", under);
  


  //print all the values
  printf("Total blocks: %d ", totalBlocks);
  printf("Free blocks: %d ", freeBlocks);
  printf("Used blocks: %d\n", usedBlocks);
  printf("Total memory allocated: %d ", totalMem);
  printf("Free memory: %d ", freeMem);
  printf("Used memory: %d\n", usedMem);
  printf("Underutilized memory: %f\n", (float)under/(float)usedMem);
}

int main ( int argc, char* argv[]) {

  printf("Starting test..\n");

  srand(100);

  double timer;
  struct timeval tstart, tend;

  gettimeofday(&tstart, NULL);

  void *buffer[BUFFER];
  for (int i = 0; i < BUFFER; i++) {
    buffer[i] = NULL;
  }

  void *init = sbrk(0);
  void *current;
  printf("The initial top of the heap is %p.\n", init);
  for (int j = 0 ; j < ROUNDS; j++) {
    printf("---------------\n%d\n" , j);

    for (int i= 0 ; i < LOOP ; i++) {
      int index = rand() % BUFFER;
      if (buffer[index] != NULL) { //if index isn't empty
        free(buffer[index]); //free it
        buffer[index] = NULL;
        printf("Freeing index %d\n", index);
        
      } 
      else {
        size_t size = (size_t) randExp(8, 4000); 
        int *memory = NULL;
        memory = malloc(size);

        if (memory == NULL) {
          fprintf(stderr, "malloc failed\n");
          return(1);
        } 
        *memory = 123;
        buffer[index] = memory;
        printf("Allocating %d bytes at index %d\n", (int) size, index);
      }
    }
    extern struct chunk* flist; //freelist
    current = sbrk(0);
    int allocated = current - init;
    init = current;

    printf("The new top of the heap is %p.\n", current);
    printf("Increased by %d (0x%x) bytes\n", allocated, allocated);
    memstats(flist, buffer, BUFFER);

  }

  for (int i = 0; i < BUFFER; i++) {
    free(buffer[i]); 
  }
  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Time is %g\n", timer);
  return 0 ;
}
