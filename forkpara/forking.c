#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main (int argc, char **argv)
{
  int n, i;
  pid_t pid;
  double d;

  double *shared;
  int shmid, iproc;

  if (argc != 2)
    n = 10;
  else
    n = atoi(argv[1]);

  d = 0.0;

  shmid = shmget(IPC_PRIVATE, 
                 sizeof(double), (IPC_CREAT | 0600));
  shared = shmat(shmid, 0, 0);
  shmctl (shmid, IPC_RMID, 0);

  iproc = 0;  
  if ((pid = fork()) == -1) {
    fprintf(stderr, "The fork failed!\n");
    exit (EXIT_FAILURE);
  } 
  else {
    if (pid != 0) 
      iproc = 1 ;
  }

  for (i=iproc+1; i<=n; i+=2) 
    d += (double) i;

  if (pid == 0) {
    *shared = d;
    exit (EXIT_SUCCESS); 
  } 
  else { 
    wait(0); 
    d = d + *shared;
    fprintf ( stdout, "result = %f\n", d);
  }

  return EXIT_SUCCESS;
}
