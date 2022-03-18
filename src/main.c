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

int main()
{
  if(clearScreen() != 0){
    fprintf(stderr, "unable to clear screen");
  }

  srand(time(NULL));  //for random bot's randomness

  return game();
}