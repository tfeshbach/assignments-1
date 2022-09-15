#include <stdlib.h> //includes others
#include <stdio.h> //includes printf and scanf
#include <string.h> //includes string functions

char shifter(char original, int shift) {
  char temp = original + shift;
  if (temp > 'z') { //if we've shifted past z
	  temp = 'a' + (shift - 1); //loop back around to a
	}
  if (temp < 'a') { //if we've shifted before a (a -2)
	  temp = 'z' + (shift + 1); //loop back around to z
	}
  return temp;
}

int main() {
  char word[30]; //set word array
  int shift;
  printf("Enter a word: ");
  scanf(" %s", word); //no ampersand because it's already a pointer
  printf("Enter a shift: ");
  scanf(" %d", &shift);
  char shiftedword[30]; //set shifted word array

  for (int i = 0; i < (strlen(word)); i++){
    shiftedword[i] = shifter(word[i], shift); //call shifter function
  }
  shiftedword[strlen(word)] = '\0'; //add end character to make strings work
  printf(" %s\n", shiftedword); //print shifted word

  
}
