#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>

void observe(int n){
  int inc;
  pid_t pid;
  for(inc=0; inc<n; inc++){
    pid= fork();
    switch (pid) {
      case -1:
        perror("Error fork");
        exit(EXIT_FAILURE);
      case 0:
        while(1){
          printf("[%d]\n", getpid());
          /*kill(getpid(), 1);*/
          sleep(5);

        }
        break;
      default:

        break;
    }
    system("ps");

    /*while((pid=wait(NULL))!=-1){
      printf("[%d] terminé\n", pid);
    }*/

  }
  while(getchar()){

    kill(0, SIGKILL);
  }
  /*kill(getpid(), 0);*/
}

int main(){

  observe(2);
  return 0;
}
