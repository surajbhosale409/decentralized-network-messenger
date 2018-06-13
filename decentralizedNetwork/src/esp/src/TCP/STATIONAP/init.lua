wifi.setmode(wifi.STATIONAP)
--wifi.setmode(wifi.SOFTAP)

--AP
wifi.ap.setip({ip="192.1.43.1",netmask="255.255.255.0"})
wifi.ap.config({ssid="ESPNETWORK1",pwd="qazmlp123"})
wifi.ap.dhcp.start({start="192.1.43.2"})

--Station
--wifi.sta.config("ESPNETWORK2","qazmlp123")
--wifi.sta.connect()

print ("WIFI CHANNEL:" ..wifi.getchannel())
print ("AP IP:" ..wifi.ap.getip())
--print ("STATION IP:" ..wifi.sta.getip())
routetable=wifi.ap.getclient()
for mac,ip in pairs(routetable) do
    print(mac,ip)
end
