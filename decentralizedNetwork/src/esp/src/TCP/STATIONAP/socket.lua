if listener~=nil
then 
   listener:close()
end
listener=net.createServer(net.TCP,300)
sender=net.createConnection(net.TCP, 0)

function receiver(sck,data)
    print(data)
    sender:connect(9999,"192.1.45.1")
    sender:send(data)

    --sck:send("Got it!!")
end

if listener then
    listener:listen(9999,function(conn)
        conn:on("receive",receiver)
        --conn:send("Hello there!!!")
        end)
end
