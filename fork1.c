#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>

void main(void) {
  int pid;

  pid=fork();

  if(pid == -1) { // Erreur
    perror("Impossible de creer un fils");
    exit(-1);
  }
  else if(pid == 0) { // Fils
    printf("FILS: je suis le fils\n");
    sleep(1);
    printf("FILS: je meurs\n");
    exit(0);
  }
  else { // pere
    printf("PERE: je suis le pere\n");
    wait(0); // Le pere attend la mort de son fils
    printf("PERE: mon fils est mort\n");
    exit(0);
  }
  return;
}
