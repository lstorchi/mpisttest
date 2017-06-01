#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <mpi.h>

#include "func.h"

// programma dimostrativo deve essere migliorato se non altro
// nell'aspetto e nella gestione degli errori

// provare strategia master slave

int main (int argc, char ** argv) 
{
  int size, rank, rlen;
  char myname[MPI_MAX_PROCESSOR_NAME]; 
  double time, ctime, mctime, commtime, mcommtime, 
         mtime, pi;

  int n = -1, circle_count, myn, t_circle_count;

  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &size);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name (myname, &rlen);

  fprintf (stdout, "I am proces %3d of %3d my name is %s (%s)\n", 
    rank, size, myname, argv[0]);
  fflush(stdout);

  if (argc == 2)
    n = atoi(argv[1]);

  if (n < 0)
    n = 100;

  myn = n / size;

  if (rank == 0) 
    myn = myn + (n - (size * myn)); 

  MPI_Barrier (MPI_COMM_WORLD);
  mtime = MPI_Wtime ();
  
  mctime = MPI_Wtime ();
  sequential (myn, rank, &circle_count);
  mctime = MPI_Wtime () - mctime;

  mcommtime = MPI_Wtime ();
  MPI_Reduce (&circle_count, &t_circle_count, 1, MPI_INT, 
      MPI_SUM, 0, MPI_COMM_WORLD);
  mcommtime = MPI_Wtime () - mcommtime;
  
  MPI_Barrier (MPI_COMM_WORLD);
  mtime = MPI_Wtime () - mtime;

  MPI_Reduce (&mcommtime, &commtime, 1, MPI_DOUBLE, MPI_MAX, 0,
      MPI_COMM_WORLD);
  MPI_Reduce (&mctime, &ctime, 1, MPI_DOUBLE, MPI_SUM, 0,
      MPI_COMM_WORLD);
  MPI_Reduce (&mtime, &time, 1, MPI_DOUBLE, MPI_MAX, 0,
      MPI_COMM_WORLD);

  if (rank == 0) 
  {
    pi = (double) t_circle_count / (double) n;
    pi *= 4.0e0;
    fprintf (stdout, "Parallel PI = %.23f  %f s (comm: %f s comp: %f s)\n", 
        pi, time, commtime, ctime);

    pi = 0.0e0;

    time = (double) clock();
    sequential (n, 0, &circle_count);
    pi = (double) circle_count / (double) n;
    pi *= 4.0e0;
    time = (double) clock() - time;
    
    time /= CLOCKS_PER_SEC;

    fprintf (stdout, "Sequential PI = %.23f %f s\n", pi, time);
  }

  MPI_Finalize ();

  return EXIT_SUCCESS;
}
