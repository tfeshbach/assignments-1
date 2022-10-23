#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: glitch <file.ppm>\n");
    return 0;
  }
  int w, h;
  char* filename = argv[1];
  char glitchedfile[100] = "";
  for (int i = 0; i < strlen(filename) - 4; i++){
    glitchedfile[i] = filename[i];
  }
  char* glitch = "-glitch.ppm";
  strcat(glitchedfile, glitch);
  //int length = strlen(filename);
  //glitchedfile[length + 1] = '.';
  //glitchedfile[length + 2] = 'p';
  //glitchedfile[length + 3] = 'p';
  //glitchedfile[length + 4] = 'm';
  //glitchedfile[length + 5] = '\0';



  struct ppm_pixel* image = read_ppm(filename, &w, &h);
  struct ppm_pixel *glitchedimage;
  glitchedimage = malloc(sizeof(struct ppm_pixel) * (w * h)); //make 2d array bu making one long array

  printf("Reading %s with width %d and height %d\n", filename, w, h);

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
       struct ppm_pixel p = image[i*w+j]; 
       struct ppm_pixel g;
       g.red = p.blue << (rand() % 2); //switching colors and randomly shifting bits
       g.green = p.red << (rand() % 2);
       g.blue = p.green << (rand() % 2);
       glitchedimage[i*w+j] = g;
    }
  }

  printf("Writing file %s\n", glitchedfile);
  write_ppm(glitchedfile, glitchedimage, w, h);
  free(image);
  free(glitchedimage);
  return 0;
}

