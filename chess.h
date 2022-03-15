/**
 * Project:  Maturitni projekt šachy
 * Author:   Jakub Urbanek
 * Year:     2022
 */

#ifndef __MODULE_CHESS_H
#define __MODULE_CHESS_H

#include "chess_structs.h"

#include <stdio.h>
#include <stdbool.h>


// constants
#define INF 1000000000
#define MAX_BORING_MOVES 100
#define ENDGAME_THRESHOLD 15


//functions for colored terminal output
#define LIGHT(string) "\x1b[43m" string "\x1b[0m"
#define DARK(string) "\x1b[45m" string "\x1b[0m"
#define LIGHT_HINT(string) "\x1b[46m" string "\x1b[0m"
#define DARK_HINT(string) "\x1b[44m" string "\x1b[0m"
#define BLACK_FOREGROUND(string) "\x1b[30m" string



void printBoard(FILE*, const Tboard* b);
void printBoardWithHints(FILE*, const Tboard* b, TmoveList *hints);
char getLastMovedPiece(const Tboard* b);
bool gotChecked(const Tboard *b, const int myKingPos[2]);




void generateAllPossibleMoves(Tboard *b, TmoveList* ml);
void generateHints(Tboard *b, const char *input, TmoveList* ml);

char* getPieceGraphics(char piece);
int getPieceValue(char piece, int row, int col, int pieceCount);
int evaluateBoard(const Tboard* b);
int getResult(Tboard *b);
int getResultFaster(Tboard *b, TmoveList *ml);
bool isInputValid(const char* input, Tboard* b);
bool isInputHintable(const char* input);
bool isMoveValid(const char* input, Tboard* b);
void toUpper(char*);
int getMax(int a, int b);
int getMin(int a, int b);

void moveBoard(const char* input, Tboard* b);
bool isEnPassant(const char* input, const Tboard* b);
bool isEnPassantLegal(const Tboard* b, const int pos[2], const int moveVector[2], int moveRestriction, char oppColor, const int mykingPos[2]);
bool isOnBoard(const int pos[2]);
void generatePieceMoves(const Tboard* b, const int pos[2], TmoveList* ml);
bool isHorseMovePossible(const Tboard* b, const char color, const int pos[2], const int moveVector[2]);
bool isKingMovePossible(const Tboard* b, const char color, const int origin[2], const int dest[2]);
bool isMoveTake(const Tboard* b, const char color, const int pos[2], const int moveVector[2], const int restriction);
bool isMoveClean(const Tboard* b, const int pos[2], const int moveVector[2], const int restriction);
bool isItsMove(const int move, const char piece);
void getPieceLocation(const Tboard* b, const char piece, int[2]);
bool isBlockingCheck(const Tboard* b, const char, const int[2], const int[2]);
bool doesMoveBlockCheck(const Tboard* b, const char *move, const int kingPos[2]);
void disableCastling(Tboard *b, char color, bool buffer[2]);
void regainCastling(Tboard *b, char color, bool buffer[2]);

char oppositeColor(const char color);
bool isColor(const char color, const char piece);
bool isUpper(const char);
bool isLower(const char);
void freeArrayOfStrings(char **arr, int len);
void insertSort(TmoveList *ml, int *keys, bool increasing);
bool isArrayInArrayOfArrays(int *array, int **arrayOfArrays, int ArrLen, int ArrOfArrsLen);
bool isStringTwiceInArrayOfStrings(char *array, char **arrayOfArrays, int ArrOfArrsLen);
void normalize(int moveVector[2]);
bool fitsRestriction(const int moveVector[2], int restriction);
bool isAttacked(const Tboard* b, const char color, const int pos[2]);
bool willBeAttacked(const Tboard *b, const char color, const int origin[2], const int dest[2]);

#endif
