#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void){

  char out;
  int ret;

  mkfifo("ma_fifo", 0600);

  return 0;
}
