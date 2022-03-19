/**
 * Project:  Maturitni projekt šachy
 * Author:   Jakub Urbanek
 * Year:     2022
 */

#include "game.h"
#include "move_counter.h"

#include <math.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int playGame(void);

void printHelp(void);


int main(int argc, char **argv)
{
  switch(argc){
    case 2:
      if(strcmp(argv[1], "-c") == 0){
        return moveCounterMain(false);
        
      } else if(strcmp(argv[1], "-g") == 0){
        return playGame();

      } else if(strcmp(argv[1], "-d") == 0){
        setIsClearScreenActive(false);
        return playGame();

      } else if(strcmp(argv[1], "-m") == 0){
        return moveCounterMain(true);

      }else{
        printHelp();
        return 0;
      }


    case 1:
      return playGame();


    default:
      printHelp();
  }
  return 0;
}


int playGame()
{

  if(clearScreen() != 0){
    fprintf(stderr, "unable to clear screen");
  }

  srand(time(NULL));  //for random bot's randomness

  return game();
}

void printHelp()
{
  const char *options[] = {
    "-g        -game (default)"
    "-d        -game with debug mode (disables clear screen)",
    "-c        -count future moves of FEN string",
    "-m        -count future moves made from every moved FEN string"
  };

  int optionCount = sizeof(options) / sizeof(const char*);

  
  printf("Usage: ./chess [OPTION]\n\n");
  printf("OPTIONS:\n");
  for(int i = 0; i < optionCount; i++){
    printf("  %s\n", options[i]);
  }
}
