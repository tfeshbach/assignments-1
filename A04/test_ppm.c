#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
  // load feep-raw and print out the grid of pixels
  int width = 0; //width and height
  int height = 0;
  int *w = &width; //initialize pointer
  int *h = &height;
  struct ppm_pixel* grid = read_ppm("feep-raw.ppm", w, h); //call function
  printf("Testing file feep-raw.ppm: %d %d \n", width, height);
  for (int i = 0; i < height; i++){ //for every row
    for (int j = 0; j < width; j++) { //for every column
      printf("("); //print the grid
      printf ("%d,", grid[(i * width) + j].red);
      printf ("%d,", grid[(i * width) + j].green);
      printf ("%d", grid[(i * width) + j].blue);
      printf(") ");
    }
    printf("\n");
  }
  free(grid); //free
  return 0;
}

