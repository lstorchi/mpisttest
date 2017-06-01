#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "func.h"

void sequential (int n, int * circle_count)
{
  int i;
    
  *circle_count = 0;  
  for (i=0; i<n; i++) {
    double x, y; 

    x = (double) rand() / ((double)RAND_MAX + 1.0e0);
    y = (double) rand() / ((double)RAND_MAX + 1.0e0);

    //printf ("%f - %f\n", x, y);

    if ((pow(x, 2.0) + pow(y, 2.0)) < 1.0)
      (*circle_count)++;
  }
 
  return;
}
