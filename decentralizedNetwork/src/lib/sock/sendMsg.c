#include"sock.h"

int sendMsg ( senderSocket *sock, char *msg) {
    if(sendto(sock->conn_fd ,msg , strlen(msg) , 0 , (struct sockaddr *) &sock->listener_addr , sizeof(sock->listener_addr) ) == -1)
        return 0;

    return 1;
}
