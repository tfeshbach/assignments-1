#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) { //if incorrect usage
    printf("usage: decode <file.ppm>\n"); //scream
    return 0; //and leave
  }
  int w, h; //width and height
  char* filename = argv[1];
  struct ppm_pixel* image = read_ppm(filename, &w, &h); //get pixel struct
  printf("Reading %s with width %d and height %d\n", filename, w, h); //printing info
  unsigned char* bits = (unsigned char*)image; //cast pixels to unsigned chars
  char* str = (char*)image; //cast pixels to chars
  int size = w * h * 3; //size of bits
  int length = (size)/8; //possible length of message based on amount of available sections of 8
  printf("Max number of characters in the image: %d\n", length); //print possible length

  unsigned char mask = 0x1; //mask
  unsigned char dest; //destination of least signigicant bit
  for (int i = 0; i < length; i++){ //for every char
    for (int j = 0; j < 8; j++){ //for every bit composing that char
      dest = mask << (7-j); //destination of this bit is our current place in the char
      str[i] &= ~dest; //clear that destination in the char
      str[i] |= ((bits[i*8 + j] & mask) << (7-j)); //after getting the least significant bit, shift it to destination and OR it in 
    }
  }

  printf("%s\n", str); //print the string 
  
  free(image); //free the pixel
  
  return 0;
}

