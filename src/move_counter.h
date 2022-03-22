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
 * Counts possible move combinations in given depth
 * 
 * @param b initial board position
 * @param depth depth of move tree
 * 
 * @return number of possible moves in the future
 * 
 * @note for starting pos - depth 1 -> 20, depth 2 -> 400
 */
long countMoves(Tboard *b, int depth);


/**
 * sets last move to check (if piece checking king is on pos a1,
 * lastMove gets set to A1A1)
 * 
 * @param b pointer to board
 * 
 * @return true if check was found and lastMove was set
 */
bool __ifIsCheckedSetLastMoveToCheck(Tboard *b);


/**
 * for all possible moves in present position  
 * prints possible move combinations in given depth
 * 
 * @param b pointer to board
 * @param depth depth of search
 * 
 */
void printDetailedMoveScheme(const Tboard *b, int depth);

#endif
