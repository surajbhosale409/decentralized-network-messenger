#include"sock.h"

char * getIP(listenerSocket *sock) {
    return inet_ntoa(sock->client_addr.sin_addr);
}
