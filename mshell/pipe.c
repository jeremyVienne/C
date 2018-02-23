/* mshell - a job manager */
#include <unistd.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pipe.h"
#include "cmd.h"
#include "jobs.h"
#include <sys/wait.h>

void do_pipe(char *cmds[MAXCMDS][MAXARGS], int nbcmd, int bg) {
    int fd[2];
    int status, inc;
    pid_t pid, pere;
    status = pipe(fd);
    assert(status!=-1);

    pere=fork();
    switch(pere){
      case -1:
        perror("fork error");
      case 0:
      setpgid(0,0);
      jobs_addjob(getpgrp(),bg, *cmds[nbcmd-1]);
      for(inc=0;inc<nbcmd;inc++){
        pid=fork();
        if(verbose){printf("\ncreation fork");}
        switch(pid){
          case -1:
            perror("fork error");
            break;
          case 0:
            if(verbose){
              printf("fork crée, gestion de la commande %i/%i\n", inc+1, nbcmd);
            }

            if(inc==0){

              if(verbose){
                printf("execute la premiere cmd\n");
              }
              close(fd[0]);
              dup2(fd[1], STDOUT_FILENO);
              execvp(cmds[inc][0], cmds[inc]);
              exit(EXIT_FAILURE);
            }
            else if (inc==nbcmd-1){
              if(verbose){
                printf("execute la derniere cmd\n");
              }
              close(fd[1]);
              dup2(fd[0], STDIN_FILENO);
              execvp(cmds[inc][0], cmds[inc]);

              exit(EXIT_FAILURE);
            }
            else{
              if(verbose){
                printf("execute la %i cmd\n", inc);
              }

              dup2(fd[0], STDIN_FILENO);
              dup2(fd[1], STDOUT_FILENO);
              execvp(cmds[inc][0], cmds[inc]);

              exit(EXIT_FAILURE);
            }


            while(wait(NULL)!=-1){
              kill(-pere, SIGKILL);

            }
            exit(EXIT_SUCCESS);

          case 1:

            break;
          default:

            break;
        }
      }

        exit(EXIT_SUCCESS);
      case 1:
        break;
      default:break;
    }



}
