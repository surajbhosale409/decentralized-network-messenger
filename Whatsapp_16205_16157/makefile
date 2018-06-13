whatsapp:
	gcc AddressResolver/connectorAR.c -o .connectorAR
	gcc AddressResolver/listenerAR.c -o .listenerAR
	gcc AddressResolver/addressResolver.c -o .addressResolver
	gcc Messenger/sender.c -o .sender
	gcc Messenger/listener.c -o .listener
	gcc Messenger/messenger.c -o .messenger
	gcc NetworkSetup/adhocCFG.c -o .adhocCFG
	gcc whatsapp.c -o whatsapp
enableAdHoc:	
	./.adhocCFG
disableAdHoc:
	sudo service network-manager start

uninstall:
	rm contacts resolver .adhocCFG .listenerAR .listener .connectorAR .addressResolver .sender .messenger whatsapp
	
