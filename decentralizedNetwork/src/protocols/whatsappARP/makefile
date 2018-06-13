CC = gcc
CFLAG = -c
libPath = /usr/lib/
startupScriptPath = /etc/init.d/
etcPath = /etc/whatsapp/whatsappARP/
binPath = /usr/sbin/


.PHONY: install_whatsappARP whatsappARP 

createEtcDir:
	mkdir -p $(etcPath)

install_init_script:
	cp  whatsappARP $(startupScriptPath)whatsappARP
	chmod +x  $(startupScriptPath)whatsappARP
	update-rc.d whatsappARP defaults
arp_scan:
	apt-get install arp-scan

install_whatsappARP: whatsappARP createEtcDir install_init_script arp_scan
	gcc whatsappARP.c $(libPath)libsock.a -o $(binPath)$<

