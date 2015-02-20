#ifndef CLIENT__H
#define CLIENT__H
/* namespace cln_ */

#include <netinet/in.h>

typedef struct _tcp_client
{
	int sockd;
	struct sockaddr_in server;
} tcp_client;

void cln_init(tcp_client * self, char const * ip_address, int listen_port);
void cln_start_comm(tcp_client self);
void cln_shutdown(tcp_client self);

void err_handler(char const * cause, int status);
void delete_newline(char string []);
void fflushin(void);

#endif