#ifndef SERVER__H
#define SERVER__H
/* namespace svr_ */

#include <netinet/in.h>

typedef struct _tcp_server
{
	int sockd;
	int connections_no;
	struct sockaddr_in data;
} tcp_server;

void svr_init(tcp_server * self, int listen_port, int connections_no);
void svr_start_comm(tcp_server self);
void svr_shutdown(tcp_server self);

void err_handler(char const * cause, int status);

#endif