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
#include "read_ppm.h"
#include "write_ppm.h"

struct ppm_pixel *mandelbrot (int size, int leftcol, int rightcol, int toprow, int bottomrow, float xmin, float xmax, float ymin, float ymax, 
int maxIterations, struct ppm_pixel *palette, struct ppm_pixel black,
struct ppm_pixel *grid){

struct ppm_pixel color;
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
  return grid;
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
  printf("  Num processes = %d\n", numProcesses);
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


  int shmid;
  shmid = shmget(IPC_PRIVATE, sizeof(struct ppm_pixel) * (size * size), 0644 | IPC_CREAT);
  if (shmid == 1){
    perror("Error: cannot initialize shared memory\n");
    exit(1);
  }
  struct ppm_pixel *grid = shmat(shmid, NULL, 0);
  if (grid == (void*)-1){
    perror("Error: cannot access shared memory\n");
    exit(1);
  }
  memset(grid,'0', sizeof(struct ppm_pixel) * (size * size));


  int halfsize = size/2;

  for (int i = 0; i < 4; i++) {
    pid_t pid;
    int status;
    pid = fork();
    if (pid == 0){
      int leftcol = (i)%2 * halfsize;
      int toprow;
      if (i<2) {
        toprow = 0;
      } else{
        toprow = halfsize;
      }
      int rightcol = ((i)%2 * halfsize) + halfsize;
      int bottomrow;
      if (i<2) {
        bottomrow = halfsize;
      } else{
        bottomrow = size;
      }
      printf("%d) Sub-image block: cols (%d, %d) to rows (%d,%d)\n", getpid(), leftcol, rightcol, toprow, bottomrow);
      grid = mandelbrot(size, leftcol, rightcol, toprow, bottomrow, xmin, xmax, ymin, ymax, maxIterations, palette, black, grid);
      exit(0);
      }
      else {
      printf("Launched child process: %d\n", pid);
    }
  }

  for (int i = 0; i < 4; i++) {
    int status;
    int pid = wait(&status);
    printf("Child process complete: %d\n", pid);
  }

  char filename[50];
  int timestamp = time(0);
  int concat = snprintf(filename, sizeof(filename),"multi-mandelbrot-%d-%d.ppm", size, timestamp);

  write_ppm(filename, grid, size, size);

  gettimeofday(&tend, NULL);

  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Computed mandelbrot set (%dx%d) in %g seconds\n", size, size, timer);
  printf("Writing file: %s\n", filename);


  free(palette);

  //cleanup
  if(shmdt(grid) == -1){
    perror("Error: cannot detatch from shared memory\n");
    exit(1);
  }
  if(shmctl(shmid, IPC_RMID,0) == -1){
    perror("Error: cannot remove shared memory\n");
    exit(1);
  }

}
