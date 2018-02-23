#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "makeargv.c"

int opt_success, opt_fail, opt_c, opt_k;

int main(int argc, char * argv[]){
  int inc, status, resultat;
  char ** arg;
  char ch;
  int i;
  pid_t pid;
  assert(argc>1);
  opt_success=0;
  opt_fail=1;
  opt_c=0;
  opt_k=0;
  i=0;
  while ((ch = getopt(argc, argv, "oack")) != -1) {
     switch (ch) {
     case 'o':
        opt_success=1;
        opt_fail=0;
        break;
     case 'a':
        opt_fail = 1;
        opt_success=0;
        break;
      case 'c':
        opt_c=1;
        break;
      case 'k':
        opt_k=1;
        break;
     default:
        return 0;

     }
     i++;
  }
  argc -= i;
  argv += i;

  /*execution commande*/
  resultat=0;
  for(inc=2; inc<argc;inc++){
    pid=fork();
    switch (pid) {
      case -1:
        perror("fork error");
        exit(EXIT_FAILURE);
      case 0:
        arg= makeargv(argv[inc]);
        assert(arg!=NULL);
        printf("[%d] execute: %s %s\n",getpid(),arg[0], arg[1]);
        execvp(arg[0], arg);
        exit(EXIT_FAILURE);
      default:;
    }
  }

  while((pid=wait(&status))!=-1){
    if(WIFEXITED(status)){

      if(opt_fail==1 && WEXITSTATUS(status)==1){
        if(opt_c==1){
          exit(EXIT_FAILURE);
        }
        else{
          resultat=WEXITSTATUS(status);
        }
      }
      else if(opt_success==1 && WEXITSTATUS(status)==0){
        if(opt_c==1){
          exit(EXIT_SUCCESS);
        }
        resultat=WEXITSTATUS(status);
      }
      else{
        resultat|=WEXITSTATUS(status);
      }
    }

  }
  exit(resultat);
}
