#include <stdio.h>
#include <stdlib.h> //includes others
#include <string.h> //includes string functions

struct restaurant { //restaurant struct
  char name[32]; //space for restaurant name
  int opentime;
  int closetime;
  float stars;
};

void enterRest(struct restaurant restList[], int position) {
  char name[32];
  int open;
  int close;
  float stars;
  printf("Enter a name: "); 
  scanf(" %[^\n]%*c", name); //scan in name
  strcpy(restList[position].name, name);

  printf("Open time: ");
  scanf(" %d%*c", &open); //scan in opening time
  restList[position].opentime = open;

  printf("Close time: ");
  scanf(" %d%*c", &close); //scan in closing time
  restList[position].closetime = close;

  printf("Stars: ");
  scanf(" %f%*c", &stars); //scan in stars
  restList[position].stars = stars;
}


int main() {
  int choices;
  printf("Enter a number of restaurants: ");
  scanf(" %d", &choices); //scan in number of choices

  struct restaurant *restList = malloc(sizeof(struct restaurant) * choices);
  //allocate space for restaurant list

  for (int i = 0; i < choices; i++) { //for every restaurant
    enterRest(restList, i);
  }

  printf("Welcome to Talia Feshbach's Dynamic Restarant List.\n");

  for (int i = 0; i < choices; i++) { //restaurant table
    printf("%d) %s    open: %d:00     close: %d:00    stars: %f\n", i, restList[i].name, restList[i].opentime, restList[i].closetime, restList[i].stars);
  }

  free (restList); //freeing rest List
  return 0;
}
