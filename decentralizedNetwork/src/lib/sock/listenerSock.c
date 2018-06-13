#include"sock.h"

listenerSocket * listenerSock(int port)
{
    listenerSocket *sock;
    sock = (listenerSocket *) malloc (sizeof(listenerSocket));

    sock->listener_fd=socket(AF_INET,SOCK_DGRAM,0);
    if(sock->listener_fd==-1) {
        perror("Unable to initiate listener socket");
        exit(1);
    }

    memset(&sock->listener_addr,'0',sizeof(sock->listener_addr));     //fill addr with '0'
    sock->listener_addr.sin_family = AF_INET;
    sock->listener_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock->listener_addr.sin_port=htons(port);

    if(bind(sock->listener_fd , (struct sockaddr *) &sock->listener_addr , sizeof(sock->listener_addr) ) == -1) {                 
        fprintf(stdout,"Address Binding Failed");
        exit(1);
    }

    return sock; 
}



