#include<stdio.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <assert.h>

/**************************************/

struct st_lien{
  dev_t st_dev;
  ino_t st_ino;
};
/**************************************/

static struct st_lien *see; /*struct wich represent all the link already seen*/
int opt_apparent_size,opt_follow_link;
int link_saw;/*increment to know the max size of struct see*/

int valid_name(char *name){
  int res= (strcmp(name, "..") && strcmp(name,"."));
  return res;
}

void usage (char *prog) {
   printf("usage : %s [Lb] file", prog);
   printf("usage : %s [B 512] file", prog);
}

/*check if the link was already seen*/
int check(dev_t st_dev, ino_t st_ino){
  int inc;
  int ok=0;
  for(inc=0; inc<link_saw;inc++){
    if(see[inc].st_dev==st_dev && see[inc].st_ino==st_ino){
      ok=-1;
    }
  }
  if(ok==0){
    see[link_saw].st_dev=st_dev;
    see[link_saw].st_ino=st_ino;
    link_saw+=1;
    return 0;
  }
  return -1;
}

int du_file(const char *pathname){
  DIR* dir;
  struct dirent *file;
  struct stat st;
  char tmp[PATH_MAX+1];
  int status;
  int res=0;
  dir =opendir(pathname);

  assert(dir!=NULL);
  status=lstat(pathname,&st);
  assert(status==0);

  res=opt_apparent_size?st.st_size:st.st_blocks;
  while((file=readdir(dir))!=NULL){
    if(valid_name(file->d_name)){

      snprintf(tmp, PATH_MAX+1, "%s/%s",pathname, file->d_name);
      status=lstat(tmp,&st);
      assert(status==0);

      res+=opt_apparent_size?st.st_size:st.st_blocks; /*opt apparent size or real size*/
      if(S_ISDIR(st.st_mode)){/*if the file is a directory*/

        res+=du_file(tmp);
      }
      if(S_ISLNK(st.st_mode) && opt_follow_link==1){ /*option follow link and if the file is a link*/
        char link[PATH_MAX+1];
        status =readlink(tmp,link,PATH_MAX);
        assert(status!=-1);
        link[status]='\0';

        assert(check(st.st_dev,st.st_ino)==0);
        res+=du_file(link);

      }
    }
  }
  return res;
}



int main(int argc ,char *argv[]) {
  int ch;
  link_saw=0;
  assert(argc>1);


  opt_apparent_size=0;
  opt_follow_link=0;

  while ((ch = getopt(argc, argv, "bBL")) != -1) {
     switch (ch) {
     case 'b':
        opt_apparent_size=1;
        break;
     case 'L':
        opt_follow_link = 1;
        break;
     default:
        return 0;
     }
  }
  argc -= optind;
  argv += optind;
  printf("%i\n",du_file(argv[0]));
  return 0;

}
