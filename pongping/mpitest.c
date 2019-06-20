#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main (int argc, char ** argv)
{
  int i, j, n, rank, size, rlen; 
  char myname[MPI_MAX_PROCESSOR_NAME];

  double * d, stime, etime, dim;

  MPI_Status status;

  MPI_Init (&argc, &argv);   
  MPI_Comm_rank (MPI_COMM_WORLD, &rank); 
  MPI_Comm_size (MPI_COMM_WORLD, &size); 

  MPI_Get_processor_name (myname, &rlen);

  if (argc == 2)
    n = atoi (argv[1]);
  else
    n = 10;

  fprintf(stdout, "Hello world from process %d of %d [%s]\n", rank, size, 
          myname);

  srand (10);

  dim = (n * n * sizeof(double)) / (1024.0*1024.0*1024.0);
  if ( (d = (double *) malloc (sizeof (double) * n * n)) == NULL) 
  {
    fprintf (stderr, "Memory allocation error\n");
    return EXIT_FAILURE;
  }

  if (rank == 0) 
  {
    for (i=0; i<n; i++)
      for (j=0; j<n; j++)
        d[(i*n) + j] = 1.0e0 + (double) (1.0e0 * n * (rand() / (RAND_MAX + 1.0e0)));   
    fprintf (stdout, "Sending: %f GB\n", dim);
  }

  MPI_Barrier (MPI_COMM_WORLD);

  if (rank == 0) 
  {
    stime = MPI_Wtime ();
    MPI_Ssend (d, n*n, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD);
    etime = MPI_Wtime ();
    fprintf (stdout, "Send time 3: %f s [%f GB/s] \n", etime - stime, 
            dim/(etime - stime));

    stime = MPI_Wtime ();
    MPI_Ssend (d, n*n, MPI_DOUBLE, 1, 2, MPI_COMM_WORLD);
    etime = MPI_Wtime ();
    fprintf (stdout, "Send time 3: %f s [%f GB/s] \n", etime - stime, 
            dim/(etime - stime)); 

    stime = MPI_Wtime ();
    MPI_Recv (d, n*n, MPI_DOUBLE, 1, 3, MPI_COMM_WORLD, 
        &status);
    etime = MPI_Wtime ();
    fprintf (stdout, "Recv time 3: %f s [%f GB/s] \n", etime - stime, 
            dim/(etime - stime));
  }
  else 
  {
    stime = MPI_Wtime ();
    MPI_Recv (d, n*n, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, 
        &status);
    etime = MPI_Wtime ();
    fprintf (stdout, "Recv time 3: %f s [%f GB/s] \n", etime - stime, 
            dim/(etime - stime));

    stime = MPI_Wtime ();
    MPI_Recv (d, n*n, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD, 
        &status);
    etime = MPI_Wtime ();
    fprintf (stdout, "Recv time 3: %f s [%f GB/s] \n", etime - stime, 
            dim/(etime - stime));

    stime = MPI_Wtime ();
    MPI_Ssend (d, n*n, MPI_DOUBLE, 0, 3, MPI_COMM_WORLD);
    etime = MPI_Wtime ();
    fprintf (stdout, "Send time 3: %f s [%f GB/s] \n", etime - stime, 
            dim/(etime - stime)); 
  }

  MPI_Barrier (MPI_COMM_WORLD);

  MPI_Finalize ();

  free (d);

  return 0;
}


