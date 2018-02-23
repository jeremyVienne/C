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

int m_read(int fd, char *buffer,int size ) {
  int status;
  status= read(fd,buffer,size);
  assert(status!=-1);
  return status;
}



int m_close(int fd){
    int status;
    status=close(fd);
    return status;
}

int main(int argc, char * argv[]){

  int fd;
  int size;
  int n;
  char *buffer;
  assert(argc>1);



  buffer=getenv("MCAT_BUFSIZ");


  size=atoi(buffer);

  buffer=(char*)malloc(size*sizeof(char));


  fd=m_open(argv[1]);

  while((n=m_read(fd, buffer,size))>0){

    write(1,buffer,n);
  }
  m_close(fd);
  free(buffer);
  return 0;
}
