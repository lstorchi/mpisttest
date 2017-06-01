#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

#include "funcinc.h"

void bcast (int myrank, int rootrank, int size, double * sbuf, 
    int bufdim) 
{
  if (myrank == rootrank) 
  {
    int i;
    for (i=0; i<size; i++) 
      if (i != rootrank)
        MPI_Send (sbuf, bufdim, MPI_DOUBLE, i, 211, MPI_COMM_WORLD);
  
  }
  else 
  {
    MPI_Status status;
    MPI_Recv (sbuf, bufdim, MPI_DOUBLE, rootrank, 211, MPI_COMM_WORLD,
        &status);
  }

  return;
}

void bcast_tree (int myrank, int size, double * sbuf, int bufdim) 
{
  int torank1, torank2, fromrank;
  MPI_Status status;

  fromrank = (int) ((myrank-1)/2);
  
  if (myrank > 0)
    MPI_Recv (sbuf, bufdim, MPI_DOUBLE, fromrank, myrank, MPI_COMM_WORLD, 
        &status);
  
  torank1 = 2 * myrank + 1;
  torank2 = 2 * myrank + 2;

  if (torank1 < size)
    MPI_Send (sbuf, bufdim, MPI_DOUBLE, torank1, torank1, MPI_COMM_WORLD);
  if (torank2 < size)
    MPI_Send (sbuf, bufdim, MPI_DOUBLE, torank2, torank2, MPI_COMM_WORLD);

  return;
}
