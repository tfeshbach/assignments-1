#include <stdlib.h> //includes others
#include <stdio.h> //includes printf and scanf
#include <string.h> //includes string functions

struct restaurant {
  char name[75]; //space for restaurant name
  int opentime;
  int closetime;
  float stars;
};

int main() {
  int hour;
  struct restaurant rest0, rest1, rest2; 
  strcpy(rest0.name, "Sushi Atsumi"); //set restaurant values
  rest0.opentime = 11;
  rest0.closetime = 23;
  rest0.stars = 3.5;
  strcpy(rest1.name, "The Thirsty Horse");
  rest1.opentime = 17;
  rest1.closetime = 2;
  rest1.stars = 4.5;
  strcpy(rest2.name, "Magic Bean Coffee");
  rest2.opentime = 6;
  rest2.closetime = 15;
  rest2.stars = 4.1;

  printf("Welcome to Talia Feshbach's Restarant List.\n");
  printf("What hour is it (24 hr clock)? ");
  scanf("%d", &hour); //scan in hour

  printf("0) %s    open: %d:00     close: %d:00    stars: %f\n", rest0.name, rest0.opentime, rest0.closetime, rest0.stars);
  printf("1) %s    open: %d:00     close: %d:00    stars: %f\n", rest1.name, rest1.opentime, rest1.closetime, rest1.stars);
  printf("2) %s    open: %d:00     close: %d:00    stars: %f\n", rest2.name, rest2.opentime, rest2.closetime, rest2.stars);
  
  int choicenum; //scan in restaurant number choice
  printf("What restaurant do you want to visit? [0,1,2] ");
  scanf("%d", &choicenum);
  struct restaurant choicerest;
  if (choicenum == 0) { //select correct restaurant from number choice
    choicerest = rest0;
  } else if (choicenum == 1) {
    choicerest = rest1;
  } else if (choicenum == 2){
    choicerest = rest2;
  } else {
    printf("That's not a valid choice buddy.");
  }

  if ((hour < choicerest.opentime) && ((choicerest.opentime - hour) < 6)) { //if it opens within 6 hours, go with opening time
    printf("%s isn't open until %d o'clock!!\n", choicerest.name, choicerest.opentime);
  } else if (hour > choicerest.closetime) {
    printf("%s closed at %d o'clock!!\n", choicerest.name, choicerest.closetime);
  } else {
    printf("Excellent choice. %s is open for %d more hours.\n", choicerest.name, (choicerest.closetime - hour));
  }
  return 0;
}
