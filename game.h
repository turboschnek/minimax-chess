/**
 * Project:  Maturitni projekt šachy
 * Author:   Jakub Urbanek
 * Year:     2022
 */

#ifndef __MODULE_GAME_H
#define __MODULE_GAME_H

#include "chess.h"
#include "evaluation.h"

#include <stdbool.h>


/**
 * ussage: \n
 * Tplayer my_player; choosePlayer(&my_player, ...);
 * 
 * @return 0 or depth of search when player is minimax
 */
typedef int (*Tplayer)(Tboard *b, char *, int);


/**
 * EXECUTES GAME LOOP -- 
 * Asks user for players (human, random, AI) and runs game. 
 * Prints result after game
 * 
 * @param void
 * @return 0 or -1 for error
 */
int game(void);

/**
 * Asks user for move and validates it.
 * 
 * @param b current board
 * @param input gets filled by validated user input (length == MAX_INP_LENGTH)
 * @param _ is not used in this function
 * 
 * @return 0
 * 
 * @note param int _ exists to make function compatible with Tplayer
 */
int humanGetMove(Tboard *b, char *input, int _);

/**
 * Generates random valid move.
 * 
 * @param b current board
 * @param randomOutput gets filled by random valid move
 *                     (length == MAX_INP_LENGTH)
 * @param _ is not used in this function
 * 
 * @return 0
 * 
 * @note param int _ exists to make function compatible with Tplayer
 */
int randomBotGetMove(Tboard* b, char* randomOutput, int _);

/**
 * Uses minimax to choose a move.
 * 
 * @param b current board
 * @param output gets filled by AI (length == MAX_INP_LENGTH)
 * @param _ is not used in this function
 * 
 * @return depth of finished search
 */
int minimaxBotGetMove(Tboard *b, char *output, int seconds);


/**
 * Counts possible move sequences for given depth
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
 * Do not use directly unless you really know what are you doing
 * recursive part of minimax alg
 * 
 * @param b board position to evaluate
 * @param depth depth of search (recomended odd value)
 * @param isMax is player maximazing?
 * @param alfa for pruning (initially -INF)
 * @param beta for pruning (initially INF)
 * 
 * @return numerical evaluation of position
 * @note use minimaxBotGetMove() instead
 */
int minimax(Tboard *b, int depth, bool isMax, int alfa, int beta);

/**
 * Lets user choose player (shows possibilities and waits for numerical input).
 * Chosen player function is saved to parameter *player
 *
 * @param player pointer to Tplayer to be chosen
 * @param playerName string displayed to user(usually "white" or "black")
 * 
 * @return void
 * @note voulnerable to buffer overflow
 */
void choosePlayer(Tplayer *player, const char* playerName);

/**
 * Runs gameloop until end of game
 * 
 * @param b initialized board (remains constant),
 * @param white pointer to player function for white
 * @param black pointer to player function for black
 * 
 * @return 0 for draw or 1 for win of white or -1 for win of black
 */
int gameLoop(Tboard* b, Tplayer white, Tplayer black);

#endif