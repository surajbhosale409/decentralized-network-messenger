
sock=net.createUDPSocket()

function receiver(conn,data,port,ip)
    print(data)
    conn:send(port,ip,"Got it!!!")
end

if sock then
    sock:listen(9999)
    sock:on("receive",receiver)
end
