#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int n, i;
  double d;

  if (argc != 2)
    n = 10;
  else
    n = atoi(argv[1]);

  d = 0.0;
  
  for (i=1; i<=n; i++)
    d += (double) i;
  
  fprintf ( stdout, "result = %f\n", d);

  return 0;
}
