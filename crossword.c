// Kyle Newman -- knewman2 -- Lab 8 Crossword -- crossword.c
// Main file -- activates one of the three modes based on command line input

#include "crossfunc.h"

int main(int argc, char *argv[])
{
  char wordsList[WORDMAX][LENGTHMAX];
  Crossword data[WORDMAX];

  char board1[SIZE][SIZE];
  char board2[SIZE][SIZE];
  initBoard(board1);
  puzzleBoard(board2);

  if (argc == 1)
    interactive(wordsList, board1, board2, data);
  
  else if (argc == 2)
    inputMode(argv[1], wordsList, board1, board2, data);

  else if (argc == 3)
    outputMode(argv[1], argv[2], wordsList, board1, board2, data);
  
  else {
    printf("Too many arguments.\n");
    return 1;
  }

  return 0;
}
