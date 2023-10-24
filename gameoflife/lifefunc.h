// Kyle Newman -- knewman2 -- Lab 6 -- Game of Life Function headers

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 42 // declared a size of 42 so that the actual playing board is 40x40 (not counting the borders)

void board(char[][SIZE]);
void display(char[SIZE][SIZE]);
void addCell(char[][SIZE], int, int);
void removeCell(char[][SIZE], int, int);
void interactive(char[][SIZE], char[][SIZE]);
void copyBoard(char[][SIZE], char[][SIZE]);
 
