#include <stdio.h>
#include <stdlib.h> //includes others
#include <string.h> //includes string functions

void slowSpeech(char *slowText, char *text, int pause) { //take in allocated space, text, and pause
  for (int i = 0; i < (strlen(text)); i++) { //go for as long as the text (including end token)
    slowText[i * (pause + 1)] = text[i]; //add text character
    for (int j = 1; j <= pause; j++) { 
      slowText[(i * (pause + 1)) + j] = '.'; //add pauses in between
    }
  }
  int stringlen = (int) strlen(text); //cast to integer
  slowText[((stringlen) * pause) + stringlen] = '\0'; //add end character at end of string
}


int main() {
  int pause; 
  char text[32];
  printf("Pause length: "); 
  scanf(" %d", &pause); //read in pause length
  printf("Text: ");
  scanf(" %s", text);  //read in text

  int stringlen = (int) strlen(text); //casting text length to int
  int totalSize = ((stringlen) * pause) + stringlen + 1; //total size of new string with spaces

  char *slowText = NULL; 
  slowText = malloc(sizeof(char) * totalSize); //allocate memory for slow text
  slowSpeech(slowText, text, pause); //call slowing down
  printf(" %s \n", slowText); //print slowed text
  free(slowText); //free slow text
  return 0;
}
