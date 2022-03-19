/**
 * Project:  Maturitni projekt šachy
 * Author:   Jakub Urbanek
 * Year:     2022
 */

#ifndef __MODULE_MOVE_COUNTER_H
#define __MODULE_MOVE_COUNTER_H

#include "chess_structs.h"


/**
 * @return 0 if OK else 1
 */
int moveCounterMain(void);

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

#endif
