#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


typedef int(*funct_t) (int);


int multif(funct_t f[], int args[], int n){
  int i;
  int status;
  int resultat;
  pid_t pid;

  resultat=0;
  for (i=0;i<n;i++){
    pid= fork();
    switch (pid) {
      case -1:
        perror("erreur fork");
        exit(EXIT_FAILURE);
      case 0:
        sleep(2);
        exit(f[i](args[i]));
      default:
        pid=wait(&status);
        if(WIFEXITED(status)){

          resultat=resultat||WEXITSTATUS(status);
          printf("valeur de retour pour la valeur args[%i]: %i\n",i,resultat);

        }

        break;
    }
  }



  return resultat;
}

int testfunc(int args){
  if(args==0){
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int main (int argc, const char * argv[]){
  assert(argc>1);
  int args[argc];
  funct_t f[argc];

  int inc;
  for(inc=0; inc<argc-1;inc++){ /*remplie le tableau de fonction test et le tableau d'arguement args*/
    if(strcmp(argv[inc+1], "true")==0)
      args[inc]=0;
    else if(strcmp(argv[inc+1], "false")==0)
      args[inc]=-1;
    else{
      printf("%s\n", "wrong argument");
      return 1;
    }
    f[inc]=(funct_t)&testfunc;
  }
  printf("valeur retournée par multif: %i\n",multif(f, args,argc));

  return 0;
}
