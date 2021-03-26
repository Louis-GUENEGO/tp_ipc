#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/wait.h>

#define MSG_TYPE 1

key_t cle = 0x99990001;

struct ordre {
  long type;
  char texte[50];	// nom de l'action
} message;

int longueur = sizeof(message) - sizeof(long);


int main(int argc, char *argv[]) {

  int msgid;

  if((msgid=msgget(cle, 0600|IPC_CREAT)) == -1) {
    perror("msgget");
    exit(-1);
  }

  int pid;
  pid=fork();

  if(pid == -1) { // Erreur
    perror("Impossible de creer un fils");
    exit(-1);
  }
  else if(pid == 0) { // Fils
    printf("FILS: je suis le fils\n");

    msgrcv(msgid, &message, longueur, MSG_TYPE,0);
    printf("%s \n", message.texte);

    exit(0);
  }
  else { // pere
    printf("PERE: je suis le pere\n");

    message.type = MSG_TYPE;
    sprintf(message.texte, "Salut");
    msgsnd(msgid, &message, longueur, 0);

    wait(0);
    printf("PERE: mon fils est mort\n");
    exit(0);
  }

  return 0;
}
