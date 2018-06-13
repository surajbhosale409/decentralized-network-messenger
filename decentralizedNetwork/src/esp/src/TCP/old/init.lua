wifi.setmode(wifi.SOFTAP)
wifi.ap.setip({netmask="255.255.255.0"})
wifi.ap.config({ssid="MYNETWORK",pwd="12345678"})
wifi.ap.dhcp.start()

print ("WIFI CHANNEL:" ..wifi.getchannel())
print ("IP:" ..wifi.ap.getip())
routetable=wifi.ap.getclient()
for mac,ip in pairs(routetable) do
    print(mac,ip)
end
