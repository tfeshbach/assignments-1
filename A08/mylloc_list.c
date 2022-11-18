#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size; // size of memory allocated from sbrk
  int used; // *NEW*: amount currently in use
  struct chunk *next;
};
struct chunk *flist = NULL;

void *malloc (size_t size) {
  // TODO: Implement malloc with a free list (See reading for details)
  if (size == 0) {
    return NULL;
  }
  struct chunk *next = flist;
  struct chunk *prev = NULL;

  while (next != NULL) {
    if (next->size >= size) {
      if (prev != NULL) {
        prev->next = next->next;
      } else {
        flist = next->next;
      }
    (next)->used = size; //note the memory being used for this chunk this time
    return (void*)(next + 1);
    } else {
      prev = next;
      next = next->next ;
    }
  }
    
  /* use sbrk to allocate new memory */
  void *memory = sbrk(size + sizeof(struct chunk));
  if (memory == (void*) - 1) {
    return NULL;
  } else {
    struct chunk *cnk = (struct chunk*)memory;
    cnk->size = size;
    cnk->used = size; //chunk just set up, memory is fully used
    return (void*)(cnk + 1);
  }
  return NULL;
}

void free(void *memory) {
  if (memory != NULL) {
  /* we're jumping back one chunk position*/
    struct chunk *cnk = (struct chunk*) ((struct chunk*) memory - 1 );
    cnk->next = flist;
    flist = cnk;
  }
  return;
}
