routetable=wifi.ap.getclient()
for mac,ip in pairs(routetable) do
    print(mac,ip)
end