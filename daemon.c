
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <resolv.h>
#define ROOT_DIR "/"


int Daemon(void)
{ }

int main(void){

	pid_t pid = fork();
	
    if(pid < 0){
		fprintf(stderr, "[error] failed to create process\n");
		exit(1);
	} else if(pid != 0){
		fprintf(stderr, "[error] process already created\n");
		exit(2);
    }
	if(pid == 0){
		chdir(ROOT_DIR);
		pid_t new_pid_session = setsid();
		close(STDIN_FILENO);
        close(STDOUT_FILENO);
   		close(STDERR_FILENO);
        Daemon();
	}
	return 0;
}