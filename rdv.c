#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dijkstra.h"

#define CLE 1000

int main(void) {
  int pid;
  int semid;

  semid = sem_create(CLE, 0);


  pid=fork();

  if(pid == -1) { // Erreur
    perror("Impossible de creer un fils");
    exit(-1);
  }
  else if(pid == 0) { // Fils
    sleep(3) ;
    printf("FILS: V(sem)\n");
    V(semid);
    exit(0);
  }
  else {	// Pere
    printf("PERE: P(sem)\n");
    P(semid);
    printf("PERE: RDV avec mon fils\n");
    sem_delete(semid);
    wait(0);
    printf("PERE: mon fils est mort\n");
    exit(0);
  }
}
