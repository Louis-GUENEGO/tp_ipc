#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void it_fils(){
  printf("interruption -> commande SIGUSR1\n");
  kill(getpid(), SIGINT);
  return;
}

int main(void) {


  int pid;

  pid=fork();

  if(pid == -1) { // Erreur
    perror("Impossible de creer un fils");
    exit(-1);
  }
  else if(pid == 0) { // Fils
    printf("FILS: je suis le fils\n");
    signal(SIGUSR1, it_fils);

    while (1) {
      printf("Attente de l'interruption \n");
      sleep(1);
    }

    printf("FILS: je meurs\n");
    exit(0);
  }
  else { // pere
    printf("PERE: je suis le pere\n");
    sleep(5); // Le pere attend la mort de son fils
    kill(pid, SIGUSR1);
    wait(0);
    printf("PERE: mon fils est mort\n");
    exit(0);
  }
  return 0;
}
