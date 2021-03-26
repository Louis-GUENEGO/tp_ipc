#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

#define ORDRE_TYPE 1

key_t cle = 0x99990001;

struct ordre {
  long type;
  char texte[50];	// nom de l'action
  int nombre;	// nombre action a vendre
} message;

int longueur = sizeof(message) - sizeof(long);


int main(int argc, char *argv[]) {
  int msgid;

  if((msgid=msgget(cle, 0600|IPC_CREAT)) == -1) {
    perror("msgget");
    exit(-1);
  }

  // Passage d'ordre d'un client
  if(strcmp(argv[1], "client") == 0) {
    message.type = ORDRE_TYPE;  // message du type 1 (ordre de vente)
    message.nombre = atoi(argv[2]);
    sprintf(message.texte, "Vendre %d actions zorglub", message.nombre);
    if(msgsnd(msgid, &message, longueur, 0) == -1) {
      perror("msgsnd");
      exit(-1);
    }
  }

  // Traitement par l'agent de change
  if(strcmp(argv[1], "agent") == 0) {
    if(msgrcv(msgid, &message, longueur, ORDRE_TYPE, 0) == -1) {
      perror("msgrcv");
      exit(-1);
    }
    printf("Reception type message %ld\n", message.type);
    printf("Ordre recu : %s\n", message.texte);
  }

  exit(0);
}
