// Kyle Newman -- knewman2 -- Lab 8 Crossword -- crossfunc.c
// Function definitions

#include "crossfunc.h"

void initBoard(char board[SIZE][SIZE])
{
  int i, j;
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      board[i][j] = '.';
}

void puzzleBoard(char board[SIZE][SIZE])
{
  int i, j;
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      board[i][j] = '#';
}

void interactive(char wordsList[WORDMAX][LENGTHMAX], char solBoard[SIZE][SIZE], char puzzBoard[SIZE][SIZE], Crossword crossword[WORDMAX])
{
  char word[MAXINPUT];
  int length = 0;
  int count;
  printf("Anagram Crossword Puzzle Generator\n----------------------------------\n\n");
  printf("Enter a list of words:\n");
    while(1) {
      scanf("%s", word);
      if (strcmp(word, ".") == 0) break;
      if (isValid(word, strlen(word)) == 0) {
        printf("Word %s is not valid\n", word);
        continue;
      }
      uppercase(word, strlen(word));
      strcpy(wordsList[length], word);
      length++;
      if (length == WORDMAX) break;
    }
  sortWords(wordsList, length);
  //displayWords(wordsList, length);
  count = makeCrossword(wordsList, solBoard, crossword, length); // count is length of struct, which is how many words are in the crossword, length is how many words were read/input to be potentially used by the crossword
  printf("\nSolution:\n");
  display(solBoard);
  editPuzzle(solBoard, puzzBoard);
  printf("\nCrossword Puzzle:\n");
  display(puzzBoard);
  displayClues(crossword, count);
}

int inputMode(char *infile, char wordsList[WORDMAX][LENGTHMAX], char solBoard[SIZE][SIZE], char puzzBoard[SIZE][SIZE], Crossword crossword[WORDMAX])
{
  FILE *fp;
  char word[MAXINPUT];
  int length = 0;
  int count;
  fp = fopen(infile, "r");
  if (!fp) {
    printf("File %s not found\n", infile);
    return 1;
  }
  printf("Anagram Crossword Puzzle Generator\n----------------------------------\n\n");
  while(1) {
    fscanf(fp, "%s", word);
    if (strcmp(word, ".") == 0) break;
    if (isValid(word, strlen(word)) == 0) {
      printf("Word %s is not valid\n", word);
      continue;
    }
    uppercase(word, strlen(word));
    strcpy(wordsList[length], word);
    length++;
    if (length == WORDMAX) break;
  }
  sortWords(wordsList, length);
  //displayWords(wordsList, length);
  count = makeCrossword(wordsList, solBoard, crossword, length);
  printf("\nSolution:\n");
  display(solBoard);
  editPuzzle(solBoard, puzzBoard);
  printf("\nCrossword Puzzle:\n");
  display(puzzBoard);
  displayClues(crossword, count);
  return 0;
}

int outputMode(char *infile, char *outfile, char wordsList[WORDMAX][LENGTHMAX], char solBoard[SIZE][SIZE], char puzzBoard[SIZE][SIZE], Crossword crossword[WORDMAX])
{
  FILE *fp, *fp2;
  char word[MAXINPUT];
  int length = 0;
  int count;
  fp = fopen(infile, "r");
  if (!fp) {
    printf("File %s not found\n", infile);
    return 1;
  }
  fp2 = fopen(outfile, "w");
  while(1) {
    fscanf(fp, "%s", word);
    if (strcmp(word, ".") == 0) break;
    if (isValid(word, strlen(word)) == 0) {
      fprintf(fp2, "Word %s is not valid\n", word);
      continue;
    }
    uppercase(word, strlen(word));
    strcpy(wordsList[length], word);
    length++;
    if (length == WORDMAX) break;
  }
  fprintf(fp2, "Anagram Crossword Puzzle Generator\n----------------------------------\n\n");
  sortWords(wordsList, length);
  //displayWords2(fp2, wordsList, length);
  count = makeCrossword2(fp2, wordsList, solBoard, crossword, length);
  fprintf(fp2, "\nSolution:\n");
  display2(fp2, solBoard);
  editPuzzle(solBoard, puzzBoard);
  fprintf(fp2, "\nCrossword Puzzle:\n");
  display2(fp2, puzzBoard);
  displayClues2(fp2, crossword, count);
  fclose(fp2);
  return 0;
}

void display(char board[SIZE][SIZE])
{
  int i, j, k;
  for (k = 0; k < SIZE+2; k++)
    printf("%c", '-');
  printf("\n");
  for (i = 0; i < SIZE; i++) {
    printf("%c", '|');
    for (j = 0; j < SIZE; j++)
      printf("%c", board[i][j]);
    printf("%c", '|');
    printf("\n");
  }
  for (k = 0; k < SIZE+2; k++)
    printf("%c", '-');
  printf("\n");
}

void display2(FILE *fp, char board[SIZE][SIZE])
{
  int i, j, k;
  for (k = 0; k < SIZE+2; k++)
    fprintf(fp, "%c", '-');
  fprintf(fp, "\n");
  for (i = 0; i < SIZE; i++) {
    fprintf(fp, "%c", '|');
    for (j = 0; j < SIZE; j++)
      fprintf(fp, "%c", board[i][j]);
    fprintf(fp, "%c", '|');
    fprintf(fp, "\n");
  }
  for (k = 0; k < SIZE+2; k++)
    fprintf(fp, "%c", '-');
  fprintf(fp, "\n");
}

void uppercase(char word[], int size)
{
  int i;
  for (i = 0; i < size; i++) {
    word[i] = toupper(word[i]);
  }
}

void sortWords(char words[WORDMAX][LENGTHMAX], int size)
{
  int i, j;
  for (i = 0; i < size-1; i++)
    for (j = 0; j < size-i-1; j++)
      if (strlen(words[j]) < strlen(words[j+1])) {
        char temp[LENGTHMAX];
        strcpy(temp, words[j]);
        strcpy(words[j], words[j+1]);
        strcpy(words[j+1], temp);
      }
}

void displayWords(char words[WORDMAX][LENGTHMAX], int size)
{
  int i;
  for (i = 0; i < size; i++)
    printf("%s\n", words[i]);
}

void displayWords2(FILE *fp, char words[WORDMAX][LENGTHMAX], int size)
{
  int i;
  for (i = 0; i < size; i++)
    fprintf(fp, "%s\n", words[i]);
}

int isValid(char word[LENGTHMAX], int size)
{
  if ((size < 2) || (size > 15)) {
    return 0;
  }
  int i;
  int c;
  for (i = 0; i < size; i++) {
    c = ("%d", word[i]);
    if (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122)))
      return 0;
  }
  return 1;
}

void editSolution(char board[SIZE][SIZE], int y, int x, char c) // row (y) then column (x)
{
  board[y][x] = c;
}

void editPuzzle(char solBoard[SIZE][SIZE], char puzzBoard[SIZE][SIZE])
{
  int i, j;
  for (j = 0; j < SIZE; j++) {
    for (i = 0; i < SIZE; i++) {
      if (solBoard[j][i] == '.')
        puzzBoard[j][i] = '#';
      else
        puzzBoard[j][i] = ' ';
    }
  }
}

void firstWord(char word[], char solBoard[SIZE][SIZE], Crossword crossword[WORDMAX]) // finds middle letter, prints that in the middle, then prints letters to the left, then to the right
{
  int middleIndex = strlen(word)/2;
  int start;
  editSolution(solBoard, MIDDLE, MIDDLE, word[middleIndex]); // middle letter
  int i;
  int j = 1;
  start = MIDDLE;
  for (i = middleIndex-1; i >= 0; i--) { // print letters to the left
    editSolution(solBoard, MIDDLE, MIDDLE-j, word[i]);
    start = MIDDLE-j;
    j++;
  }
  j = 1;
  for (i = middleIndex+1; i < strlen(word); i++) { // print letters to the right
    editSolution(solBoard, MIDDLE, MIDDLE+j, word[i]);
    j++;
  }
  crossword[0].x = start;
  crossword[0].y = MIDDLE;
  crossword[0].direction = 'a'; // a for across, d for down
  strcpy(crossword[0].words, word);  
}

void secondWord(char word[], char solBoard[SIZE][SIZE], Crossword crossword[WORDMAX]) // this was temporary -- not used after making crossword algorithm, which can be applied to all words after the first
{
  int i, j, index, intersect, flag, start;
  for (i = 0; i < strlen(word); i++) {
    for (j = 0; j < SIZE; j++) {
      if (word[i] == solBoard[MIDDLE][j]) {
        index = i;
        intersect = j;
        flag = 1;
        break;
      }
    }
    if (flag == 1) break;
  }
  int k = 1;
  start = MIDDLE; // if the intersect occurs at the beginning
  for (i = index-1; i >= 0; i--) {
    editSolution(solBoard, MIDDLE-k, intersect, word[i]);
    start = MIDDLE-k;
    k++;
  }
  k = 1;
  for (j = index+1; j < strlen(word); j++) {
    editSolution(solBoard, MIDDLE+k, intersect, word[j]);
    k++;
  }
  crossword[1].x = intersect;
  crossword[1].y = start;
  crossword[1].direction = 'd';
  strcpy(crossword[1].words, word);
}


int makeCrossword(char wordsList[WORDMAX][LENGTHMAX], char solBoard[SIZE][SIZE], Crossword crossword[WORDMAX], int size)
{
  int structSize;
  firstWord(wordsList[0], solBoard, crossword);
  //secondWord(wordsList[1], solBoard, crossword); // was temporary -- not needed after making crossword algorithm for the rest of the words, algorithm starts after first word
  structSize = tryWord(wordsList, solBoard, crossword, size);
  return structSize;
}

int makeCrossword2(FILE *fp, char wordsList[WORDMAX][LENGTHMAX], char solBoard[SIZE][SIZE], Crossword crossword[WORDMAX], int size)
{
  int structSize;
  firstWord(wordsList[0], solBoard, crossword);
  structSize = tryWord2(fp, wordsList, solBoard, crossword, size);
  return structSize;
}

int tryWord(char wordsList[][LENGTHMAX], char solBoard[SIZE][SIZE], Crossword crossword[WORDMAX], int size) // crossword will be the previous word that word is compared to
{  
  int i, j, k, l;
  int xIndex;
  int yIndex;
  int placedWord;
  int structSize = 1;
  for (i = 1; i < size; i++) { // i is index of words list
    placedWord = 0;
    for (j = 0; j < structSize; j++) { // j is index of structs
      for (k = 0; k < strlen(wordsList[i]); k++) { // k is index of word characters
        for (l = 0; l < strlen(crossword[j].words); l++) { // l is index of struct word characters
          if (crossword[j].words[l] == wordsList[i][k]) {
            if (crossword[j].direction == 'a') { // index of intersections of the words, varies on direction, will be used to find new x and y coordinate of hypothetical new word placement
              xIndex = l;
              yIndex = k;
            }
            else if (crossword[j].direction == 'd') {
              xIndex = k;
              yIndex = l;
            }
            if (check(crossword[j], wordsList[i], solBoard, xIndex, yIndex) == 1) {
              placedWord = 1;
              placeWord(crossword[j], wordsList[i], solBoard, xIndex, yIndex);
              strcpy(crossword[structSize].words, wordsList[i]);
              if (crossword[j].direction == 'a') {
                crossword[structSize].x = crossword[j].x + xIndex; // next words starting x coordinate and y coordinate, varies based on direction
                crossword[structSize].y = crossword[j].y - yIndex;
                crossword[structSize].direction = 'd';
              }
              else if (crossword[j].direction == 'd') {
                crossword[structSize].direction = 'a';
                crossword[structSize].x = crossword[j].x - xIndex;
                crossword[structSize].y = crossword[j].y + yIndex;
              }
              structSize++;
              break;
            } 
          }
        }
        if (placedWord == 1) break;
      }
      if (placedWord == 1) break;
    }
    if (placedWord == 0)
      printf("\"%s\" could not be placed on the crossword\n", wordsList[i]);
  }
  return structSize;
}

int tryWord2(FILE *fp, char wordsList[][LENGTHMAX], char solBoard[SIZE][SIZE], Crossword crossword[WORDMAX], int size)
{
  int i, j, k, l;
  int xIndex;
  int yIndex;
  int placedWord;
  int structSize = 1;
  for (i = 1; i < size; i++) { // i is index of words list
    placedWord = 0;
    for (j = 0; j < structSize; j++) { // j is index of structs
      for (k = 0; k < strlen(wordsList[i]); k++) { // k is index of word characters
        for (l = 0; l < strlen(crossword[j].words); l++) { // l is index of struct word characters
          if (crossword[j].words[l] == wordsList[i][k]) {
            if (crossword[j].direction == 'a') {
              xIndex = l;
              yIndex = k;
            }
            else if (crossword[j].direction == 'd') {
              xIndex = k;
              yIndex = l;
            }
            if (check(crossword[j], wordsList[i], solBoard, xIndex, yIndex) == 1) {
              placedWord = 1;
              placeWord(crossword[j], wordsList[i], solBoard, xIndex, yIndex);
              strcpy(crossword[structSize].words, wordsList[i]);
              if (crossword[j].direction == 'a') {
                crossword[structSize].x = crossword[j].x + xIndex;
                crossword[structSize].y = crossword[j].y - yIndex;
                crossword[structSize].direction = 'd';
              }
              else if (crossword[j].direction == 'd') {
                crossword[structSize].direction = 'a';
                crossword[structSize].x = crossword[j].x - xIndex;
                crossword[structSize].y = crossword[j].y + yIndex;
              }
              structSize++;
              break;
            }
          }
        }
        if (placedWord == 1) break;
      }
      if (placedWord == 1) break;
    }
    if (placedWord == 0)
      fprintf(fp, "\"%s\" could not be placed on the crossword\n", wordsList[i]);
  }
  return structSize;
}
      
int check(Crossword crossword, char word[], char solBoard[SIZE][SIZE], int xIndex, int yIndex)
{
  int x, y, i;
  int length = strlen(word);
  // if the most recently placed  word is across, new word will be down, and is evaluated as so -- as can be seen, many of these functions are differently evaluated based on direction
  if (crossword.direction == 'a') { // use x andd y indexes found in tryWord to find the hypothetical new starting coordinates if a word were to be placed -- varies on direction
    x = crossword.x + xIndex;
    if (!(x > -1 && x < 15)) return 0; // make sure word starts inbounds
    y = crossword.y - yIndex;
    if (!(y > -1 && y < 15)) return 0;
    if (solBoard[y-1][x] != '.' && y >= 0) return 0; // make sure beginning of word doesnt touch another word
    if (y + length > 15) return 0;
    for (i = 0; i < strlen(word); i++) {
      if (i == yIndex) {
        y++;
        continue;
      }
      if (solBoard[y][x-1] != '.' || solBoard[y][x+1] != '.' || solBoard[y][x] != '.') return 0; // make sure word would not touch other words to the sides or overlap
      y++;
    }
    if (solBoard[y][x] != '.' && y < 15) return 0; // make sure end of word doesnt touch another word
  }
  // if the most recently placed word is down, new word will be across, and is evaluated as so
  else if (crossword.direction == 'd') {
    x = crossword.x - xIndex;
    if (!(x > -1 && x < 15)) return 0;
    y = crossword.y + yIndex;
    if (!(y > -1 && y < 15)) return 0;
    if (solBoard[y][x-1] != '.' && x >= 0) return 0;
    if (x + length > 15) return 0;
    for (i = 0; i < strlen(word); i++) {
      if (i == xIndex) {
        x++;
        continue;
      }
      if (solBoard[y-1][x] != '.' || solBoard[y+1][x] != '.' || solBoard[y][x] != '.') return 0; // make sure word would not touch other words above or below or overlap
      x++;
    }
    if (solBoard[y][x] != '.' && x < 15) return 0;   
  }
  return 1;
}

void placeWord(Crossword crossword, char word[], char solBoard[SIZE][SIZE], int xIndex, int yIndex)
{
  int x, y, i;
  if (crossword.direction == 'a') {
    x = crossword.x + xIndex; // new words starting coordinates
    y = crossword.y - yIndex;
    for (i = 0; i < strlen(word); i++) {
      editSolution(solBoard, y, x, word[i]); // placing the word letter by letter
      y++;
    }
  }
  else if (crossword.direction == 'd') {
    x = crossword.x - xIndex;
    y = crossword.y + yIndex;
    for (i = 0; i < strlen(word); i++) {
      editSolution(solBoard, y, x, word[i]);
      x++;
    }
  }
}

void displayClues(Crossword crossword[], int size)
{
  int i;
  char word[LENGTHMAX];
  char directions[size][LENGTHMAX];
  for (i = 0; i < size; i++) {
    if (crossword[i].direction == 'a') strcpy(directions[i], "Across");
    else strcpy(directions[i], "Down");
  }
  printf("\nClues:\n");
  for (i = 0; i < size; i++)
  {
    strcpy(word, crossword[i].words);
    printf("%2d,%2d %-7s %-15s\n", crossword[i].x, crossword[i].y, directions[i], strfry(word));
  }
} 

void displayClues2(FILE *fp, Crossword crossword[], int size)
{
  int i;
  char word[LENGTHMAX];
  char directions[size][LENGTHMAX];
  for (i = 0; i < size; i++) {
    if (crossword[i].direction == 'a') strcpy(directions[i], "Across");
    else strcpy(directions[i], "Down");
  }
  fprintf(fp, "\nClues:\n");
  for (i = 0; i < size; i++)
  {
    strcpy(word, crossword[i].words);
    fprintf(fp, "%2d,%2d %-7s %-15s\n", crossword[i].x, crossword[i].y, directions[i], strfry(word));
  }
}
