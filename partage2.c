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


int main(void){
  int pid, shmid;
  int semid;
  int * mem;
  key_t key_shm = 0x99990000;

  if((shmid=shmget(key_shm, sizeof(int), IPC_CREAT|IPC_EXCL|SHM_R|SHM_W)) < 0) {
    perror("shmget");
    exit(-1);
  }

  semid = sem_create(CLE, 1);

  pid =fork();

  if(pid == 0){		// Processus fils
    if((mem=shmat(shmid, 0, 0)) == (void *) -1) {
      perror("shmat fils");
      exit(-1);
    }
    while(1){
      P(semid);
      (*mem)++;
      printf("FILS : %d\n", *mem);
      sleep(1);
      V(semid);
    }
    exit(0);
  }
  else {			// Processus pere
    if((mem=shmat(shmid, 0, 0)) == (void *) -1) {
      perror("shmat pere");
      exit(-1);
    }

    while(1){
      P(semid);
      (*mem)++;
      printf("PERE : %d\n", *mem);
      sleep(1);
      V(semid);
    }

    printf("PERE : attente mort du fils\n");
    wait(0); 	// Attente fin du fils
    shmdt(mem);
  }
  shmctl(shmid, IPC_RMID, NULL);
  exit(0);
}
