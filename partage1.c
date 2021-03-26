#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/shm.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dijkstra.h"

#define CLE 1001
#define CLE2 1002

int main(void) {
  int pid;
  int semid;
  int shmid;
  int * mem;

  shmid = shmget ( CLE2, sizeof(int), IPC_CREAT|IPC_EXCL|SHM_R|SHM_W);

  semid = sem_create(CLE, 1);
  pid=fork();

  if(pid == -1) { // Erreur
    perror("Impossible de creer un fils");
    exit(-1);
  }

  else if(pid == 0) { // Fils
    mem=shmat(shmid, 0, 0);
    while(1){
      P(semid);
      (*mem)++;
      printf("FILS : %d\n", *mem);
      sleep(1);
      V(semid);
    }
    exit(0);
  }

  else {	// Pere
    mem=shmat(shmid, 0, 0);
    while(1){
      P(semid);
      (*mem)++;
      printf("PERE : %d\n", *mem);
      sleep(1);
      V(semid);
    }
    wait(0);
    exit(0);
  }
}
