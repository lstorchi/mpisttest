#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <mpi.h>
#include <assert.h>

#include "func.h"

// test a different approach

int main (int argc, char ** argv) 
{
  int size, rank, rlen, i;
  char myname[MPI_MAX_PROCESSOR_NAME]; 
  double time, ctime, pi, * points;

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

  if (size > 1) 
  {
    MPI_Barrier (MPI_COMM_WORLD);
    ctime = MPI_Wtime ();
    myn = n / size;
    
    points = (double *) malloc (sizeof (double) * myn * 2);
    assert(points != NULL);
    
    if (rank == 0) 
    {
      int torank;

      srand (10);
      for (torank=1; torank<size; torank++) 
      {
        for (i=0; i<myn; i++) 
        {
          points[2*i] = (double) rand() / ((double)RAND_MAX + 1.0e0);
          points[(2*i)+1] = (double) rand() / ((double)RAND_MAX + 1.0e0);
        }
        
        // need to test nonblocking 
        MPI_Send (points, myn*2, MPI_DOUBLE, torank, torank, MPI_COMM_WORLD);
      }
    
      myn = myn + (n - (size * myn)); 
      circle_count = 0;  
      for (i=0; i<myn; i++) 
      {
        double x, y; 
      
        x = (double) rand() / ((double)RAND_MAX + 1.0e0);
        y = (double) rand() / ((double)RAND_MAX + 1.0e0);
      
        if ((pow(x, 2.0) + pow(y, 2.0)) < 1.0)
          (circle_count)++;
      }
    }
    else 
    {
      MPI_Status status;
    
      MPI_Recv (points, myn*2, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD, &status);
    
      circle_count = 0;
      for (i=0; i<myn; i++) 
        if ((pow(points[2*i], 2.0) + pow(points[(2*i)+1], 2.0)) < 1.0)
          circle_count++;
    }
    
    free (points);
    
    MPI_Reduce (&circle_count, &t_circle_count, 1, MPI_INT, MPI_SUM, 0, 
        MPI_COMM_WORLD);
    ctime = MPI_Wtime () - ctime;

    if (rank == 0) 
    {
      pi = 0.0e0;
      pi = (double) t_circle_count / (double) n;
      pi *= 4.0e0;
      fprintf (stdout, "Parallel PI = %.23f  %f s\n", pi, ctime);
    }
  }

  if (rank == 0) 
  {
    time = (double) clock();
    srand(10);
    pi = 0.0e0;
    circle_count = 0;
    sequential (n, &circle_count);
    pi = (double) circle_count / (double) n;
    pi *= 4.0e0;
    time = (double) clock() - time;
    
    time /= CLOCKS_PER_SEC;

    fprintf (stdout, "Sequential PI = %.23f %f s\n", pi, time);
  }

  MPI_Finalize ();

  return EXIT_SUCCESS;
}
