#ifndef SERVER__H
#define SERVER__H
/* namespace svr_ */

#include <netinet/in.h>

typedef struct _udp_server
{
	int sockd;
	struct sockaddr_in data;
} udp_server;

void svr_init(udp_server * self, int listen_port);
void svr_start_comm(udp_server self);
void svr_shutdown(udp_server self);

void err_handler(char const * cause, int status);

#endif