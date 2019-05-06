
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

extern char * optarg;
extern int optind;

int main(int argc, char ** argv){
    const struct option daemon_opts[] = {
	    { "start", optional_argument, NULL, 'r'},
   	    {"stop", no_argument, NULL, 'p'},
	    {"show", required_argument, NULL, 'w'},
	    {"select", required_argument, NULL, 's'},
	    {"stat", required_argument, NULL, 't'},
	    {"help", no_argument, NULL, 'h'},
	    {NULL, 0, NULL, 0}
    };

    while((getopt_long(argc, argv, "r:pw:s:t:h", daemon_opts, NULL)) != -1){
    }

    return 0;
}