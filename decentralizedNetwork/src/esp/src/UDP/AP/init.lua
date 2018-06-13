wifi.setmode(wifi.SOFTAP)
wifi.ap.setip({ip="192.168.3.1",netmask="255.255.255.0"})
wifi.ap.config({ssid="MYNETWORK1",pwd="12345678"})
wifi.ap.dhcp.start({start="192.168.3.2"})

print ("WIFI CHANNEL:" ..wifi.getchannel())
print ("IP:" ..wifi.ap.getip())
routetable=wifi.ap.getclient()
for mac,ip in pairs(routetable) do
    print(mac,ip)
end
