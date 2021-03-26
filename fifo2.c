#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>

int main(void){

  char out[6];
  int ret;

  int fd;

  mkfifo("ma_fifo", 0600);

  int pid;
  pid=fork();

  if(pid == -1) { // Erreur
    perror("Impossible de creer un fils");
    exit(-1);
  }

  else if(pid == 0) { // Fils
    printf("FILS: je suis le fils\n");
    fd = open("ma_fifo", O_RDONLY);
    read(fd, out, 5);
    out[5] = 0;
    printf("%s \n", out);
    exit(0);
  }
  else { // pere
    printf("PERE: je suis le pere\n");
    fd = open("ma_fifo", O_WRONLY);
    write(fd, "Salut", 5);
    wait(0);
    printf("PERE: mon fils est mort\n");
    exit(0);
  }

  return 0;
}
