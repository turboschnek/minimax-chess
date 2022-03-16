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
  if(system("clear") != 0){
    fprintf(stderr, "unable to clear screen");
    return -1;
  }

  srand(time(NULL));  //for random bot's randomness

  return game();
}