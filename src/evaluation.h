/**
 * Project:  Maturitni projekt šachy
 * Author:   Jakub Urbanek
 * Year:     2022
 */

#ifndef __MODULE_EVALUATION_H
#define __MODULE_EVALUATION_H

#include "chess_logic.h"

//maximal number of pieces needed to make king more vlauable in center of board
#define ENDGAME_THRESHOLD 15

/**
 * Evaluates board.  
 * Returns sum of values of all pieces.
 * 
 * @param b pointer to board to be evaluated
 * @return evaluation (bigger means better for white and 0 means equal)
 * @note Returns value theoreticaly between -11 000 and 11 000
 */
int evaluateBoard(const Tboard* b);

/**
 * Gets value of piece.  
 * Position is considered for knight, pawn and king.
 * 
 * @param piece ex.: 'k', 'K', 'n'
 * @param col piece's column (starting on left)
 * @param row piece's row (starting on top)
 * @param pieceCount number of remaining pieces on board
 * 
 * @return value between -900(Q) and 900(q)
 */
int getPieceValue(char piece, int row, int col, int pieceCount);



#endif
