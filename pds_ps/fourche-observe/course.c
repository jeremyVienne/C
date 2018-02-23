#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>


int main(){
  pid_t pid;
  int i;
  int inc;

  for(i=0;i<10;i++){
    pid=fork();
    switch (pid) {
      case -1:
        perror("erreur fork");
        exit(EXIT_FAILURE);
      case 0:
        for(inc=0; inc<100000000;inc++){

        }
        printf("[%d] a compté jusqu'a 100000000\n", getpid());
        for(inc=0; inc<100000000;inc++){

        }
        exit(EXIT_SUCCESS);
      default:
        break;
    }

  }
  inc=1;
  while((pid=wait(NULL))!=-1){
    printf("%i : [%d]\n",inc,pid );
    inc++;
  }

  exit(EXIT_SUCCESS);

}
