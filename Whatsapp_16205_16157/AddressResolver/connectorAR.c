#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

typedef struct clientsocketData
{
    int conn_fd;
    struct sockaddr_in listener_addr;
}clientSocketData;



clientSocketData * clientSocket (char *ipaddr, int port)
{
    clientSocketData *sock;
    
    sock=(clientSocketData *) malloc (sizeof(clientSocketData));

    memset(&sock->listener_addr,'0',sizeof(sock->listener_addr));

    sock->conn_fd=socket(AF_INET,SOCK_DGRAM,0);
        if (sock->conn_fd == -1)
        {
            fprintf(stdout,"Unable To Initiate Client Socket");
            exit(1);
        }

    sock->listener_addr.sin_family = AF_INET;
    sock->listener_addr.sin_port = htons(port);
    sock->listener_addr.sin_addr.s_addr = inet_addr(ipaddr) ;

    return sock;
}



int main(int argc, const char *argv[])
{
 char usrnum[20],ipaddr[50],numbers[20];
 clientSocketData *sock;
 char *ip,*number;
 int i=-1;
 FILE *fp,*fpContacts;
 int counter=1;
 int pid;

 fp=fopen("contacts","a+");
 strcpy(usrnum,argv[1]);
 strcat(usrnum,"\n");
 fputs(usrnum,fp);
 fclose(fp);



 pid=fork();

 if(pid==0)
 {
   while(1){
     system("./.scanIPs > .IPs");
     sleep(5);
   }
 }
 while(1)
 {
     
     fp=fopen(".IPs","r");
     while(fgets(ipaddr,50,fp))
     {
     
     ip=strtok(ipaddr,"\n");    
     sock=clientSocket(ip,39994);
    
     fpContacts=fopen("contacts","r");

     while(fgets(numbers,20,fpContacts))
     {
     number=strtok(numbers,"\n");
     sendto(sock->conn_fd ,number , strlen(number) , 0 , (struct sockaddr *) &sock->listener_addr , sizeof(sock->listener_addr) );
     }
     fclose(fpContacts);


     if(counter%10==0)
     {
         sleep(1);
         counter=1;
     }
     else
         counter++;
     }
     fclose(fp);

 }

 return 0;
}

