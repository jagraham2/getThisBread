#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "e4c_lite.h"

int main(void){
  char something[1];
  scanf("%s", something);

  if (isdigit(atoi(something))){
    printf("It's a digit");
  }
  else{
    printf("that's not a digit");
  }
}
