#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>


int main(int argc,char *argv[])
{

  int pid;
  char usrname[30],*uname;
  char *myargv1[]={".connectorAR",argv[1]};
  char *myargv2[]={".listenerAR",argv[1]};
  FILE *fp;


   pid=fork();
   
   if(pid==0)
   {
    execve(myargv1[0],myargv1,NULL);                 // Child code, Child process will be replaced by connectorAR
   }
   else
   {
    execve(myargv2[0],myargv2,NULL);           // Parent process will be replaced by listenerAR
   }

return 0;
}




