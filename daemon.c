#include "include/color_output.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/wait.h>

#include <pcap.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>

#include <ctype.h>
#include <errno.h>
#include <arpa/inet.h>

#define ROOT_DIR "/"

//ethernet headers are always exactly 14 bytes [1] 
#define SIZE_ETHERNET 14

// IP header
struct sniff_ip {
        u_char  ip_vhl;                 /* version << 4 | header length >> 2 */
        u_char  ip_tos;                 /* type of service */
        u_short ip_len;                 /* total length */
        u_short ip_id;                  /* identification */
        u_short ip_off;                 /* fragment offset field */
        #define IP_RF 0x8000            /* reserved fragment flag */
        #define IP_DF 0x4000            /* dont fragment flag */
        #define IP_MF 0x2000            /* more fragments flag */
        #define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
        u_char  ip_ttl;                 /* time to live */
        u_char  ip_p;                   /* protocol */
        u_short ip_sum;                 /* checksum */
        struct  in_addr ip_src,ip_dst;  /* source and dest address */
};
#define IP_HL(ip)               (((ip)->ip_vhl) & 0x0f)
#define IP_V(ip)                (((ip)->ip_vhl) >> 4)


char devs[128][256];
FILE * logfile = NULL, 
	 * list_ip = NULL;
	 

void ProcessPacket(u_char * arg, const struct pcap_pkthdr * header, const u_char * packet){

	static int count = 1;                   // packet counter 
	const struct sniff_ip *ip;              // The IP header 
	int size_ip;
	count++;
	ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
	size_ip = IP_HL(ip)*4;
	if (size_ip < 20) {
		fprintf(logfile, "Invalid IP header length: %u bytes\n", size_ip);
		return;
	}
	fprintf(logfile, "From IP: %s\t Packet number %d\n", inet_ntoa(ip->ip_src), count);
	return;
}
void IndexInterface(){

	if(!logfile){
		exit(1);
	}
	fprintf(logfile, "Finding available devices ...\n");
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t * alldevsp;

	if(pcap_findalldevs(&alldevsp, errbuf)){
		fprintf(logfile,"Error finding devices: %s\n", errbuf);
		exit(1);
	}
	fprintf(logfile, "\nAvailable Devices are :\n");
	pcap_if_t * device = NULL;
	int count = 0;
	FILE * devices = fopen("/tmp/listdevices", "w");
	if(!devices){
		fprintf(logfile, "Don`t open file listdevices\n");
		exit(1);
	}
	for(device = alldevsp; device; device = device->next, ++count){
		fprintf(logfile, "[%d] %s - %s\n" , count , device->name , device->description);
		if(device->name != NULL && count < 128)
			strcpy(devs[count], device->name);
		fprintf(devices, "%s\n", devs[count]);
	}
	fclose(devices);
}

void Daemon(void){ 

	IndexInterface();
	
	char * dfldev = devs[0];
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t * handler = pcap_open_live(dfldev, BUFSIZ, 1, 1000, errbuf);
	
	if(!handler){
		fprintf(logfile, "Couldn't open device %s : %s\n" , dfldev, errbuf);
		exit(1);
	}
	pcap_loop(handler, -1, ProcessPacket, 0);

}

int main(void){

	pid_t pid = fork();
	
	if(pid == -1){
		fprintf(stderr, AC_RED"[error] failed to create process\n"AC_RESET);
		exit(1);
	}
	if(pid == 0){
		chdir(ROOT_DIR);
		setsid();
		close(STDIN_FILENO);
   		close(STDOUT_FILENO);
   		close(STDERR_FILENO);
		logfile = fopen("/tmp/sniffer.log", "w");
  	    Daemon();
	}

	return 0;
}