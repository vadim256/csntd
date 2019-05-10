
.PHONY: clean all 
all: csntd

CC := gcc
FLAGS :=  -Wall
DAEMON := csntd
PROCESS := cli_control

${DAEMON}: ../daemon.c ${PROCESS} ../container_ip.c
	${CC} ${FLAGS} ../daemon.c ../container_ip.c -o ${DAEMON} -lpcap

${PROCESS}: ../cli_process.c
	${CC} ${FLAGS} ../cli_process.c -o ${PROCESS}

clear: 
	rm -rf /build/bin/*.*

