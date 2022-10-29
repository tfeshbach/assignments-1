#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) { //if incorrect usage
    printf("usage: encode <file.ppm>\n"); //scream
    return 0; //and leave
  }

  int w, h; //width and height
  char* filename = argv[1];
  struct ppm_pixel* image = read_ppm(filename, &w, &h); //get pixel struct
  printf("Reading %s with width %d and height %d\n", filename, w, h); //printing info
  int size = w * h * 3; //size of bits
  int length = (size)/8; //possible length of message based on amount of available sections of 8
  printf("Max number of characters in the image: %d\n", length);

  char* phrase; //phrase to encode
  phrase = malloc(length*sizeof(char)); //malloc its size based on how many chars are available
  memset(phrase, 0, length*sizeof(char)); //fill it with 0s because valgrind cried when you don't
  printf("Enter a phrase: ");
  scanf(" %[^\n]%*c", phrase); //scan in phrase

  char encodedfile[100] = ""; //making the new file name
  for (int i = 0; i < strlen(filename) - 4; i++){ //reading in all but ".ppm"
    encodedfile[i] = filename[i]; 
  }
  char* code = "-encoded.ppm"; 
  strcat(encodedfile, code); //appending "-encoded.ppm"



  unsigned char* bits = (unsigned char*)image; //cast pixels to unsigned chars
  //unsigned char* str = (unsigned char*)image; //cast pixels to chars


  unsigned char mask = 0x1; //mask
  unsigned char bit; //thing to put in least signigicant bit
  for (int i = 0; i < length; i++){ //for every char
    for (int j = 0; j < 8; j++){ //for every bit composing that char
      bit = (phrase[i] >> (7-j)) & mask; //get relevant bit from string
      bits[i*8 + j] &= ~mask; //clear the least significant bit in the current char
      bits[i*8 + j] |= bit; //AND the bit into the least significant place
    }
  }

struct ppm_pixel *grid = malloc(sizeof(struct ppm_pixel) * (w * h)); //make new pixel grid
for (int i = 0; i < size; i++){
  int index = i % 3; //find value of this position
  if (index == 0) { //if value is red
      grid[i/3].red = bits[i]; //set the red value of the correct tile to the char
    } else if (index == 1) { //if value is green
      grid[i/3].green = bits[i];
    } else if (index == 2) { //if value is blue
      grid[i/3].blue = bits[i]; 
    }
}

  printf("Writing file %s\n", encodedfile); 
  write_ppm(encodedfile, grid, w, h); //write encoded file 

  free(grid); //free the grid we made for encoded image
  free(image); //free the image opened in the first place
  free(phrase); //free the phrase they gave us
  return 0;
}

