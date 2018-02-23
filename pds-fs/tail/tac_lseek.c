#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

void tac_lseek(int fd){
  int status;
  char c;
  status=lseek(fd, 0, SEEK_END);
  status=lseek(fd,-1,SEEK_CUR);
  assert(status!=-1);
  read(fd,&c,1);
  write(STDOUT_FILENO, &c,1);
  while((lseek(fd,-2,SEEK_CUR))!=-1){
    read(fd,&c,1);
    write(STDOUT_FILENO,&c,1);
  }
  write(STDOUT_FILENO,"\n",1);
}

int main(int argc, const char* argv[]){
  int fd;
  assert(argc>1);

  fd=open(argv[1],O_RDWR|O_CREAT,S_IROTH|S_IRGRP|S_IRUSR|S_IWUSR);

  tac_lseek(fd);
  close(fd);
  return 0;
}
