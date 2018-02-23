/* mshell - a job manager */

#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "jobs.h"
#include "cmd.h"

void do_help() {
    printf("available commands are:\n");
    printf(" exit - cause the shell to exit\n");
    printf(BOLD "\t exit\n" NORM);
    printf(" jobs - display status of jobs in the current session\n");
    printf(BOLD "\t jobs\n" NORM);
    printf(" fg   - run a job identified by its pid or job id in the foreground\n");
    printf(BOLD "\t fg " NORM "pid" BOLD "|" NORM "jobid \n");
    printf(" bg   - run a job identified by its pid or job id in the background\n");
    printf(BOLD "\t bg " NORM "pid" BOLD "|" NORM "jobid \n");
    printf(" stop - stop a job identified by its pid or job id\n");
    printf(BOLD "\t stop " NORM "pid" BOLD "|" NORM "jobid \n");
    printf(" kill - kill a job identified by its pid or job id\n");
    printf(BOLD "\t kill " NORM "pid" BOLD "|" NORM "jobid \n");
    printf(" help - print this message\n");
    printf(BOLD "\t help\n" NORM);
    printf("\n");
    printf("ctrl-z and ctrl-c can be used to send a SIGTSTP and a SIGINT, respectively\n\n");
}

/* treat_argv - Determine pid or jobid and return the associated job structure */
struct job_t *treat_argv(char **argv) {
    struct job_t *jobp = NULL;

    /* Ignore command if no argument */
    if (argv[1] == NULL) {
        printf("%s command requires PID or %%jobid argument\n", argv[0]);
        return NULL;
    }

    /* Parse the required PID or %JID arg */
    if (isdigit((int) argv[1][0])) {
        pid_t pid = atoi(argv[1]);
        if (!(jobp = jobs_getjobpid(pid))) {
            printf("(%d): No such process\n", (int) pid);
            return NULL;
        }
    } else if (argv[1][0] == '%') {
        int jid = atoi(&argv[1][1]);
        if (!(jobp = jobs_getjobjid(jid))) {
            printf("%s: No such job\n", argv[1]);
            return NULL;
        }
    } else {
        printf("%s: argument must be a PID or %%jobid\n", argv[0]);
        return NULL;
    }

    return jobp;
}


/* do_bg - Execute the builtin bg command */
void do_bg(char **argv) {
    struct job_t *job;
    pid_t pid ;
    if(strcmp(argv[1], "%")){
      job=jobs_getjobjid(atoi(argv[1]+1));
      pid=job->jb_pid;
    }
    else{

     pid  = atoi(argv[1]);
    }
    kill(pid, SIGCONT);
    job=jobs_getjobpid(pid);
    job->jb_state=BG;
    return;
}

/* waitfg - Block until process pid is no longer the foreground process */
void waitfg(pid_t pid) {
    struct job_t *job;
    job= jobs_getjobpid(pid);
    if(job == NULL){return; }
    while(job->jb_state==FG){
      sleep(1);
      if(verbose){
        printf("j'attend la fin du processus\n");
      }
    }
    if(verbose){
      printf("je reprend la main\n");
    }

}

/* do_fg - Execute the builtin fg command */
void do_fg(char **argv) {
    if(verbose){
      printf("je rentre dans do_fg");
    }
    struct job_t *job;
    job=treat_argv(argv);
    if(job==NULL){
      if(verbose){
        printf("job == NULL dans do_fg");
      }
      return;}
    kill(job->jb_pid, SIGCONT);
    job->jb_state=FG;
    waitfg(job->jb_pid);
    if(verbose){
      printf("je sors de do_fg");
    }
}

/* do_stop - Execute the builtin stop command */
void do_stop(char **argv) {
  struct job_t *job_to_kill;
  job_to_kill=jobs_getjobpid(atoi(argv[1]));
  if(job_to_kill==NULL){return;}
  kill(job_to_kill->jb_pid, SIGSTOP);
  return;
}

/* do_kill - Execute the builtin kill command */
void do_kill(char **argv) {
    struct job_t *job_to_kill;
    if(strcmp(argv[1], "%")){
      job_to_kill=jobs_getjobjid(atoi(argv[1]+1));
    }
    else{
      job_to_kill=jobs_getjobpid(atoi(argv[1]));
    }
    if(job_to_kill==NULL){return;}
    kill(job_to_kill->jb_pid, SIGKILL);
    return;
}

/* do_exit - Execute the builtin exit command */
void do_exit() {
    struct job_t *job;
    job= jobs_getstoppedjob();
    if(job!=NULL){
      printf("deconnexion \nIl ys a des tâches stopées\n");
      return;
    }

    while((job=jobs_getjobjid(jobs_maxjid()))!=NULL){
      kill(job->jb_pid, SIGKILL);
      jobs_deletejob(job->jb_pid);
    }
    kill(getpid(), SIGKILL);


    return;
}

/* do_jobs - Execute the builtin fg command */
void do_jobs() {
  jobs_listjobs();
  printf("\n");
}
