#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>

int main(void) {

  char out[6];
  int ret;
  int p_dest[2];

  if (pipe(p_dest)){
    printf("Erreur lors de la creation du pipe\n");
    return 0;
  }

  int pid;
  pid=fork();

  if(pid == -1) { // Erreur
    perror("Impossible de creer un fils");
    exit(-1);
  }

  else if(pid == 0) { // Fils
    printf("FILS: je suis le fils\n");
	close(p_dest[1]);
    read(p_dest[0], out, 5);
    out[5] = 0;
    printf("%s \n", out);

    exit(0);
  }
  else { // pere
    printf("PERE: je suis le pere\n");
    close(p_dest[0]);
    write(p_dest[1], "Salut", 5);
    wait(0);
    printf("PERE: mon fils est mort\n");
    exit(0);
  }
  return 0;
}
