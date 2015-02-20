#include "nb-server.h"

#include <stdlib.h>

int main(int argc, char const *argv[])
{
	nb_tcp_server server;
	nb_svr_init(&server, atoi(argv[1]), atoi(argv[2]));
	nb_svr_start_comm(server);
	return 0;
}