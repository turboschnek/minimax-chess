/**
 * Project:  Maturitni projekt šachy
 * Author:   Jakub Urbanek
 * Year:     2022
 */

#include "game.h"

#include <math.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int playGame(void);

void printHelp(void);


int main(int argc, char *argv[])
{
  switch(argc){
    case 2:
      if(strcmp(argv[1], "-d") == 0){
        setIsClearScreenActive(false);
      } else{
        printHelp();
        return 1;
      }

    case 1:
      return playGame();


    default:
      printHelp();
  }
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
    "-d    -debug mode (disable clear screen)"
  };

  int optionCount = sizeof(options) / sizeof(const char*);

  
  printf("Usage: ./chess [OPTIONS]\n\n");
  printf("OPTIONS:\n");
  for(int i = 0; i < optionCount; i++){
    printf("  %s", options[i]);
  }
}
