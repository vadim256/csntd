
.PHONY: clean all
all: csntd

CC := gcc
FLAGS :=  -Wall
DAEMON := csntd
PROCESS := cli_control

${DAEMON}: ../daemon.c ${PROCESS}
	${CC} ${FLAGS} ../daemon.c -o ./bin/${DAEMON} -lpcap

${PROCESS}: ../cli_process.c
	${CC} ${FLAGS} ../cli_process.c -o ./bin/${PROCESS}

clear: 
	rm -rf /build/bin/*.*


