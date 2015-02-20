#include "server.h"

#include <stdlib.h>

int main(int argc, char const *argv[])
{
	udp_server server;
	svr_init(&server, atoi(argv[1]));
	svr_start_comm(server);
	return 0;
}