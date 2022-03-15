/**
 * Project:  Maturitni projekt šachy
 * Author:   Jakub Urbanek
 * Year:     2022
 */

#include "chess_structs.h"

#include <stdlib.h>
#include <string.h>

Tboard* initBoard()
{
  Tboard *b = malloc(sizeof(Tboard));
  b->canBlackCastle[0] = true;
  b->canBlackCastle[1] = true;
  b->canWhiteCastle[0] = true;
  b->canWhiteCastle[1] = true;
  b->lastMove = malloc(MAX_INP_LEN * sizeof(char));
  strcpy(b->lastMove, "0000");
  b->move = 0;
  b->boringMoveCount = 0;
  b->boringPoss = malloc(0);
  b->pieceCount = 32;

  char temp[8][8] = {
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
  };
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      b->pieces[i][j] = temp[i][j];
    }
  }
  return b;
}

Tboard* copyBoard(const Tboard *input)
{
  Tboard *b = malloc(sizeof(Tboard));
  b->canBlackCastle[0] = input->canBlackCastle[0];
  b->canBlackCastle[1] = input->canBlackCastle[1];
  b->canWhiteCastle[0] = input->canWhiteCastle[0];
  b->canWhiteCastle[1] = input->canWhiteCastle[1];
  b->lastMove = malloc(MAX_INP_LEN * sizeof(char));
  strcpy(b->lastMove, input->lastMove);
  b->move = input->move;
  b->boringMoveCount = input->boringMoveCount;

  b->boringPoss = malloc(b->boringMoveCount * sizeof(char*));
  for(int i = 0; i < b->boringMoveCount; i++){
    b->boringPoss[i] = malloc(POS_STRING_LEN * sizeof(char));
    strcpy(b->boringPoss[i], input->boringPoss[i]);
  }

  b->pieceCount = input->pieceCount;

  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      b->pieces[i][j] = input->pieces[i][j];
    }
  }

  return b;
}

void freeBoard(Tboard* b)
{
  for(int i = 0; i < b->boringMoveCount; i++){
    free(b->boringPoss[i]);
  }
  free(b->boringPoss);

  free(b->lastMove);
  free(b);
}


char* boardToPosString(const Tboard *b)
{
  char *posString = malloc(POS_STRING_LEN * sizeof(char));
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      posString[i*8 + j] = b->pieces[i][j];
    }
  }
  posString[64] = '\0';
  return posString;
}



TmoveList* initMoveList(int n)
{
  TmoveList *ml = malloc(sizeof(TmoveList));
  ml->moves = malloc(n * sizeof(char*));
  for(int i = 0; i < n; i++){
    ml->moves[i] = malloc(MAX_INP_LEN * sizeof(char));
  }
  ml->filled = 0;
  ml->size = n;

  return ml;
}

void reallocMoveList(TmoveList* ml, int n)
{
  ml->moves = realloc(ml->moves, n * sizeof(*ml->moves));
  for(int i = ml->size; i < n; i++){
    ml->moves[i] = malloc(MAX_INP_LEN * sizeof(char));
  }
  ml->size = n;
}

void appendMoveList(TmoveList *ml, char* move)
{
  ml->filled++;

  // if can fit in allocated memory... else realloc
  if(ml->filled <=ml->size){
    strcpy(ml->moves[ml->filled-1], move);
    return;
  }

  reallocMoveList(ml, ml->size * 2);
  strcpy(ml->moves[ml->filled-1], move);
}


void freeMoveList(TmoveList* ml)
{
  for(int i = 0; i < ml->size; i++){
    free(ml->moves[i]);
  }
  free(ml->moves);
  free(ml);
}
