#include<sock.h>
#include<pwd.h>
#include<unistd.h>

int alreadyIn(char *list[],int count,char *ip) {

    for(int i=0;i<count;i++)
        if(strcmp(list[i],ip)==0)
            return 1;
    return 0;
}


void sender() {

    FILE *IPs;
    char *sentIPs[200],line[100],*ip,msg[100],hname[50];
    int count=0;
    char iline[50],interface[50],cmd[200];
    FILE *temp,*log;

    ////hostname
    gethostname(hname,50);
    strcpy(msg,"WHATSAPP_ARP : ");
    strcat(msg,hname);
    ////
    
    /////Initialisation for arp-scan
    system("ifconfig | cut -c1-8 | sort -u | grep -E -o 'w[a-z|A-Z|0-9]*' > /etc/whatsapp/whatsappARP/interface");
    temp=fopen("/etc/whatsapp/whatsappARP/interface","r");
    if(fgets(iline,50,temp)) {
	    sscanf(iline,"%s\n",interface);
	    sprintf(cmd,"arp-scan --localnet --interface %s | grep -E  -o '[0-9]+(.)[0-9]+(.)[0-9]+(.)[0-9]+' > /etc/whatsapp/whatsappARP/IPs",interface);
    }
    else
	    sprintf(cmd,"arp-scan --localnet | grep -E  -o '[0-9]+(.)[0-9]+(.)[0-9]+(.)[0-9]+' > /etc/whatsapp/whatsappARP/IPs");
    fclose(temp);
    ///////////

    while(1) {
    
    log=fopen("/etc/whatsapp/whatsappARP/sender.log","a+");

    system(cmd);
    IPs=fopen("/etc/whatsapp/whatsappARP/IPs","r");
    
    if(IPs) {
        while(fgets(line,20,IPs)) {
        
            if(ip=(char *)malloc(20)) {
                memset(ip,'\0',20);
                sscanf(line,"%s\n",ip);

                if(!alreadyIn(sentIPs,count,ip)) {
                    senderSocket *sock = senderSock(ip,2424);
                    sendMsg(sock,msg);
                    sentIPs[count++]=ip;
		    fprintf(log,"%s %s\n",msg,ip);
		    fclose(log);
                }
                else
                    free(ip);
            }
        }
    sleep(5);
    
    }


    }
}


void listener() {   
    int pid,count=0;
    char line[20],msg[1024],*ip,*clientIP,*recvdIPs[200],tok1[50],tok2[50],entry[100];
    FILE *hosts,*log;

    listenerSocket *sock = listenerSock(2424);
    
    while(1) {
        
    	log=fopen("/etc/whatsapp/whatsappARP/listener.log","a+");
        
	recvMsg(sock,msg);
        clientIP=getIP(sock);

        hosts=fopen("/etc/whatsapp/whatsappARP/hosts","r");

	if(hosts) {
            while(fgets(line,20,hosts)) {
                ip=(char *) malloc(20);
                sscanf(line,"%s\n",ip);
                if(!alreadyIn(recvdIPs,count,ip))
                    recvdIPs[count++]=ip;
                else
                    free(ip);
                memset(line,'\0',20);
            }
            fclose(hosts);
        }
	
	fprintf(log,"[1] %s %s\n ",msg,clientIP);

        if(!alreadyIn(recvdIPs,count,clientIP)){
            sscanf(msg,"%s : %s",tok1,tok2);
	    
	    fprintf(log,"[2] :%s:%s:\n",tok1,tok2);  //logger
            
	    if(strcmp(tok1,"WHATSAPP_ARP")==0) {
                hosts=fopen("/etc/whatsapp/whatsappARP/hosts","a+");
                memset(entry,'\0',1024);
                sprintf(entry,"%s %s",tok2,clientIP);
                fprintf(hosts,"%s\n",entry);

		fprintf(log,"[3] %s\n",entry);      //logger
                
		fclose(hosts);
            }
        }
    	fclose(log);  
    }
}



int main() {
    
    register struct passwd *pw;
    register uid_t uid;
    
    uid = geteuid ();
    pw = getpwuid (uid);
    if (pw)
    {
      if(strcmp(pw->pw_name,"root")!=0) {
	  fprintf(stdout,"Protocol must run with root privileges: FAILURE\n");
          exit (EXIT_FAILURE);
      }
    }

    int pid=fork();
    
    if(pid==0)
        sender();
    else
        listener();
   
    return 0;
}
