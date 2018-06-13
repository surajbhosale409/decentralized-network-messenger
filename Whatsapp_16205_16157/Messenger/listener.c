#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

typedef struct socketData
{
    int listener_fd;
    struct sockaddr_in forward_addr,listener_addr, client_addr;
}socketData;

char * getIpByNum(char *destNum)
{
 char line[1024],*tip,*tnum;
 FILE *fp=NULL;
 int i=0;
 
 while(! (fp = fopen("resolver","r")))
 {}
 
 if (fp)
 {
      while(fgets(line,1024,fp))
      {
          tnum=(char *)malloc(20);
          memset(tnum,'\0',20);
      	  tip=(char *)malloc(20);
          memset(tip,'\0',20);
      
          sscanf(line,"%s %s\n",tnum,tip);
          if(strcmp(tnum,destNum)==0)
          { 
	     fclose(fp);
             return tip;
	  }

          memset(line,'\0',1024);
      }
      fclose(fp);
  }
}




void forwardMsg(socketData *sock,char *destNumber,char *msg)
{
 
 memset(&sock->forward_addr,'0',sizeof(sock->listener_addr));
 sock->forward_addr.sin_port=htons(65302);
 sock->forward_addr.sin_family=AF_INET;
 sock->forward_addr.sin_addr.s_addr = inet_addr(getIpByNum(destNumber)) ;
 
 sendto(sock->listener_fd,msg,strlen(msg),0,(struct sockaddr *) &sock->forward_addr,sizeof(sock->forward_addr));
}


socketData * listenerSocket(int port) 
{
 socketData *sock;

 sock=(socketData *)malloc(sizeof(socketData));
 
 sock->listener_fd=socket(AF_INET,SOCK_DGRAM,0);
    if(sock->listener_fd==-1)
    {
        perror("Unable to initiate listener socket");
        exit(1);
    }

 memset(&sock->listener_addr,'0',sizeof(sock->listener_addr));     //fill addr with '0'

 sock->listener_addr.sin_family = AF_INET;
 sock->listener_addr.sin_addr.s_addr = htonl(INADDR_ANY);
 sock->listener_addr.sin_port=htons(port);

 if(bind(sock->listener_fd , (struct sockaddr *) &sock->listener_addr , sizeof(sock->listener_addr) ) == -1)
 {
     fprintf(stdout,"Address Binding Failed");
     exit(1);
 }

 return sock; 
}




int main(int argc, const char *argv[])
{
    socketData *sock;
    sock=listenerSocket(65302);
    char *tokMsg,username[20],msg[1024],destNumber[20];
    int pid,r=5,addrlen,i=-1;
    
    addrlen=sizeof(sock->client_addr);

    
    while(1)
    {
        
        fprintf(stdout,"\033[%d;%df",1,60);                            
        fprintf(stdout,"                   ####Display####                 ");   //FIXED HEADERS FOR DISPLAY (FOR LOOK AND FEEL ONLY)
        fprintf(stdout,"\033[%d;%df",2,95);
        fprintf(stdout,"User Logged In:  %s",argv[1]);
        fprintf(stdout,"\033[%d;%df",4,90);
        fprintf(stdout,"###INBOX###    ");

        
        memset(msg,'\0',1024);
        recvfrom(sock->listener_fd, msg , 1024 , 0 , (struct sockaddr *) &sock->client_addr , (socklen_t *) &addrlen );

        strcpy(destNumber,msg+(strlen(msg)-10));
        
        if(strcmp(destNumber,argv[1])==0)
        {
        tokMsg=strtok(msg,"~");
        fprintf(stdout,"\033[%d;%df",r,90);    // for displaying output on right portion of terminal so no overlapping with kbd
        fputs(tokMsg,stdout);
        r++;
        }
        else
        {
         pid=fork();
         if(pid==0)
         {
          forwardMsg(sock,destNumber,msg);
         }

        }

   }

   return 0;
}


