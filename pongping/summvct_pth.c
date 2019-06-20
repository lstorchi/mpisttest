#include <stdio.h>
#include <stdlib.h>

int n, num_threads = 4;
double * a, *b, * c;

void * sumwork (void * arg)
{
  int i, rank;
  
  rank = *(int *)arg;
  
  for (i=rank; i<n; i+=num_threads) 
    c[i] = a[i] + b[i];

  return NULL;
}

int main (int argc, char ** argv)
{
  int i, *rank; 
  pthread_t * tid;

  if (argc == 2)
    n = atoi (argv[1]);
  else 
    n = 10;

  if ( (rank = (int *) calloc(n,sizeof(int))) == NULL) 
  {
    fprintf (stderr, "Memory allocation error\n");
    exit (EXIT_FAILURE);
  }

  if ( (tid = (pthread_t *) calloc(num_threads, sizeof(pthread_t))) == NULL) 
  {
    fprintf (stderr, "Memory allocation error\n");
    exit (EXIT_FAILURE);
  }

  if ( (a = (double *) malloc (sizeof (double) * n)) == NULL) 
  {
    fprintf (stderr, "Memory allocation error\n");
    return EXIT_FAILURE;
  }

  if ( (b = (double *) malloc (sizeof (double) * n)) == NULL) 
  {
    fprintf (stderr, "Memory allocation error\n");
    return EXIT_FAILURE;
  }

  if ( (c = (double *) malloc (sizeof (double) * n)) == NULL) 
  {
    fprintf (stderr, "Memory allocation error\n");
    return EXIT_FAILURE;
  }

  for (i=0; i<n; i++)
  {
    a[i] = (double) i;
    b[i] = 2.0 * (double) i;
    c[i] = 0.0;
  }
 
  for (i=0; i<n; i++)
    fprintf (stdout, "%f ", a[i]);
  fprintf (stdout, "\n");

  for (i=0; i<n; i++)
    fprintf (stdout, "%f ", b[i]);
  fprintf (stdout, "\n");

  for (i=0; i<num_threads; i++) 
  {
    rank[i] = i;
    if(pthread_create(&tid[i],NULL,
                          sumwork,(void *)&rank[i])) 
      exit (EXIT_FAILURE); 
  }

  for (i=0; i<num_threads; i++)
    pthread_join(tid[i],NULL);

  for (i=0; i<n; i++)
    fprintf (stdout, "%f ", c[i]);
  fprintf (stdout, "\n");

  free (a);
  free (b);
  free (c);

  return 0;
}
