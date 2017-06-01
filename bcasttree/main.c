#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

#include "funcinc.h"

int main (int argc, char ** argv)
{
  char myname[MPI_MAX_PROCESSOR_NAME]; 
  int size, rank, rlen, N, i;
  double * buf, stime, etime;

  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &size);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name (myname, &rlen);

  fprintf (stdout, "I am proces %3d of %3d my name is %s (%s)\n", 
    rank, size, myname, argv[0]);
  fflush(stdout);

  N = -1;
  if (argc == 2)
    N = atoi(argv[1]);

  if (N < 0)
    N = 100;

  buf = malloc (N * sizeof (double));
  if (buf == NULL)
  { 
     fprintf (stderr, "Malloc error\n");
     return EXIT_FAILURE;
  }

  if (rank == 0) 
    for (i=0; i<N; i++)
      buf[i] = (double) i;

  MPI_Barrier (MPI_COMM_WORLD);
  stime = MPI_Wtime();
  bcast (rank, 0, size, buf, N);
  MPI_Barrier (MPI_COMM_WORLD);
  etime = MPI_Wtime();

  if (rank == 0)
    fprintf (stdout, "Bcast time: %f s\n", etime-stime);

  MPI_Barrier (MPI_COMM_WORLD);
  stime = MPI_Wtime();
  bcast_tree (rank, size, buf, N);
  MPI_Barrier (MPI_COMM_WORLD);
  etime = MPI_Wtime();

  if (rank == 0)
    fprintf (stdout, "Bcast btree time: %f s\n", etime-stime);
  /*
  else {
    for (i=0; i<N; i++)
      if (buf[i] != (double )i)
        fprintf (stdout, "Bcast error\n");
  }

  MPI_Barrier (MPI_COMM_WORLD);
  stime = MPI_Wtime();
  MPI_Bcast (buf, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Barrier (MPI_COMM_WORLD);
  etime = MPI_Wtime();

  if (rank == 0)
    fprintf (stdout, "Bcast time: %f s\n", etime-stime);
  */

  free (buf);

  MPI_Finalize ();
 
  return EXIT_SUCCESS;
} 
