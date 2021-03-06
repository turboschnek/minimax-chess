/**
 * Project:  Maturitni projekt šachy
 * Author:   Jakub Urbanek
 * Year:     2022
 */

#ifndef __MODULE_GAME_H
#define __MODULE_GAME_H

#include "chess_logic.h"


#include <stdbool.h>

/**
 * constants for minimax alg
 */
// limit of search depth for minimax
#define MAX_MINIMAX_DEPTH 20
/**
 * constant for evaluation of checkmate
 * 
 * following must be true:
 *    (max value of evaluateBoard() <
 *    MINIMAX_WIN_EVAL_COEF <
 *    INF/(MAX_MINIMAX_DEPTH-1))
 */
#define MINIMAX_WIN_EVAL_COEF 100000


/**
 * ussage:  
 * Tplayer my_player; choosePlayer(&my_player, ...);
 * 
 * @return 0 or depth of search when player is minimax
 */
typedef int (*Tplayer)(Tboard *b, char *, int);


/**
 * EXECUTES GAME -- 
 * Asks user for players (human, random, AI) and runs game. 
 * Prints result after game
 * 
 * @param void
 * @return 0 or 1 for error
 */
int game(void);

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
 * @param whiteTimeBudget time in seconds allowed for white minimax's move
 * @param blackTimeBudget time in seconds allowed for black minimax's move
 * 
 * @return 0 for draw or 1 for win of white or -1 for win of black
 */
int gameLoop(Tboard* b, Tplayer white, Tplayer black,
             int whiteTimeBudget, int blackTimeBudget);

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
 * returns bigger integer from parameters
 * @note if a==b returns b
 */
int getMax(int a, int b);

/**
 * returns smaller integer from parameters
 * 
 * @note if a==b returns a
 */
int getMin(int a, int b);

/**
 * sorts movelist using keys
 * 
 * @param ml pointer to movelist to be sorted
 * @param keys array of evaluations of moves
 * @param increasing sets whether the sorted data has to be in increasing order
 * 
 * @note keys and ml must be the same length!
 */
void insertSort(TmoveList *ml, int *keys, bool increasing);


/**
 * capitalizes english letters in string
 */
void toUpper(char*);

/**
 * gets time for minimax bot's move from user
 * 
 * @param identifier this is printed as name of minimax bot
 * @param timeBudget returns scanned value
 *
 */
void scanTimeBudget(int *timeBudget, char* identifier);

/**
 * returns true for inputs of len>=2 where input[0] and input[1]
 * bellong to board
 * 
 * @return true if it is hintable else false
 */
bool isInputHintable(const char* input);


/**
 * sets isClearScreenActive to isIt
 */
void setIsClearScreenActive(bool isIt);

/**
 * clears terminal if isClearScreenActive is set to true (it is by default)
 * @return 0 if OK, 1 if failed
 * @note to change value of isClearScreenActive use fun setIsClearScreenActive
 */
int clearScreen(void);

/**
 * prints board using ANSI color codes
 * 
 * @param b pointer to board to be printed
 */
void printBoard(const Tboard* b);

/**
 * prints board using ANSI color codes, also highlights moves in hint
 * 
 * @param b pointer to board to be printed
 * @param hints pointer to moveList containing hints
 */
void printBoardWithHints(const Tboard* b, TmoveList *hints);

/**
 * prints board using ANSI color codes
 * 
 * @param f output file
 * @param b pointer to board to be printed
 */
void fprintBoard(FILE* out, const Tboard* b);

/**
 * prints board using ANSI color codes, also highlights moves in hint
 * 
 * @param f output file
 * @param b pointer to board to be printed
 * @param hints pointer to moveList containing hints
 */
void fprintBoardWithHints(FILE* out, const Tboard* b, TmoveList *hints);

#endif