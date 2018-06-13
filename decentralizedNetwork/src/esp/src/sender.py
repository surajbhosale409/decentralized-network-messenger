import socket

#FOR TCP
#Max bytes can be sent so ESP can forward that also to next host then max bytes to be sent is 1460
#Otherwise it can recieve max of 2920 bytes

byteCount=1460
data="#"*byteCount
sender=socket.socket(socket.AF_INET,socket.SOCK_STREAM,0)
sender.connect(("192.168.4.1",9999))
sender.send(data)




