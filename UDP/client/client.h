#ifndef CLIENT__H
#define CLIENT__H
/* namespace cln_ */

#include <netinet/in.h>

typedef struct _udp_client
{
	int sockd;
	struct sockaddr_in server;
} udp_client;

void cln_init(udp_client * self, char const * ip_address, int listen_port);
void cln_start_comm(udp_client self);
void cln_shutdown(udp_client self);

void err_handler(char const * cause, int status);
void delete_newline(char string []);
void fflushin(void);

#endif