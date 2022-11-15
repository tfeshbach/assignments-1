#include <stdio.h>

int main() {
  int a = ?? 
  int b = ??
  int c = mystery(a, b);
  c = foo(c);
  int d = 0;
  printf("Guess the mysterious number: ");  
  scanf(" %d", &d);
  if (c == d) printf("You are right!\n");
  else printf("You are wrong!\n");
}
