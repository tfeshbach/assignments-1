#include <stdio.h>
#include <string.h>
#include <time.h>
#include "words.h" // header that defined chooseWord()

//a little funky when words have repeat letters ie repeats messages

int guessing (const char word[], char* guess) {
  printf("Please enter a 5-letter word:");
  scanf(" %s", guess);
  int success = 5; //records how many correct letters there are
  for (int i = 0; i < 5; i++) { //loop for place in guess
    int present = 0; //is the letter in guess present?
    for (int j = 0; j < 5; j++){ //loop for place in word
      if (guess[i] == word[j] && i == j) { //if the char is in the word AND the right spot
        printf("%c is in the word AND in the correct spot!\n", guess[i]);
        present = 1; 
        success = success - 1;
      } else if (guess[i] == word[j] && i != j && present==0) { //if the char is in the word but NOT the right spot
        printf("%c is in the word (but not in the correct spot!)\n", guess[i]);
        present = 1;
      } 
    }
    if (present == 0) { //if letter wasn't marked present
      printf("%c is NOT in the word.\n", guess[i]);
    }
  }

  if (success == 0) { //if we guessed it correctly
    printf("You guessed it! The word is %s\n", word);
    return 1;
  }
  return 0;
}

int main() {
  srand(time(0));
  const char* word = chooseWord();
  char guess[6];
  int guessed = 0;
  int count = 0;
  printf("Welcome to Wordle!\n");

  while ((guessed == 0) && (count < 6)) { //six tries
    guessed = guessing(word, guess); //5 letter word, one more space for end char
    count++;
  }

  if (guessed == 0) {
    printf("Sorry, you ran out of tries. The word is %s.\n", word);
  } else {
    printf("You took %d tries to guess the word.\n", count);
  }
  
  //printf("cheat: %s\n", word);

  return 0;
}
