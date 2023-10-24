//  Kyle Newman -- knewman2 -- Lab 6 -- Game of Life Main file
#include <stdio.h>
#include "lifefunc.h"

int main(int argc, char *argv[])
{
  char gameBoard[SIZE][SIZE];
  char tempBoard[SIZE][SIZE];
  board(gameBoard);
  board(tempBoard);
  int n1, n2;
  char choice;
  FILE *fp;

  // interactive mode where the user adds/removes cells of their choosing and can progress the game one iteration at a time or run it continuously
  if (argc == 1) {
    while (choice != 'q') {
      printf("Enter your arguments: ");
      scanf("%c", &choice);
      if (choice == 'a') {
        scanf("%d %d", &n1, &n2);
        addCell(tempBoard, n1, n2);
        display(tempBoard);
      }
      if (choice == 'r') {
        scanf("%d %d", &n1, &n2);
        removeCell(tempBoard, n1, n2);
        display(tempBoard);
      }
      if (choice == 'n') {
        interactive(gameBoard, tempBoard);
        display(gameBoard);
        copyBoard(gameBoard, tempBoard);
      }
      if (choice == 'p') {
        while(1) {
          interactive(gameBoard, tempBoard); 
          display(gameBoard);
          copyBoard(gameBoard, tempBoard);
          usleep(400000); // pauses the iterations of the game for a bit so it is visible
          system("clear"); // clears terminal
        }  
      }
      getchar();
    }
  }

  // same thing but if the user enters a file name after the executable
  else if (argc == 2) {
    fp = fopen(argv[1], "r");
    while(1) {
      fscanf(fp, "%c", &choice);
      if (choice == 'a') {
        fscanf(fp, "%d %d", &n1, &n2);
        addCell(tempBoard, n1, n2);
        display(tempBoard);
      }
      if (choice == 'r') {
        fscanf(fp, "%d %d", &n1, &n2);
        removeCell(tempBoard, n1, n2);
        display(tempBoard);
      }
      if (choice == 'n') {
        interactive(gameBoard, tempBoard);
        display(gameBoard);
        copyBoard(gameBoard, tempBoard);
      }
      if (choice == 'p') {
        while(1) {
          interactive(gameBoard, tempBoard);
          display(gameBoard);
          copyBoard(gameBoard, tempBoard);
          usleep(400000); // pauses the iterations of the game for a bit so it is visible      
          system("clear"); // clears terminal
        }
      }
    }
  }
  else {
    printf("Error: too many arguments\n");
    return 1;
  }

  return 0;
}

