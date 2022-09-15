#include <stdlib.h> //includes others
#include <stdio.h> //includes printf and scanf
#include <string.h> //includes string functions

int power(int base, int exp){
    int result = 1;
    int i = 0;
    while (i<exp) {
        result = result * base;
        i++;
    }
    return result;

}

int main(){
    int base, exp;
    printf("Give me a base: ");
    scanf("%d", &base);
    printf("Give me a power: ");
    scanf("%d", &exp);
    int result = power(base, exp);
    printf("The result is %d.\n", result);
}