//Author: Talia Feshbach
//Date: 9/30/22
//Name: Minesweeper

#include <stdio.h>
#include <stdlib.h> //includes others
#include <string.h> //includes string functions
#include <time.h>

char tileMaker(float p){ //makes every tile on the board
  float random = (float) rand()/RAND_MAX; //random number between 0 and 1
  char tile; 
  if (random < p){ //if number less than prob
    tile = 'X'; //is mine
  } else {
    tile = '.'; //else is not mine
  }
  return tile;
}

int findMine(char *board, int row, int column, int m, int n){
  int count = 0; //counting nearby mines

  //calculating lowest and highest nearby rows
  int rowLow;
  int rowHigh;
  int columnLow;
  int columnHigh;

  if ((row - 1) < 0) { //finds lowest row
    rowLow = 0;
  } else {
    rowLow = row - 1;
  }

  if ((row + 1) > (m - 1)) { //finds highest row
    rowHigh = m - 1;
  } else {
    rowHigh = row + 1;
  }

  if ((column - 1) < 0) { //finds lowest column
    columnLow = 0; 
  } else {
    columnLow = column - 1;
  }

 if ((column + 1) > (n - 1)) { //finds highest column
    columnHigh = n - 1;
  } else {
    columnHigh = column + 1;
  }

  for (int i = 0; i < m; i++) { //for every row
    for (int j = 0; j < n; j++) { //for every column
      //if current is nearby in row and nearby in column to target position
      if (((i >= rowLow) && (i <= rowHigh) ) && ((j >= columnLow) && (j <= columnHigh) )) {
        if (((i * n) + j) == ((row * n) + column)) { //if current is target position
          continue; //don't count this
        } else if (board[(i * n) + j] == 'X') { //if current is a mine
          count++; //iterate up count of mines
        }
      }
    }
  }

  return count; 
}


int main(int argc, char** argv) {
  srand((unsigned) time(NULL)); //setting up random time
  int m;
  int n;
  float p;
  if (argc != 4) { //if not enough arguments
    //use default values
    printf("You didn't give me enough arguments? I'm taking over! I like THESE numbers: %d %d %f\n", 3, 5, 0.4);
    m = 3;
    n = 5;
    p = 0.4;
  } else { //else use command line arguments
    m = atoi(argv[1]);
    n = atoi(argv[2]);
    p = atof(argv[3]);
  }

  char *board; //pointer to char
  board = malloc(sizeof(char) * (m * n)); //single call to malloc for char array
  
  //making the board
  for (int i = 0; i < m; i++) { //for every row
    for (int j = 0; j < n; j++){ //for every column
      //position is calculated row * n + col
      board[(i * n) + j] = tileMaker(p); //calling tile making with probability
    }
  }

  //printing the board
  for (int i = 0; i < m; i++) { //for every row
    for (int j = 0; j < n; j++){ //for every column
      printf ("%c ", board[(i * n) + j]); //print tiles
    }
    printf("\n"); //next row
  }

  printf("\n"); //spacing before nearby mines

  //printing the nearby mines
  for (int i = 0; i < m; i++) {  //row
    for (int j = 0; j < n; j++){ //column
      if (board[(i * n) + j] == 'X') { //if current is a mine
        printf ("%c ", 'X'); //print X for mine
      } else { //if current is not mine
        printf ("%d ", findMine(board, i, j, m, n)); //print total mines found nearby
      }
    }
    printf("\n"); //next row
  }

  free(board); //freeing our malloc
  return 0;
}
