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

  int maxDepth = 0;
  printf("depth of search:\n");
  scanf("%d", &maxDepth);
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

