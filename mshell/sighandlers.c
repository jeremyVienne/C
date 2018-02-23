/* mshell - a job manager */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>


#include "jobs.h"
#include "common.h"
#include "sighandlers.h"

/*
 * wrapper for the sigaction function
 */
int sigaction_wrapper(int signum, handler_t * handler) {
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    if(sigaction(signum,&action , NULL)>0 ){return 1;}
    return 0;
}

/*
 * sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
 *     a child job terminates (becomes a zombie), or stops because it
 *     received a SIGSTOP or SIGTSTP signal. The handler reaps all
 *     available zombie children
 */
void sigchld_handler(int sig) {
    struct job_t *job;
    pid_t pid;
    int status;
    if(verbose){printf("je rentre dans sigchld_handler\n");}
    while((pid=waitpid(-1, &status, WNOHANG|WUNTRACED))>0){
      if(WIFEXITED(status)){
        if(verbose){printf("je rentre dans WIFEXITED\n");}
        job=jobs_getjobpid(pid);
        jobs_deletejob(pid);
      }
      else if(WIFSIGNALED(status)){
        if(verbose){printf("je rentre dans WIFSIGNALED\n");}
        job=jobs_getjobpid(pid);
        printf("\n[%d]+ Finished  %s\n",job->jb_jid ,job->jb_cmdline);
        jobs_deletejob(pid);
      }
      else if(WIFSTOPPED(status)>0){
        if(WSTOPSIG(status)>0){
          if(verbose){printf("je rentre dans WSTOPSIG\n");}
          job=jobs_getjobpid(pid);

          job->jb_state=ST;
          printf("\n[%d]+ Arrêté  %s\n", job->jb_jid, job->jb_cmdline);
        }
      }

    }

}

/*
 * sigint_handler - The kernel sends a SIGINT to the shell whenver the
 *    user types ctrl-c at the keyboard.  Catch it and send it along
 *    to the foreground job.
 */
void sigint_handler(int sig) {
  pid_t pid;
  pid=jobs_fgpid();
  if(pid>0){
    kill(-pid, sig);
  }
}

/*
 * sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
 *     the user types ctrl-z at the keyboard. Catch it and suspend the
 *     foreground job by sending it a SIGTSTP.
 */
void sigtstp_handler(int sig) {
  pid_t pid;

  pid=jobs_fgpid();
  if(pid>0){
    kill(-pid, sig);
  }
}
