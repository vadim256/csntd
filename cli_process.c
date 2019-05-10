#include "include/cli_process.h"
#include "include/color_output.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>

extern char * optarg;
extern int optind;


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

