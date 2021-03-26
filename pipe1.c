#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>



int main(void){

  char out;
  int ret;

  int p_dest[2];
  if (pipe(p_dest)){
    printf("Erreur lors de la creation du pipe\n");
    return 0;
  }

  write(p_dest[1], "AB", 2);
  close(p_dest[1]);
  for (int i = 0; i < 3 ; i++){
    ret = read(p_dest[0], &out, 1);
    printf("%c, valeur de retour de read() : %d\n", out, ret);
  }


  return 0;
}
