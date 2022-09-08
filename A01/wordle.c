#include <stdio.h>
#include <string.h>
#include <time.h>
#include "words.h" // header that defined chooseWord()

int main() {
  srand(time(0));
  const char* word = chooseWord();
  printf("cheat: %s\n", word);

  return 0;
}
