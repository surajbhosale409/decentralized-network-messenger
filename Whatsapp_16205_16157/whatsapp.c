#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>


int main(int argc,char *argv[])
{
  
   int pid;
   char usrname[30];
   char *myargv1[]={".addressResolver",argv[1]};
   char *myargv2[]={".messenger",argv[1]};
   char *myenv[]={"TERM=xterm-256color"};
   
   system("clear");  
 
   if(argc==2)
   {

   pid=fork();
   
   if(pid==-1)
   {
    fputs("Unable to initiate app\n",stdout);
    exit(1);
   }
   
   if(pid==0)
   {
    execve(myargv1[0],myargv2,myenv);       
   }
   else
   {
    execve(myargv2[0],myargv2,myenv);   
   }
 
   }
   else
       fputs("Specify Username: ./whatsapp <username>\n",stdout);

return 0;
}




