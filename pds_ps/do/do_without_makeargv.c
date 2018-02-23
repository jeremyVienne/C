#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
  int inc, status, resultat;
  pid_t pid;
  assert(argc>1);
  resultat=0;
  for(inc=2; inc<argc;inc++){
    pid=fork();
    switch (pid) {
      case -1:
        perror("fork error");
        exit(EXIT_FAILURE);
      case 0:
        printf("[%d] execute: %s\n",getpid(),argv[inc]);
        execvp(argv[inc], argv+inc);
        exit(EXIT_FAILURE);
      default:;
    }
  }

  while((pid=wait(&status))!=-1){
    if(WIFEXITED(status)){
      resultat|=WEXITSTATUS(status);
    }
  }
  exit(resultat);
}
