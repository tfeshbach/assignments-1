#include <stdlib.h> //includes others
#include <stdio.h> //includes printf and scanf
#include <string.h> //includes string functions

void remover(char* str, char letter) {
    char newstr[50];
    int i = 0;
    int j = 0;
    while (i < strlen(str)) {
        if (str[i] != letter) {
            newstr[j] = str[i];
            j++;
        }
        i++;
    }
    newstr[j] = '\0';
    strcpy(str, newstr);
}

int main() {
    char str[50] = "tester";
    printf("Old string: %s \n", str);
    char letter = 'e';
    remover(str, letter);
    printf("New string: %s \n", str);
}