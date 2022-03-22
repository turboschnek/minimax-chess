/**
 * Project:  Maturitni projekt šachy
 * Author:   Jakub Urbanek
 * Year:     2022
 */

#include "move_counter.h"
#include "chess_logic.h"
#include "chess_structs.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


int moveCounterMain(bool debugMode)
{
  char *position = malloc(100 * sizeof(char));
  printf("insert FEN string:\n");
  
  fgets(position, 100, stdin);

  Tboard *b = fenToBoard(position);
  if(b == NULL){
    free(position);
    printf("invalid FEN string\n");
    return 1;
  }

  __ifIsCheckedSetLastMoveToCheck(b);

  printBoard(b);
  printf("FEN:\n%s\n", position);

  int maxDepth = 0;
  printf("depth of search:\n");
  scanf("%d", &maxDepth);

  if(debugMode){
    char *inputMove = calloc(MAX_INP_LEN, sizeof(char));
    inputMove[MAX_INP_LEN-1] = '\0';
    while(true){
      printDetailedMoveScheme(b, maxDepth);
      printBoard(b);
      printf("move to node: (quit to quit)\n");
      
      
      scanf("%s", inputMove);
      if(strcmp(inputMove, "quit") == 0){
        free(inputMove);
        return 0;
      }
      for(int i = 0; i < MAX_INP_LEN-1; i++){
        inputMove[i] = toupper(inputMove[i]);
      }

      while(!isInputValid(inputMove, b)){
        printf("invalid input\n");
        printf("move to node: (quit to quit)\n");
        scanf("%s", inputMove);
        if(strcmp(inputMove, "quit") == 0){
          free(inputMove);
          return 0;
        }
        for(int i = 0; i < MAX_INP_LEN-1; i++){
          inputMove[i] = toupper(inputMove[i]);
        }
      }

      moveBoard(inputMove, b);
      printf("depth of search:\n");
      scanf("%d", &maxDepth);
    }
    free(inputMove);

  } else {
    printf("results:\n");
    for(int i = 1; i <= maxDepth; i++){
      printf("depth %d -> %ld\n", i, countMoves(b, i));
    }
  }
  
  freeBoard(b);
  free(position);
  return 0;
}


long countMoves(Tboard *b, int depth){

  if(depth == 0){
    return 1;
  }

  long sum = 0;

  TmoveList *ml = initMoveList(8);
  generateAllPossibleMoves(b, ml);

  for(int i = 0; i < ml->filled; i++){
    Tboard *copy = copyBoard(b);

    moveBoard(ml->moves[i], copy);
    sum += countMoves(copy, depth-1);

    freeBoard(copy);
  }
  freeMoveList(ml);

  return sum;
}

bool __ifIsCheckedSetLastMoveToCheck(Tboard *b)
{
  char king = 'k';
  if(b->move%2 == 1){
    king = 'K';
  }
  int kingPos[2];
  getPieceLocation(b, king, kingPos);

  //if not checked, return false
  if(!isAttacked(b, king - ('k' - 'a'), kingPos)){
    return false;
  }
  
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      
      if(!isColor(king - ('k' - 'a'), b->pieces[i][j])){
        strcpy(b->lastMove, (char []){j + 'A',
                                      '8' - i,
                                      j + 'A',
                                      '8' - i,
                                      '\0'});
        if(gotChecked(b, kingPos)){
          return true;
        }
      }
    }
  }
  return NULL;
}


void printDetailedMoveScheme(Tboard *b, int depth)
{
  if(depth <= 0){
    return;
  }

  TmoveList *ml = initMoveList(8);
  generateAllPossibleMoves(b, ml);


  long sum = 0;
  for(int i = 0; i < ml->filled; i++){
    Tboard *copy = copyBoard(b);

    moveBoard(ml->moves[i], copy);
    long temp = countMoves(copy, depth-1);

    printf("%s: %ld\n", ml->moves[i], temp);

    sum += temp;

    freeBoard(copy);
  }
  printf("\nsearched moves: %ld\n", sum);
  freeMoveList(ml);
}
