#include <stdio.h>

int main() {
  char message[32];
  printf("Please enter a phrase: ");
  fgets(message, 31, stdin);
  message[31] = '\0';

  // todo: modify message using bitwise operations
  printf("scramble: %s\n", message);
}
