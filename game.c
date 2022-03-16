/**
 * Project:  Maturitni projekt šachy
 * Author:   Jakub Urbanek
 * Year:     2022
 */

#include "game.h"
#include "chess.h"

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/**
 * constants for minimax alg
 */
//time limit in seconds for minimax search (AI)
//you can change this as you wish
#define TIME_FOR_MOVE 10
// limit of search depth for minimax
#define MAX_MINIMAX_DEPTH 10

/**
 * constant for evaluation of checkmate
 * 
 * following must be true:
 *    (max value of evaluateBoard() <
 *    MINIMAX_WIN_EVAL_COEF <
 *    INF/(MAX_MINIMAX_DEPTH-1))
 */
#define MINIMAX_WIN_EVAL_COEF 100000


int game(void)
{
  Tplayer white;
  Tplayer black;
  choosePlayer(&white, "white");
  system("clear");
  choosePlayer(&black, "black");
  system("clear");


  Tboard *b = initBoard();
  printf("White to move:\neval: 0\nmoves: 0\nlastMove/depth/time: -/-/-\n");
  printBoard(stdout, b);

  int result = 2;

  result = gameLoop(b, white, black);

  freeBoard(b);

  switch(result){
  case 0:
    printf("\nDRAW\n");
    break;

  case 1:
    printf("\nWHITE WON\n");
    break;

  case -1:
    printf("\nBLACK WON\n");
    break;

  default:
    return -1;
  }

  return 0;
}

void choosePlayer(Tplayer *player, const char* playerName)
{
  char choice;
  printf("Choose %s player\n", playerName);
  printf("1 - human\n2 - random bot\n3 - minimax bot\n");
  scanf("%s", &choice);
  switch(choice){
  case '1':
    *player = &humanGetMove;
    break;
  case '2':
    *player = &randomBotGetMove;
    break;
  case '3':
    *player = &minimaxBotGetMove;
    break;
  default:
    system("clear");
    printf("invalid choice\n");
    choosePlayer(player, playerName);
    break;
  }
}


int gameLoop(Tboard* b, Tplayer white, Tplayer black)
{
  FILE *gameSave = fopen("game_save.txt", "w");
  fprintf(gameSave, "1\n1\n");
  char *moveBuffer = malloc(MAX_INP_LEN * sizeof(char));
  int result = 2, timeBudget = TIME_FOR_MOVE;
  while(result == 2)
  {
    if(b->move%2 == 0){
      //whites move:
      time_t seconds;
      seconds = time(NULL);
      int depth = white(b, moveBuffer, timeBudget);
      seconds = time(NULL) - seconds;

      moveBoard(moveBuffer, b);

      system("clear");
      printf("Black to move:\nstatic eval: %d\
             \nmoves: %d\nlastMove/depth/time: %s/%d/%ld\n",
             evaluateBoard(b), b->move, b->lastMove, depth, seconds);
      printBoard(stdout, b);
      fprintf(gameSave, "%s\n", b->lastMove);
    } else {

      //blacks move:
      time_t seconds;
      seconds = time(NULL);
      int depth = black(b, moveBuffer, timeBudget);
      seconds = time(NULL) - seconds;

      moveBoard(moveBuffer, b);

      system("clear");
      printf("White to move:\nstatic eval: %d\
             \nmoves: %d\nlastMove/depth/time: %s/%d/%ld\n",
             evaluateBoard(b), b->move, b->lastMove, depth, seconds);
      printBoard(stdout, b);
      fprintf(gameSave, "%s\n", b->lastMove);
    }

    result = getResult(b);
  }

  free(moveBuffer);
  fclose(gameSave);
  return result;
}

int randomBotGetMove(Tboard* b, char *randomOutput, int _)
{
  TmoveList *ml = initMoveList(16);

  generateAllPossibleMoves(b, ml);

  if(ml->filled > 0){
      strcpy(randomOutput, ml->moves[rand()%ml->filled]);
  }
  else {
    strcpy(randomOutput, (char[5]){'n', 'o', 'm', 'o', '\0'});
  }

  freeMoveList(ml);
  return 0;
}

int minimaxBotGetMove(Tboard *b, char *output, int seconds)
{
  FILE *minimaxDepthFile = fopen("minimax_depth_log.txt", "w");
  if(minimaxDepthFile == NULL) {
    strcpy(output, (char[5]){'n', 'o', 'm', 'o', '\0'});
    return -1;
  }
  fprintf(minimaxDepthFile, "depth-move -- eval -- time\n");


  int maxDepth = MAX_MINIMAX_DEPTH-1, startDepth = 1, depthStep = 2,
      depth = startDepth, timeBudget = seconds * 1000000;
  float depthTimeCoeff = 0.5;
  bool isBlack = (((b->move+1) % 2) == 0), isInTime = true, interrupted = false;

  //white
  TmoveList *ml = initMoveList(16);

  generateAllPossibleMoves(b, ml);

  if(ml->filled > 0){

    clock_t startTime = clock();

    for(; depth <= maxDepth && isInTime; depth += depthStep){
      int *keys = malloc(ml->filled * sizeof(int));
      for(int i = 0; i < ml->filled && isInTime; i++){
        Tboard *copy = copyBoard(b);
        moveBoard(ml->moves[i], copy);

        keys[i] = minimax(copy, depth, isBlack, -INF, INF);
        //printf("%s -> %d\n", ml->moves[i], keys[i]);

        freeBoard(copy);

        isInTime = !(startTime + timeBudget < clock());
        interrupted = !isInTime;
      }

      if(!interrupted) insertSort(ml, keys, isBlack);

      fprintf(minimaxDepthFile, "%2d -- %s --%5d -- %ld\n",
              depth+1, ml->moves[0], keys[0], clock()-startTime);
      
      if(!interrupted) {
        fprintf(minimaxDepthFile, "\n");
        for(int i = 0; i < ml->filled; i++){
          fprintf(minimaxDepthFile, "%s -> %5d\n", ml->moves[i], keys[i]);
        }
        fprintf(minimaxDepthFile, "\n");
      }

      free(keys);

      isInTime = !((startTime + timeBudget/
                    (depthTimeCoeff * pow(10, depthStep))) < clock());

    }
    strcpy(output, ml->moves[0]);

  } else {
    strcpy(output, (char[5]){'n', 'o', 'm', 'o', '\0'});
  }
  freeMoveList(ml);

  if(!isInTime){
    if(interrupted){
      depth -= depthStep;
    }
    depth -= depthStep;
  }

  fclose(minimaxDepthFile);

  return depth+1;
}

int humanGetMove(Tboard *b, char *input, int _)
{
  int result = getResult(b);
  if (result < 2){
    strcpy(input, (char[5]){'n', 'o', 'm', 'o', '\0'});
    return 0;
  }

  scanf("%s", input);
  toUpper(input);
  while(!isInputValid(input, b)){



    if(isInputHintable(input)){
      if(isItsMove(b->move, b->pieces['8' - input[1]][input[0]-'A'])){

        TmoveList* hints = initMoveList(2);
        generateHints(b, input, hints);

        system("clear");
        printf("!INVALID MOVE!\nstatic eval: %d\
               \nmoves: %d\nlastMove/depth/time: %s/0/0\n",
               evaluateBoard(b), b->move, b->lastMove);
        printBoardWithHints(stdout, b, hints);

        freeMoveList(hints);
      } else {
        system("clear");
        printf("!INVALID MOVE!\nstatic eval: %d\
               \nmoves: %d\nlastMove/depth/time: %s/0/0\n",
               evaluateBoard(b), b->move, b->lastMove);
        printBoard(stdout, b);
      }
    }
    else {
      system("clear");
      printf("!INVALID MOVE!\nstatic eval: %d\
             \nmoves: %d\nlastMove/depth/time: %s/0/0\n",
             evaluateBoard(b), b->move, b->lastMove);
      printBoard(stdout, b);
    }

    scanf("%s", input);
    toUpper(input);

    if (strcmp(input, "END") == 0){
      strcpy(input, (char[5]){'n', 'o', 'm', 'o', '\0'});
    }
  }
  return 0;
}

long countMoves(Tboard *b, int depth){
  // unoptimized performance with gcc -O3: depth = 6: 20s, depth = 5: 1s,

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

int minimax(Tboard *b, int depth, bool isMax, int alfa, int beta)
{
  if(depth == 0){
    return evaluateBoard(b);
  }

  TmoveList *ml = initMoveList(8);
  generateAllPossibleMoves(b, ml);

  int result = getResultFaster(b, ml);
  if(result < 2){
    freeMoveList(ml);

    // *(depth+1) for faster checkmates
    return result * (MINIMAX_WIN_EVAL_COEF * (depth+1));
  }

  if(isMax){
    int max = -INF;

    for (int i = 0; i < ml->filled; i++){
      Tboard *copy = copyBoard(b);
      moveBoard(ml->moves[i], copy);

      max = getMax(max, minimax(copy, depth-1, false, alfa, beta));
      freeBoard(copy);

      alfa = getMax(alfa, max);
      if(beta <= alfa){
        freeMoveList(ml);
        return max;
      }
    }
    freeMoveList(ml);
    return max;
  }else{
    int min = INF;

    for (int i = 0; i < ml->filled; i++){
      Tboard *copy = copyBoard(b);
      moveBoard(ml->moves[i], copy);

      min = getMin(min, minimax(copy, depth-1, true, alfa, beta));
      freeBoard(copy);

      beta = getMin(beta, min);
      if(beta <= alfa){
        freeMoveList(ml);
        return min;
      }
    }
    freeMoveList(ml);
    return min;
  }
}

int getMax(int a, int b)
{
  if(a > b) return a;
  return b;
}

int getMin(int a, int b)
{
  if(a > b) return b;
  return a;
}

void insertSort(TmoveList *ml, int *keys, bool increasing)
{
  if(increasing){
    for(int i = 1; i < ml->filled; i++){
      int j, tempKey = keys[i];
      char *tempMove = ml->moves[i];

      for(j = i-1; (j >= 0 && keys[j] > tempKey); j--){
        ml->moves[j+1] = ml->moves[j];
        keys[j+1] = keys[j];
      }
      ml->moves[j+1] = tempMove;
      keys[j+1] = tempKey;
    }
  } else {
    for(int i = 1; i < ml->filled; i++){
      int j, tempKey = keys[i];
      char *tempMove = ml->moves[i];

      //keys[j] <= tempKey   would be stable, but slower
      for(j = i-1; (j >= 0 && keys[j] < tempKey); j--){
        ml->moves[j+1] = ml->moves[j];
        keys[j+1] = keys[j];
      }
      ml->moves[j+1] = tempMove;
      keys[j+1] = tempKey;
    }
  }
}

