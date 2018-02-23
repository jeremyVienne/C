#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int vflag, rflag, wflag, xflag;

void usage (char *prog) {
   printf("usage : %s [rvwx] file", prog);
}

int maccess (int argc, char **argv) {
   int i;
   int res=0;


   printf("OPTIONS verbose:%i, read:%i, write:%i, exec:%i\n",vflag,rflag,wflag,xflag);
   printf("REMAINING %i ARGS:\n",argc);
   for (i = 0 ; i < argc; i++) {
      printf("\t%s\n",argv[i]);
   }
   if(rflag==1){ /* read permission test*/
    res=access(argv[0], R_OK);
    if(res==-1){
      printf("Error: %i\n", errno);
    }
   }
   if(wflag==1){ /* writing permission test*/
    res=access(argv[0], W_OK);
    if(res==-1){
      printf("Error: %i\n", errno);
    }
   }
   if(xflag==1){/*execute permission test*/
    res=access(argv[0], X_OK);
    if(res==-1){
      printf("Error: %i\n", errno);
    }
   }


   return res;
}

int main (int argc, char **argv) {
   int ch;
   int res;

   vflag = 0;
   rflag = 0;
   wflag = 0;
   xflag = 0;
   while ((ch = getopt(argc, argv, "vrwxh")) != -1) {
      switch (ch) {
      case 'v':
         vflag = 1;
         break;
      case 'r':
         rflag = 1;
         break;
      case 'w':
         wflag = 1;
         break;
      case 'x':
         xflag = 1;
         break;
      case 'h':
      default:
         usage(argv[0]);
      }
   }
   argc -= optind;
   argv += optind;
   res=maccess(argc,argv);
   return res;
}
