#include <stdlib.h> //includes others
#include <stdio.h> //includes printf and scanf
#include <string.h> //includes string functions

struct node { 
    int row; //row of brace
    int column; //column of brace
    struct node* next; //next node
};

struct node* push(int row, int column, struct node* head){ //essentially inserting at front
    struct node* n = malloc(sizeof(struct node)); //malloc space for node
    if (n == NULL) { //if we're out of space
        printf("ERROR: Out of space!\n"); //scream
        exit(1); //and leave
    }
    n->row = row;
    n->column = column;
    n->next = head;
    return n;
}

struct node* pop(struct node* popped){ //essentially popping from front, returning new head
    struct node* head = popped->next; //making new head next node
    free(popped); //bye-bye old head
    return head; //return new head
}

void printer(struct node* printed){ //printer for debugging and also just printing
    printf("(%d, %d)", printed->row, printed->column);
}

void clear(struct node* head){ //frees all remaining nodes and prints where they were
    struct node* current = head; 
    struct node* to_delete = head;
    while (current != NULL) { //while current isn't null
        printf("Unmatched brace on Line %d and Column %d\n", current->row, current->column);
        //if there's an extra unmatched brace, say where
        current = current->next;
        free(to_delete); //delete node
        to_delete = current;
    }
}

int main(int argc, char** argv) {
    if (argc != 2) { //if not enough arguments
        printf("usage: ./match_braces\n"); //scream
        exit(1); //and leave
    }
    FILE *infile; //file set up
    infile = fopen(argv[1], "r"); //read in file
    if (infile == NULL) { //if file invalid
        printf("Cannot open file: %s\n", argv[1]); //scream
        exit(1); //and leave
    }
    int lineNumber = 1; //files start counting lines at 1
    int columnNumber = 1; //files start counting columns at 1, I think
    char ch = fgetc(infile); //get first char
    struct node* head = NULL;
    while(ch != EOF){ //while char is not end of file
        if (ch == '{'){ //if char starting brace
            head = push(lineNumber, columnNumber, head); //push location 
        } else if (ch == '}') { //if char ending brace
            if (head != NULL) { //if list not empty
                printf("Found matching braces: "); //print locations of
                printer(head); //start brace
                printf(" -> (%d, %d)\n", lineNumber, columnNumber); //and end brace
                head = pop(head); //then pop that start brace out
            } else { //if list empty
                printf("Unmatched brace on Line %d and Column %d\n", lineNumber, columnNumber);
                //note that this end brace doesn't have a match
            }
        } else if (ch == '\n'){ //if we reach newline char
            lineNumber++; //updates the line number
            columnNumber = 0; //will be increased to 1 below
        }
        columnNumber++; //moving on to next column position
        ch = fgetc(infile); //read in new char
    }
    clear(head); //once we've read everything in, if we have extra start braces, note that and free them
    fclose(infile); //closes file we read in
    return 0;
}