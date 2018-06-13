//Author: Suraj R Bhosale.

#ifndef _SOCK_H
#define _SOCK_H

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>


typedef struct senderSocket {
 int conn_fd;
 struct sockaddr_in listener_addr;
}senderSocket;


typedef struct listenerSocket {
 int listener_fd;
 struct sockaddr_in listener_addr, client_addr;
}listenerSocket;


senderSocket * senderSock(char *,int );
listenerSocket * listenerSock(int);
int sendMsg(senderSocket *,char *);
int recvMsg(listenerSocket *,char *);
char * getIP(listenerSocket *);


#endif
