#include"sock.h"

int recvMsg ( listenerSocket *sock, char *msg) {
    
    int addrlen=sizeof(sock->client_addr);
    memset(msg,'\0',1024);

    if(recvfrom(sock->listener_fd,msg,1024,0, (struct sockaddr *) &sock->client_addr , (socklen_t *) &addrlen ) == -1)
        return 0;

    return 1;
}
