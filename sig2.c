#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>

#include <signal.h>

char val;

void fin(){
  printf("interruption -> commande CTRL-C\n");
  val = 0;
  return;
}


int main(void) {
  val = 1;
  signal(SIGINT, fin);

  while (val) {
    printf("Attente de l'interruption \n");
    sleep(1);
  }

  return 0;
}
