#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAILLE_TAMPON 16

int fd;
int n;
char *buffer;

/*retourne le nombre de retour a la ligne lu*/
int nb_retour(){

  int i;
  int nb;
  nb=0;
  for(i=0;i<(n*TAILLE_TAMPON);i++){
    if(buffer[i]=='\n'){
      nb++;
    }
  }
  return nb;
}

/*retourne la positon du dernier retour a la ligne pour les ntail lignes demander*/
int pos_write(int nb,int ntail,int size){
  int i;
  int e;
  e=nb;
  for(i=0;i<size;i++){
    if(e==(ntail+1)){
      if(buffer[i]=='\n'){
        return i;
      }
    }
    else if(buffer[i]=='\n'){
      e--;
    }
  }
  return 0;
}

/*version itérative de tail_efficace*/
void tail_efficace(const char *path, int ntail){
  int nb;
  int status;
  int pos;
  int size;
  int finish;
  int file_size;
  char *tmp;

  finish=0;
  n=1;
  fd=open(path,O_RDWR|O_CREAT,S_IROTH|S_IRGRP|S_IRUSR|S_IWUSR);
  size=n*TAILLE_TAMPON;
  file_size= lseek(fd,0,SEEK_END);
  while(finish==0){
    if(size > file_size){
      size=file_size;
      buffer=(char*)malloc(size*sizeof(char));
      lseek(fd,0,SEEK_SET);
      status=read(fd,buffer,size);
      nb=nb_retour();
      if(nb>=ntail){
        pos=pos_write(nb,ntail,size);
        size=size-pos;
        tmp=(char*)malloc(size*sizeof(char));
        strncpy(tmp, buffer+pos, size);
        write(STDOUT_FILENO,tmp,size);
        free(buffer);
        free(tmp);
      }
      else{
        write(STDOUT_FILENO, buffer,size);
        free(buffer);
      }
      finish=1;

    }
    else{
      size=n*TAILLE_TAMPON;
      buffer=(char*)malloc(size*sizeof(char));
      lseek(fd,-(size),SEEK_END);
      status=read(fd,buffer,size);
      nb=nb_retour();
      if(nb>ntail){
        pos=pos_write(nb,ntail,size);
        size=size-pos;
        tmp=(char*)malloc(size*sizeof(char));
        strncpy(tmp, buffer+pos, size);
        finish=1;
        write(STDOUT_FILENO,tmp,size);
        free(buffer);
        free(tmp);
      }
      else{
        n++;
      }

    }


  }

}
int main(int argc, char* argv[]){

  int required;
  int ch;
  assert(argc>1);
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

  tail_efficace(argv[1],required  );
  close(fd);
  return 0;
}
