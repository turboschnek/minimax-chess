/**
 * Project:  Maturitni projekt šachy
 * Author:   Jakub Urbanek
 * Year:     2022
 */

#ifndef __MODULE_MOVE_COUNTER_H
#define __MODULE_MOVE_COUNTER_H

#include "chess_structs.h"


/**
 * @param debuugMode if true, prints detailend view of search
 * 
 * @return 0 if OK else 1
 */
int moveCounterMain(bool debugMode);

/**
 * Counts possible move sequences in given depth
 * 
 * @param b initial board position
 * @param depth depth of move tree
 * 
 * @return number of possible moves in the future
 * 
 * @note for starting pos - depth 1 -> 20, depth 2 -> 400
 */
long countMoves(Tboard *b, int depth);

bool __ifIsCheckedSetLastMoveToCheck(Tboard *b);

void printDetailedMoveScheme(Tboard *b, int depth);

#endif
