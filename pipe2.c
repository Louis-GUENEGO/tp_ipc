#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int p_dest[2];

void it_sigpipe(){
  printf("écriture dans un PIPE fermé en lecture \n");
}

int main(void){

  signal(SIGPIPE, it_sigpipe);

  if (pipe(p_dest)){
    printf("Erreur lors de la creation du pipe\n");
    return 0;
  }


  close(p_dest[0]);
  write(p_dest[1], "A", 1);


  return 0;
}
