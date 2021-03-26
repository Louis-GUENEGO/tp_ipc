#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dijkstra.h"

#define CLE 1000

main() {
  int pid;
  int semid;

  semid = sem_create(CLE, ...);


  pid=fork();

  if(pid == -1) { // Erreur
    perror("Impossible de creer un fils");
    exit(-1);
  }
  else if(pid == 0) { // Fils
    sleep(5) ;
    printf("FILS: V(sem)\n");
    ...
      exit(0);
  }
  else {	// Pere
    printf("PERE: P(sem)\n");
    ...
      printf("PERE: RDV avec mon fils\n");

      sem_delete(...);
      exit(0);
  }
}

