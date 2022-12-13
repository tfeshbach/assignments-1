#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

struct thread_data {
  int size;
  int leftcol;
  int rightcol;
  int toprow;
  int bottomrow;
  float xmin;
  float xmax;
  float ymin;
  float ymax;
  int maxIterations;
  struct ppm_pixel *palette;
  struct ppm_pixel black;
  struct ppm_pixel *grid;
};

void *mandelbrot (void *userdata){
  struct thread_data *data = (struct thread_data *) userdata;
  struct ppm_pixel color;

  int size = data->size;
  int leftcol = data->leftcol;
  int rightcol = data->rightcol;
  int toprow = data->toprow;
  int bottomrow = data->bottomrow;
  float xmin = data->xmin;
  float xmax = data->xmax;
  float ymin = data->ymin;
  float ymax = data->ymax;
  int maxIterations = data->maxIterations;
  struct ppm_pixel *palette = data->palette;
  struct ppm_pixel black = data->black;
  struct ppm_pixel *grid = data->grid;

  for (float i = toprow; i < bottomrow; i++) { //for every row in the image
   for (float j = leftcol; j < rightcol; j++) { //for each col in the image 
      float xfrac = i / (size);
      float yfrac = j / (size);
      float x0 = xmin + xfrac * (xmax - xmin);
      float y0 = ymin + yfrac * (ymax - ymin);

      float x = 0;
      float y = 0;
      int iter = 0;
      while ((iter < maxIterations) && ((x*x + y*y) < 2*2)) {
        float xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        iter++;
      }
      if (iter < maxIterations) {// escaped
        color = palette[iter];
      } else {
        color = black;
      }
      grid[(int)(j*(size) + i)] = color;
    }
  }
  //return grid;
  return (void*) NULL;
}

int main(int argc, char* argv[]) {
 srand(time(NULL));

   //time calculation start
  double timer;
  struct timeval tstart, tend;
  int** M = NULL;

  gettimeofday(&tstart, NULL);

 
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> "
        "-b <ymin> -t <ymax> -p <numProcesses>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  //printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  struct ppm_pixel *palette; 
  palette = malloc(sizeof(struct ppm_pixel) * (maxIterations));
  for (int i = 0; i < maxIterations; i++){
    palette[i].red = rand() % 255;
    palette[i].green = rand() % 255;
    palette[i].blue = rand() % 255;
  }

  struct ppm_pixel black;
  black.red = 255;
  black.green = 255;
  black.blue = 255;

  struct ppm_pixel *grid; 
  grid = malloc(sizeof(struct ppm_pixel) * (size * size));
  memset(grid,'0', sizeof(struct ppm_pixel) * (size * size));

  
  int halfsize = size/2;

  pthread_t threads[4];
  struct thread_data data[4];

  for (int i = 0; i < 4; i++) {
    int leftcol = (i)%2 * halfsize;
    int toprow;
    if (i<2) {
      toprow = 0;
    } else {
      toprow = halfsize;
    }
    int rightcol = ((i)%2 * halfsize) + halfsize;
    int bottomrow;
    if (i<2) {
      bottomrow = halfsize;
    } else {
      bottomrow = size;
    }
    data[i].size = size;
    data[i].leftcol = leftcol;
    data[i].rightcol = rightcol;
    data[i].toprow = toprow;
    data[i].bottomrow = bottomrow;
    data[i].xmin = xmin;
    data[i].xmax = xmax;
    data[i].ymin = ymin;
    data[i].ymax = ymax;
    data[i].maxIterations = maxIterations;
    data[i].palette = palette;
    data[i].black = black;
    data[i].grid = grid;

    pthread_create(&threads[i], NULL, mandelbrot, (void*) &data[i]);
    //grid = mandelbrot(size, leftcol, rightcol, toprow, bottomrow, xmin, xmax, ymin, ymax, maxIterations, palette, black, grid);
    printf("%lu) sub-image block: cols (%d, %d) to rows (%d,%d)\n", pthread_self(), leftcol, rightcol, toprow, bottomrow);
    }

  for (int i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
    printf("Thread %lu) finished \n", pthread_self());
  }

  char filename[50];
  int timestamp = time(0);
  int concat = snprintf(filename, sizeof(filename),"mandelbrot-%d-%d.ppm", size, timestamp);

  write_ppm(filename, grid, size, size);

  gettimeofday(&tend, NULL);

  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Computed mandelbrot set (%dx%d) in %g seconds\n", size, size, timer);
  printf("Writing file: %s\n", filename);

  //cleanup
  free(palette);
  free(grid);

}
