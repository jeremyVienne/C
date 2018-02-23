#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

int m_open(const char* path){
  int fd;
  fd=open(path,O_RDWR|O_CREAT,S_IROTH|S_IRGRP|S_IRUSR|S_IWUSR);
  assert(fd!=-1);

  return fd;
}

int m_close(int fd){
    int status;
    status=close(fd);
    return status;
}

int main(int argc, char * argv[]){
  int ch;
  int fd;
  int n;
  int nb;
  char buffer;
  int required;
  int inc;
  assert(argc>1);
  nb=0;

  inc=0;
  required=10;
  while ((ch = getopt(argc, argv, "n")) != -1) {
     switch (ch) {
     case 'n':
        required= atoi(argv[2]);
        argc -= optind;
        argv += optind;
        break;

     default:
          return 0;
     }
  }



  fd=m_open(argv[1]);

  while((n=read(fd,&buffer,1))>0){
    if(buffer=='\n'){
      nb++;
    }

  }
  if(required>nb){
    required=nb;
  }


  printf("Number of line: %i\n", nb);


  lseek(fd,0,SEEK_SET);

  while((n=read(fd,&buffer,1))>0){
    if(buffer =='\n'){
      inc++;
    }
    if(required>=(nb-inc)){
      write(STDOUT_FILENO, &buffer,1);
    }
  }
  write(STDOUT_FILENO,"\n",1);

  m_close(fd);
  return 0;
}
