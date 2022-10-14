#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

char assignment(int value){ //assigning the character symbols to the values
  char symbol;
  if (value < 26){
    symbol = '@';
  } else if (value >= 26 && value < 51){
    symbol = '#';
  } else if (value >= 51  && value < 76){
    symbol = '%';
  } else if (value >= 76  && value < 101){
    symbol = '*';
  } else if (value >= 101  && value < 126){
    symbol = 'o';
  } else if (value >= 126  && value < 151){
    symbol = ';';
  } else if (value >= 151  && value < 176){
    symbol = ':';
  } else if (value >= 176  && value < 201){
    symbol = ',';
  } else if (value >= 201  && value < 225){
    symbol = '.';
  } else if (value >= 225  && value <= 255){
    symbol = ' ';
  } else {
    printf("Huh?");
    symbol = '!';
  }
  return symbol;
}


int main(int argc, char** argv) {
  char* filename; 
  if (argc != 2) { //if not enough ergs
    printf("usage: ascii_image <file.ppm>\n"); //scream
    return 0; //and leave
  }
  filename = argv[1]; //file
  int width = 0;
  int height = 0;
  int *w = &width;
  int *h = &height;
  struct ppm_pixel* grid = read_ppm(filename, w, h); //call function
  printf("Reading file %s with width %d and height %d \n", filename, width, height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int x = (i * width) + j; //find place in grid
      int i = (grid[x].red + grid[x].green + grid[x].blue)/3; //calculate sum
      char value = assignment(i); //find symbol for sum
      printf("%c", value);
    }
    printf("\n");
  }

  free(grid); //free
  return 0;
}

