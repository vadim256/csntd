#include "include/color_output.h"
#include "include/container_ip.h"
#include "include/daemon.h"


char devs[N][M];
FILE * logfile = NULL, 
	 * list_ip = NULL;
ListIP *list;	 


FILE * OpenPwdFile(const char * name){
	char *pwd = getenv("PWD");
	char buffer[1024];
	sprintf(buffer, "%s/%s", pwd, name);

	return fopen(buffer, "w+");
}
void CountDevices(){

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
	FILE * devices = fopen("/home/ameliepulen/sniffer/build/listdevices", "w+");
	int flag = 1;
	if(!devices){
		fprintf(logfile, "Don`t open file listdevices\n");
		flag = 0;
	}
	for(device = alldevsp; device; device = device->next, ++count){
		fprintf(logfile, "[%d] %s - %s\n" , count , device->name , device->description);
		if(device->name != NULL && count < N)
			strcpy(devs[count], device->name);
		if(flag) fprintf(devices, "%s\n", devs[count]);
	}

	if(flag) fclose(devices);
}

void Daemon(void){ 
	
	logfile = fopen("/home/ameliepulen/sniffer/build/sniffer.log", "w+");
	//logfile = OpenPwdFile("sniffer.log");
	Data data = {"0.0.0.0", 1};
	list = Create(data);
	CountDevices();

	char * dfldev = devs[0];
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t * handler = pcap_open_live(dfldev, BUFSIZ, 1, 10000, errbuf);
	
	if(!handler){
		fprintf(logfile, "Couldn't open device %s : %s\n" , dfldev, errbuf);
		exit(1);
	}

	u_char * packet = 0;
	struct pcap_pkthdr header;
	for(;;){

		packet = (u_char*) pcap_next(handler, &header);		
		if(!packet) continue;
				
		static int count = 0;                   // packet counter 
		const struct sniff_ip *ip;              // The IP header 
		int size_ip;
		count++;
		ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
		size_ip = IP_HL(ip)*4;
		if (size_ip < 20) {
			fprintf(logfile, "Invalid IP header length: %u bytes\n", size_ip);
			continue;
		}
	
		Data data;
		strcpy(data.address_ip, inet_ntoa(ip->ip_src));
		data.count_ip = 1;
		ListIP * f = Find(list, data);
		if(f == NULL)
		AddList(&list, data);
		else f->d.count_ip += 1;

		Print(list, logfile);
		//fflush(logfile);
		//fprintf(logfile, "From IP:\t Packet number %d\n", inet_ntoa(ip->ip_src), count);
	}				
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
  	    Daemon();
	}

	return 0;
}
