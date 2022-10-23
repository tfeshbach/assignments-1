#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned long img;
  scanf(" %lx", &img); //scan in image
  printf("Image (unsigned long): %lx\n", img);
  int count = 64; //count for shift placement
  unsigned long mask; //mask
  unsigned long value; //value
  for (int i = 0; i < 8; i++){ //for every row
    for (int j = 0; j < 8; j++){ //every column
      mask = 0x1ul << (count - 1); //make mask by shifting 1 left by count
      value = (mask & img); //and mask and image
      if (value == 0) { //if zero
        printf(" "); //space

      } else {
        printf("@"); //else symbol
      }
      count--; //decrement count
    }
    printf("\n"); //next line
  }
  return 0;
}
