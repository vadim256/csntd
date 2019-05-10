#include "include/cli_process.h"
#include "include/color_output.h"


void StopDaemon(){
	
	FILE * tmp = fopen("/home/ameliepulen/sniffer/build/pid_daemon.txt", "r+");
	if(!tmp)
		return;
	char buffer[128];
	fgets(buffer, 128, tmp);
	int daemon_pid = atoi(buffer);
	kill(daemon_pid, SIGUSR1);
	fclose(tmp);
}
void StartDaemon(){
	FILE * tmp = fopen("/home/ameliepulen/sniffer/build/pid_daemon.txt", "r+");
	if(!tmp)
		return;
	char buffer[128];
	fgets(buffer, 128, tmp);
	int daemon_pid = atoi(buffer);
	kill(daemon_pid, SIGUSR2);
	fclose(tmp);
}

int main(int argc, char ** argv){
    const struct option daemon_opts[] = {
	    {"start", optional_argument, NULL, 'r'},
   	  {"stop", no_argument, NULL, 'p'},
	    {"show", required_argument, NULL, 'w'},
	    {"select", required_argument, NULL, 's'},
	    {"stat", required_argument, NULL, 't'},
	    {"help", no_argument, NULL, 'h'},
	    {NULL, 0, NULL, 0}
    };
	int current_option;
	while((current_option = getopt_long(argc, argv, "r:pw:s:t:h", daemon_opts, NULL)) != -1){
		switch(current_option){
			
			case 'r':					
				printf("--start");
				StartDaemon();
				return 0;
			case 'p':
				printf("--stop");
				StopDaemon();
				return 0;
			case 'w':
				printf("--show");
				return 0;
			case 's':
				printf("--select");
				return 0;
			case 't':
				printf("--stat");
				return 0;
			case 'h':
				fprintf(stdout, AC_GREEN"%s", help_str);
				fprintf(stdout, ""AC_RESET);
			return 0;
			case '?':
				fprintf(stderr, AC_GREEN"%s", help_str);
				fprintf(stdout, ""AC_RESET);

				return 3;
		}
    }

    return 0;
}

