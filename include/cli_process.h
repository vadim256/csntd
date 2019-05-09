#ifndef CLI_PROCESS_H_
#define CLI_PROCESS_H_
const char * const help_str = 
	"Usage: cli_process [options]...\n"
	"Options: \n"
	"--start, -r                    packets are being sniffed from now on from default iface(eth0)\n"
	"--stop​, -p                     packets are not sniffed\n"
	"--show [ip], -w [ip]           count print number of packets received from ip address\n"
	"--select [iface], -s [iface]   select interface for sniffing eth0, wlan0, ethN, wlanN...\n"
    "--stat [iface]​, -t [iface]     show all collected statistics for particular interface,\n"
    "                               if iface omitted - for all interfaces\n"
    "--help, -h                     show usage information\n";
#endif