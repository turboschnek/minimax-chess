/**
 * Project:  Maturitni projekt šachy
 * Author:   Jakub Urbanek
 * Year:     2022
 */

#include "evaluation.h"
#include "chess_logic.h"

#include <stdlib.h>

int evaluateBoard(const Tboard *b)
{
  int sum = 0;
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      sum += getPieceValue(b->pieces[i][j], i, j, b->pieceCount);
    }
  }
  return sum;
}


int getPieceValue(char piece, int row, int col, int pieceCount)
{
  int temp = 0;
  switch(piece)
  {
  
  // value of king:
  // in the beginning is highest in corner
  // in endgame is highest in the centre
  case 'k':
    if(pieceCount > ENDGAME_THRESHOLD){
      if(row == 7)
        temp = 1;
      return (temp * abs(35 - (col*10))) / 2;
    }
    return ((abs(35 - (col*10)) + abs(35 - (row*10))) / 2);
  case 'K':
    if(pieceCount > ENDGAME_THRESHOLD){
      if(row == 0)
        temp = 1;
      return -(temp * abs(35 - (col*10))) / 2;
    }
    return -((abs(35 - (col*10)) + abs(35 - (row*10))) / 2);

  case 'q':
    return 900;
  case 'Q':
    return -900;
  case 'b':
    return 300;
  case 'B':
    return -300;
  case 'n':
    // forces knights to be in the middle, where it is ideal for them
    return 300 - ((abs(35 - (col*10)) + abs(35 - (row*10))) / 10);
  case 'N':
    return -(300 - ((abs(35 - (col*10)) + abs(35 - (row*10))) / 10));
  case 'r':
    return 500;
  case 'R':
    return -500;
  case 'p':
    // pawns are most valuable in middle cols and near promotion
    return 100 + (7-row) - (abs(35 - (col*10)) / 10);
  case 'P':
    return -(100 + row - (abs(35 - (col*10)) / 10));
  default:
    return 0;
  }
}
