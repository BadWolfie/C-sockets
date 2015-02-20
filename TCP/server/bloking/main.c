#include "server.h"

#include <stdlib.h>

int main(int argc, char const *argv[])
{
	tcp_server client;
	svr_init(&client, atoi(argv[1]), atoi(argv[2]));
	svr_start_comm(client);
	return 0;
}