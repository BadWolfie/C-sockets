#ifndef NB_SERVER__H
#define NB_SERVER__H
/* namespace nb_svr_ */

#include <netinet/in.h>

typedef struct _nb_tcp_server
{
	int sockd;
	int connections_no;
	struct sockaddr_in data;
} nb_tcp_server;

void nb_svr_init(nb_tcp_server * self, int listen_port, int connections_no);
void nb_svr_start_comm(nb_tcp_server self);
void nb_svr_shutdown(nb_tcp_server self);

void err_handler(char const * cause, int status);

#endif