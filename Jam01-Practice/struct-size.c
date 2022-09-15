#include <stdlib.h> //includes others
#include <stdio.h> //includes printf and scanf
#include <string.h> //includes string functions

struct Snack {
        char name[32];
        int quantity;
        float cost;
        };

int main(){
    struct Snack snack1;
    printf("Size of Snack: %lu \n", sizeof(snack1));
}