wifi.setmode(wifi.STATIONAP)

--AP
wifi.ap.setip({ip="192.168.4.1",netmask="255.255.255.0"})
wifi.ap.config({ssid="MYNETWORK2",pwd="12345678"})
wifi.ap.dhcp.start({start="192.168.4.2"})

--Station
wifi.sta.config("MYNETWORK1","12345678")
wifi.sta.connect()

print ("WIFI CHANNEL:" ..wifi.getchannel())
print ("IP:" ..wifi.ap.getip())
routetable=wifi.ap.getclient()
for mac,ip in pairs(routetable) do
    print(mac,ip)
end
