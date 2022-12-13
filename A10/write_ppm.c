#include "write_ppm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
    FILE *outfile;
    outfile = fopen(filename, "w"); //opens file for writing
    if (outfile == NULL) { //if file invalid
        printf("Error: unable to open outfile\n"); //scream
        exit(1); //leave
    }
    char *lineone = "P6"; //file type
    char *linetwo = "#Created by Talia Feshbach in C"; //creation message
    //skipping line three because I print out width and height individually
    char *linefour = "255"; //max size
    fprintf(outfile, "%s\n%s\n%d %d\n%s\n", lineone, linetwo, w, h, linefour); //formatted print
    fwrite(pixels, sizeof(struct ppm_pixel), (w*h), outfile); //write the data to the file

    fclose(outfile); //close file
}
