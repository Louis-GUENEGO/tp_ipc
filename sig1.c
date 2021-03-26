#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>

#include <signal.h>

char val;

void it(){
  printf("interruption \n");
  val = 0;
  return;
}


int main(void) {
  val = 1;
  signal(SIGALRM, it);
  alarm(5);

  while (val) {
    printf("Attente de l'interruption \n");
    sleep(1);
  }

  return 0;
}
