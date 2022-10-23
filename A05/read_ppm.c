#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int startsWith(char string[], char substring[]) { //function for determining if string starts with substring
    for (int i = 0; substring[i] != '\0'; i++){ //for every char in substring
      if (string[i] != substring[i]){ //if it's not the same as string
        return 0; //return false
      }
    }
    return 1; //else return true
  }

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *infile;
  infile = fopen(filename, "r"); //read in file
    if (infile == NULL) { //if file invalid
        printf("Cannot open file: %s\n", filename); //scream
        return NULL; //and leave
    }

  int lineCount = 0; //count for header lines
  while (lineCount < 4) { //reading in the header, which I know is 4 lines
    char str[100]; //space for line
    fgets(str, 100, infile); //read in line
    char firstLine[3] = "P6"; //P6
    char comment[2] = "#"; //hashtag
    char max[4] = "255"; //255
    if ((startsWith(str, firstLine) == 0) && (startsWith(str, comment) == 0) && (startsWith(str, max) == 0)){ //if line doesn't start w/above
      int count = 0; //counting if width or height
      int place = 0; //finding place in width or height
      char width[50] = "";
      char height[50] = "";
      for (int i = 0; str[i] != '\n'; i++){ //for every char in the entire line
        if (str[i] != ' '){ //if char is not a space
          if (count == 0){ //if we're on width
            width[place] = str[i]; //add char to our place in width
            place++; //go to next place
          } else { //if we're on height
            height[place] = str[i]; //add char to our place in heigh
            place++; //go to next place
          }
        } else { //if char is a space
          place = 0; //set place to zero
          count++; //move on to height (or just iterate up, only first two numbers matter)
        }
      }

      int x = atoi(width); //convert string to int
      int y = atoi(height);

      *w = x; //redefining w
      *h = y; //redefining h
    }
    lineCount++; //go to next line of header
  }

  struct ppm_pixel *grid; 
  grid = malloc(sizeof(struct ppm_pixel) * (*w * *h)); //make 2d array bu making one long array


  int position = 0; //for every char we read in
  unsigned char ch = fgetc(infile); //get first char of non-header line

  for (int i = 0; i < (*w * *h)*3; i++){ //for all three values in each tile of the array
    int index = position % 3; //find value of this position
    if (index == 0) { //if value is red
      grid[position/3].red = ch; //set the red value of the correct tile to the char
    } else if (index == 1) { //if value is green
      grid[position/3].green = ch;
    } else if (index == 2) { //if value is blue
      grid[position/3].blue = ch;
    } else {
      printf("Error with the ppm pixel value"); 
    }
    position++; //iterate place
    ch = fgetc(infile); //get next char
  }

  fclose(infile); //closing file
  return grid; //returning the array of structs
  //return NULL;
}

