// Kyle Newman -- knewman2 -- Lab 6 -- Game of Life Functions file
#include <stdio.h>
#include "lifefunc.h"

// makes the board for the game
void board(char board[][SIZE])
{
  int i, j;
  for (j = 0; j <= SIZE-1; j++) {
    board[0][j] = '-';
  }

  for (i = 1; i <= SIZE-2; i++) {
    board[i][0] = '|';
    for (j = 1; j <= SIZE-2; j++) {
      board[i][j] = ' ';
    }
    board[i][SIZE-1] = '|';
  }

  for (j = 0; j <= SIZE-1; j++) {
    board[SIZE-1][j] = '-';
  }
}

// displays the current state of the playing board 
void display(char board[SIZE][SIZE])
{
  int i, j;
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++)
      printf("%c", board[i][j]);
    printf("\n");
  }
}

// add an x (live cell) at the coordinate the user chooses
void addCell(char board[][SIZE], int x, int y)
{
  char add = 'x';
  board[y+1][x+1] = add;
}

// remove a cell/adding a space (killing a cell) at the coordinate the user chooses
void removeCell(char board[][SIZE], int x, int y)
{
  char remove = ' ';
  board[y+1][x+1] = remove;
}

// one iteration of the game of life
void interactive(char mainBoard[][SIZE], char tempBoard[][SIZE])
{
  int x, y;
  int count = 0;
  for (y = 1; y < SIZE-1; y++) {
    for (x = 1; x < SIZE-1; x++) {
      if (tempBoard[y-1][x] == 'x')
        count += 1;
      if (tempBoard[y+1][x] == 'x')
        count += 1;
      if (tempBoard[y][x-1] == 'x')
        count += 1;
      if (tempBoard[y][x+1] == 'x')
        count += 1;
      if (tempBoard[y-1][x-1] == 'x')
        count += 1;
      if (tempBoard[y-1][x+1] == 'x')
        count += 1;
      if (tempBoard[y+1][x-1] == 'x')
        count += 1;
      if (tempBoard[y+1][x+1] == 'x')
        count += 1;
      
      if (tempBoard[y][x] == ' ') {
        if (count == 3)
          mainBoard[y][x] = 'x';
        else
          mainBoard[y][x] = ' ';
      }
      else {
        if(count == 2 || count == 3)
          mainBoard[y][x] = 'x';
        else
          mainBoard[y][x] = ' ';
      }
      count = 0;
    }      
  }
}

// copies the current state of the main game board to the temporary board so the next iteration of the game of life can operate correctly
void copyBoard(char mainBoard[][SIZE], char tempBoard[][SIZE])
{
  int i, j;
  for (j = 0; j < SIZE; j++) {
    for (i = 0; i < SIZE; i++) {
      tempBoard[j][i] = mainBoard[j][i];
    }
  }
} 
