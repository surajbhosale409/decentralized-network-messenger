#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>


int main(int argc,char *argv[])
{

  system("clear");  
  int pid;
  char usrname[30],*uname;
  char *myargv1[]={".sender",argv[1]};
  char *myargv2[]={".listener",argv[1]};

   pid=fork();
   
   if(pid==0)
   {
    execve(myargv2[0],myargv2,NULL);       
   }
   else
   {
    execve(myargv1[0],myargv1,NULL);   
   }

return 0;
}




