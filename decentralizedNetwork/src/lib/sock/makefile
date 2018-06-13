CC = gcc
CFLAG = -c
libPath = /usr/lib/
includePath = /usr/include/

.PHONY: install_sock libsock.a 

sockObjects = $(libPath)senderSock.o $(libPath)listenerSock.o $(libPath)recvMsg.o $(libPath)sendMsg.o $(libPath)getIP.o

$(libPath)%.o: %.c
	$(CC) $(CFLAG) $< -o $@

libsock.a: $(sockObjects)
	ar rcs $(libPath)$@ $^

install_sock: libsock.a
	cp sock.h $(includePath)sock.h
	
