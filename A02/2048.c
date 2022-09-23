#include <stdio.h>
#include <stdlib.h> //includes others
#include <string.h> //includes string functions

int maxMatrix (int matrix[4][4]) {
  int max = 0;
  for (int i = 0; i < 4; i++){ //every row 
    for (int j = 0; j < 4; j++) { //every column
      if (matrix[i][j] > max) { //if current is bigger than max
        max = matrix[i][j]; //current is now max
      } 
    }
  }
  return max;
}
int shiftRows(int matrix[4][4]) { //go by rows - works for both shift left and right
  int biggest = 0; //finds biggest combo
  int combo = 0; //boolean for if a combo happens
  for (int i = 0; i < 4; i++){ //for every row 
    int prev = 0; //set up prev
    for (int j = 0; j < 4; j++) { //for every column
      int now = matrix[i][j]; //set current
      if (now == 0){ //if current is 0
        continue; //skip to next value
      }

      if (now == prev) { //if now is same as prev
        if ((now + prev) > biggest) {//if their combo is bigger than biggest
          biggest = now + prev; //set biggest
        }
        combo = 1; //boolean switched to combo found
      }
      prev = now; //prev set to now
    }
  }
  if (combo == 1) { //if combo found
    return biggest; //return max combo
  } else { //if combo not found
    return 0; //return 0
  } 
}

int shiftColumns(int matrix[4][4]) { //go by columns - works for both shift up and down
  //mostly same as rows function
  int biggest = 0; 
  int combo = 0;
  for (int j = 0; j < 4; j++){ //for every column
    int prev = 0;
    for (int i = 0; i < 4; i++) { //for every row
      int now = matrix[i][j];
      if (now == 0){
        continue;
      }

      if (now == prev) {
        if ((now + prev) > biggest) {
          biggest = now + prev;
        }
        combo = 1;
      }
      prev = now;
    }
  }
  if (combo == 1) {
    return biggest;
  } else {
    return 0;
  }
}

int main( ) {
  int matrix[4][4]; //row then column
  for (int i = 0; i < 4; i++) { //for every row
    scanf("%d %d %d %d", &matrix[i][0], &matrix[i][1], &matrix[i][2], &matrix[i][3]);
    //scan in values from text file to that row
  }

  int max = 0; //set max
  if (shiftColumns(matrix) >= shiftRows(matrix)){ //if column shift bigger or equal
    max = shiftColumns(matrix); //max is column shift
  } else if (shiftColumns(matrix) < shiftRows(matrix)){ //if row shift bigger
    max = shiftRows(matrix); //max is row shift
  } else if ((shiftColumns(matrix) == 0) && ((shiftRows(matrix) == 0))) { //if both are 0 cause no combos
    max = maxMatrix(matrix); //set max to max value found in matrix
  } else {
    printf ("Eh? "); //something weird happened
  }
  printf ("The largest value is %d.\n", max); //print max we found

  return 0;

}
