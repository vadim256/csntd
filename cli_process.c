#include "include/cli_process.h"
#include "include/color_output.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

extern char * optarg;
extern int optind;

void RunDaemon(const char * name_device){
	if(!name_device)
		name_device = "eth0";
	int exit_status;
	pid_t pid = fork();
	if(pid == -1){
		perror("fork");
		exit(1);
	}
	if(pid == 0){
		char *curpwd = (char *)getenv("PWD");
		char bufpwd[512];
		sprintf(bufpwd, "%s/csntd", curpwd);
		execl(bufpwd, "csntd", name_device, "NULL");
		fprintf(stderr, "Exec error\n");
		exit(2);

	} else {
		int childpid = wait(&exit_status);
		if (WIFEXITED (exit_status)) {
			printf("Process with PID=%d "
					"has exited with code=%d\n", childpid, 
					WEXITSTATUS (exit_status));
		}
		return;
	}

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
	char * name_device = 0;
    while((current_option = getopt_long(argc, argv, "r:pw:s:t:h", daemon_opts, NULL)) != -1){
		switch(current_option){
			case 'r':
				RunDaemon(optarg);
			return 0;				
			case 'p':
			case 'w':
			case 's':
			case 't':
			case 'h':
				fprintf(stdout, AC_GREEN"%s", help_str);
				fprintf(stdout, ""AC_RESET);
			return 0;
			case '?':
				fprintf(stderr, "%s", help_str);
				return 3;
		}
    }

    return 0;
}