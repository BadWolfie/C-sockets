#include "client.h"

#include <stdlib.h>

int main(int argc, char const *argv[])
{
	tcp_client client;
	cln_init(&client, argv[1], atoi(argv[2]));
	cln_start_comm(client);
	cln_shutdown(client);
	return 0;
}