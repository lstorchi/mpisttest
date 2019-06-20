#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main (int argc, char ** argv)
{
  int i, n, rank, size, rlen; 
  char myname[MPI_MAX_PROCESSOR_NAME];

  double * a, *b, * c, stime, etime;

  MPI_Status status;

  MPI_Init (&argc, &argv);   
  MPI_Comm_rank (MPI_COMM_WORLD, &rank); 
  MPI_Comm_size (MPI_COMM_WORLD, &size); 

  MPI_Get_processor_name (myname, &rlen);

  if (argc == 2)
    n = atoi (argv[1]);
  else
    n = 10;

  /*fprintf(stdout, "Hello world from process %d of %d [%s]\n", rank, size, 
          myname); */

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
 
  /* sync printf */
  MPI_Barrier (MPI_COMM_WORLD);
  MPI_Barrier (MPI_COMM_WORLD);

  if (rank == 0)
  {
    for (i=0; i<n; i++)
      fprintf (stdout, "%f ", a[i]);
    fprintf (stdout, "\n");

    for (i=0; i<n; i++)
      fprintf (stdout, "%f ", b[i]);
    fprintf (stdout, "\n");
  }
  
  /* solo per misurare il tempo */
  MPI_Barrier (MPI_COMM_WORLD);
  stime = MPI_Wtime ();

  for (i=rank; i<n; i+=size)
    c[i] = a[i] + b[i];

  etime = MPI_Wtime ();
  /*fprintf (stdout, "Exec time 3: %f s \n", etime - stime);*/

  /* solo per misurare il tempo */
  MPI_Barrier (MPI_COMM_WORLD);

  MPI_Reduce(c, c, n, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  if (rank == 0)
  {
    for (i=0; i<n; i++)
      fprintf (stdout, "%f ", c[i]);
    fprintf (stdout, "\n");
  }

  MPI_Finalize ();

  free (a);
  free (b);
  free (c);

  return 0;
}


