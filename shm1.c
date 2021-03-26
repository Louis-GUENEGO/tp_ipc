#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main(){
  int pid, shmid;
  char *mem;
  key_t key_shm = 0x99990000; 

  if((shmid=shmget(key_shm, 128, IPC_CREAT|IPC_EXCL|SHM_R|SHM_W)) < 0) {
    perror("shmget");
    exit(-1);
  }


  pid =fork();

  if(pid == 0){		// Processus fils
    if((mem=shmat(shmid, 0, 0)) == (void *) -1) {
      perror("shmat fils");
      exit(-1);
    }
    strcpy(mem,"Hello papa");
    printf("FILS : message pour le pere=%s\n", mem);
    shmdt(mem);
    sleep(5);
    printf("FILS : bye\n", mem);
    exit(0);
  }
  else {			// Processus pere
    if((mem=shmat(shmid, 0, 0)) == (void *) -1) {
      perror("shmat pere");
      exit(-1);
    }
    printf("PERE : attente mort du fils\n");
    wait(0); 	// Attente fin du fils
    printf("PERE : message recu=%s\n", mem);
    shmdt(mem);
  }
  shmctl(shmid, IPC_RMID, NULL);
  exit(0);
}
