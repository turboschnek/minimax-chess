/**
 * Project:  Maturitni projekt šachy
 * Author:   Jakub Urbanek
 * Year:     2022
 */

#ifndef __MODULE_CHESS_STRUCTS_H
#define __MODULE_CHESS_STRUCTS_H

#include <stdbool.h>


#define POS_STRING_LEN 65
#define MAX_INP_LEN 6


/**
 * The main structure of this module.  
 * It has all the data you will ever need for chess games
 */
typedef struct{

  // 2d arrray of pieces
  // white - k = king, q = queen, r = rook, b = bishop, n = knight, p = pawn
  // black - K = king, Q = queen, R = rook, B = bishop, N = knight, P = pawn
  char pieces[8][8];

  // two values for long and short castling (0 - long, 1- short)
  bool canWhiteCastle[2];

  // two values for long and short castling (0 - long, 1 - short)
  bool canBlackCastle[2];
  
  // useful for "en passant"
  char* lastMove;

  // total number of moves made
  int move;

  // number of moves without take or pawn move (for draws by repetition)
  int boringMoveCount;

  // array of boring positions since last unboring move
  // (used for draws by repetition)
  char **boringPoss;
  
  //number of pieces left (for evaluating king's position)
  int pieceCount;

} Tboard;


/**
 * initializes board datastructure
 * 
 * @param void
 * @return pointer to allocated board
 * @note board is set to starting position
 */
Tboard* initBoard(void);

/**
 * copies board datastructure
 * 
 * @param b pointer to board to be copied
 * @return pointer to copy of b
 */
Tboard* copyBoard(const Tboard *b);

/**
 * returns posString of current possition
 * 
 * @param b pointer to board
 * @returns string with len 65 representing current position
 * @note posString of srarting position:  
 * "RNBQKBNRPPPPPPPP                                pppppppprnbqkbnr"
 */
char* boardToPosString(const Tboard *b);

/**
 * frees board
 * 
 * @param b pointer to board to be freed
 * @return void
 */
void freeBoard(Tboard* b);






/**
 * dynamically allocated expandable list of moves
 */
typedef struct{

  //array of moves
  char **moves;

  //allocated number of moves
  int size;

  //filled number of moves
  int filled;

} TmoveList;


/**
 * initializes TmoveList
 * 
 * @param size initial size of list (meaning count of moves to fill it)
 * @return pointer to initialized moveList
 */
TmoveList* initMoveList(int size);
void reallocMoveList(TmoveList* ml, int resultSize);
void appendMoveList(TmoveList* ml, char* move);
void freeMoveList(TmoveList* ml);

#endif