#include"sock.h"

senderSocket * senderSock(char *ipaddr,int port)
{
    senderSocket *sock;
    sock = (senderSocket *) malloc (sizeof(senderSocket));
    memset(&sock->listener_addr,'0',sizeof(sock->listener_addr));
    
    sock->conn_fd=socket(AF_INET,SOCK_DGRAM,0);
    if (sock->conn_fd == -1) {
        fprintf(stdout,"Unable To Initiate Client Socket");
        exit(1);
    }

    sock->listener_addr.sin_family = AF_INET;
    sock->listener_addr.sin_port = htons(port);
    sock->listener_addr.sin_addr.s_addr = inet_addr(ipaddr) ;
    
    return sock;
}


