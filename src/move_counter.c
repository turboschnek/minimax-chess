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

int moveCounterMain()
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

  if(b->move % 2 == 0){
    printf("white to move:\n");
  } else {
    printf("black to move:\n");
  }

  printBoard(stdout, b);

  int maxDepth = 0;
  printf("depth of search:\n");
  scanf("%d", &maxDepth);
  printf("results:\n");
  for(int i = 1; i <= maxDepth; i++){
    printf("depth %d -> %ld\n", i, countMoves(b, i));
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
  char *lastMoveBackup = malloc(MAX_INP_LEN * sizeof(char));
  strcpy(lastMoveBackup, b->lastMove);
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      char king = 'k';
      if(b->move%2 == 1){
        king = 'K';
      }
      int kingPos[2];
      getPieceLocation(b, king, kingPos);
      
      strcpy(b->lastMove, (char []){i + 'A',
                                    j + '1',
                                    i + 'A',
                                    j + '1',
                                    '\0'});

      if(gotChecked(b, kingPos)){
        free(lastMoveBackup);
        return true;
      }
    }
  }

  strcpy(b->lastMove, lastMoveBackup);
  free(lastMoveBackup);
  return false;
}
