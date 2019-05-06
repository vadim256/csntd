#include "include/color_output.h"
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
#include <pcap.h>

#define ROOT_DIR "/"


//int Daemon(void){ }

int main(void){

pid_t pid = fork();
	
		if(pid < 0){
		printf(AC_RED "[error] failed to create process\n" AC_RESET);
		exit(1);
		} else if(pid != 0){
		printf(AC_RED "[error] process already created\n" AC_RESET);
		exit(2);
    }
		if(pid == 0){
			chdir(ROOT_DIR);
			setsid();
			close(STDIN_FILENO);
      close(STDOUT_FILENO);
   		close(STDERR_FILENO);
  //    Daemon();
	}
	return 0;
}