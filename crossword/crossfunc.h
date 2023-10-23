// Kyle Newman -- knewman2 -- Lab 8 Crossword -- crossfunc.h
// Function headers

#define _GNU_SOURCE // stirfry
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // stirfry
#define SIZE 15 // crossword board size
#define WORDMAX 20 // max words read/input
#define LENGTHMAX 15 // max length of words
#define MAXINPUT 100 // for reading words from the user or file
#define MIDDLE 7 // middle index of the crossword board

// Crossword struct, contains x and y starting coordinates, word direction, and the word itself, for each word placed in the crossword
typedef struct {
  int x;
  int y;
  char direction;
  char words[LENGTHMAX];
} Crossword;

void initBoard(char[SIZE][SIZE]); // initializes the solution board
void puzzleBoard(char[SIZE][SIZE]); // initializes the puzzle board
void interactive(char[WORDMAX][LENGTHMAX], char[SIZE][SIZE], char[SIZE][SIZE], Crossword[]); // interactive mode, where the user enters words to be placed in the crossword and the crossword is printed in the terminal
int inputMode(char *, char[WORDMAX][LENGTHMAX], char[SIZE][SIZE], char[SIZE][SIZE], Crossword[]); // mode where the words are read from a file and the crossword is printed in the terminal
int outputMode(char *, char *, char[WORDMAX][LENGTHMAX], char[SIZE][SIZE], char[SIZE][SIZE], Crossword[]); // mode where the words are read from a file and everything is output in a file
void display(char[SIZE][SIZE]); // display the crossword board
void display2(FILE *, char[SIZE][SIZE]); // same thing as above, but used for third mode -- display board in file
void uppercase(char[], int); // convert all words to uppercase
void sortWords(char[WORDMAX][LENGTHMAX], int); // sort all words by length, greatest to least
void displayWords(char[WORDMAX][LENGTHMAX], int); // displaying the words after sorted -- was for my own use, not used in final algorithm
void displayWords2(FILE *, char[WORDMAX][LENGTHMAX], int); // displaying the words after sorted -- was for my own use, not used in final algorithm
int isValid(char word[LENGTHMAX], int size); // checks if the word being read (whether from user or in a file) is valid
void editSolution(char[SIZE][SIZE], int, int, char); // edit the solution board
void editPuzzle(char[SIZE][SIZE], char[SIZE][SIZE]); // edit the puzzle board
void firstWord(char[], char[SIZE][SIZE], Crossword[]); // placing the first word on the crossword
void secondWord(char[], char[SIZE][SIZE], Crossword[]); // placing the second word on the crossword -- was for my own use, not used in final algorithm
int makeCrossword(char[][LENGTHMAX], char[][SIZE], Crossword[], int); // placing all words after the first word on the crossword; the overarching algorithm function
int makeCrossword2(FILE *, char[][LENGTHMAX], char[][SIZE], Crossword[], int); // same thing as above, but used for third mode
int tryWord(char[][LENGTHMAX], char[][SIZE], Crossword[], int); // finds intersections in words to check if they can be placed in the crossword -- called in the makeCrossword function
int tryWord2(FILE *, char[][LENGTHMAX], char[][SIZE], Crossword[], int); // same thing as above, but used for third mode -- prints skipped word message in file
int check(Crossword, char[], char [][SIZE], int, int); // does the checking to see if a word can be placed in the crossword -- called in tryWord function
void placeWord(Crossword, char[], char[][SIZE], int, int); // places the word if check function is satisfied -- called in tryWord function
void displayClues(Crossword[], int); // display the clues for the crossword puzzle
void displayClues2(FILE *, Crossword[], int); // same thing as above, but used for third mode -- prints clues to file
