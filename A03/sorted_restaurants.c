//Author: Talia Feshbach
//Date: 9/30/22
//Name: Sorted Restaurants

#include <stdio.h>
#include <stdlib.h> //includes others
#include <string.h> //includes string functions

struct restaurant { //restaurant struct
  char name[32]; //space for restaurant name
  int opentime; 
  int closetime;
  float stars;
  struct restaurant* next; //pointer to next restaurant
};

struct restaurant* insertSorted(struct restaurant* head) { //insert a resturant at the correct place
  struct restaurant* n = malloc(sizeof(struct restaurant)); //malloc space for the restaurant
  if (n == NULL) { //if we're out of space
    printf("ERROR: Out of space!\n"); //scream
    exit(1);
  }

  char name[32];
  int open;
  int close;
  float stars;
  
  printf("Enter a name: "); 
  scanf(" %[^\n]%*c", name); //scan in name
  strcpy(n->name, name);

  printf("Open time: ");
  scanf(" %d%*c", &open); //scan in opening time
  n->opentime = open;

  printf("Close time: ");
  scanf(" %d%*c", &close); //scan in closing time
  n->closetime = close;

  printf("Stars: ");
  scanf(" %f%*c", &stars); //scan in stars
  n->stars = stars;

  if (head == NULL) { //if this is the first node
    n->next = NULL; //point to null
    head = n; //this is the head
  } else if ((head->stars < n->stars)){ //if n stars is bigger than head stars
      n->next = head; //point to head
      head = n; //set n as head
  } else {
    struct restaurant* temp = head; //temp value is head
    while (temp != NULL) { //while there is still another node
      if ((temp->stars >= n->stars) && temp->next == NULL) {
        //if temp is bigger and there's nothing after it
        temp->next = n; //head points to n
        n->next = NULL; //n points to null
        break;
      } else if ((temp->stars >= n->stars) && temp->next != NULL) {
        //if head is bigger than current and something is after it
          if (temp->next->stars < n->stars) { //if the thing after it is smaller
            n->next = temp->next;
            temp->next = n;
            break;
          } else { //if it's bigger
            temp = temp->next; //move temp to it and move on
          }
      }
    }
  }
  return head; //return the head
 }


void clear (struct restaurant* head) {
  struct restaurant* current = head; //current value is head
  struct restaurant* to_delete = head; //value to delete is head
  while (current != NULL) { //if the current value exists
    current = current->next; //current is now next
    free(to_delete); //delete to delete
    to_delete = current; //set to delete to current
  }
}


int main() {
  int choices;
  printf("Enter a number of restaurants: ");
  scanf(" %d", &choices); //scan in number of choices


struct restaurant* head = NULL; //null restaurant to be filled later

  for (int i = 0; i < choices; i++) { //for every restaurant
    head = insertSorted(head); //create a value in list
  }

  printf("Welcome to Talia Feshbach's Sorted Restarant List.\n");
  printf("\n"); //print stuff

  struct restaurant* temp = head; //temporary value to iterate through list
  for (int i = 0; i < choices; i++) { //restaurant table
    printf("%d) %s    open: %d:00     close: %d:00    stars: %f\n", i, temp->name, temp->opentime, temp->closetime, temp->stars);
    temp = temp->next; //set temp to next
  }
 
  clear(head); //clear the list
  return 0;
}
