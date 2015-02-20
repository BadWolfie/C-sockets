#include "client.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

void cln_init(udp_client * self, char const * ip_address, int listen_port)
{
	self->server.sin_family = AF_INET;
	self->server.sin_addr.s_addr = inet_addr(ip_address);
	self->server.sin_port = htons(listen_port);

	printf("\nCreating socket... ");
	self->sockd = socket(AF_INET, SOCK_DGRAM, 0);
	err_handler("(socket)", self->sockd);
	printf("Done.\n");
}

void cln_start_comm(udp_client self)
{
	int status;
	char data_buffer[1024];
	int server_size = sizeof(self.server);

	do {
		printf("\nType in your message: ");
		memset(data_buffer, 0, sizeof(data_buffer));

		fflushin();
		fgets(data_buffer, sizeof(data_buffer), stdin);
		delete_newline(data_buffer);

		printf("\nSending message... ");
		status = sendto(self.sockd,
			data_buffer,
			strlen(data_buffer), 0,
			(struct sockaddr *) &self.server,
			(socklen_t) server_size);
		err_handler("(send)", status);
		printf("Done.\n");

		printf("\nWaiting for confirmation... ");
		memset(data_buffer, 0, sizeof(data_buffer));
		status = recvfrom(self.sockd,
			data_buffer,
			sizeof(data_buffer), 0,
			(struct sockaddr *) &self.server,
			(socklen_t *) &server_size);
		err_handler("(recv)", status);
		printf("%s\n", data_buffer);
	} while (strcmp(data_buffer,"Close connection.") != 0);
}

void cln_shutdown(udp_client self)
{
	printf("\nShutting down the client... ");
	close(self.sockd);
	printf("Done.\n");
}


void err_handler(char const *cause, int status)
{
	char const * err = " Error";
	char aux[150];

	if (status == -1) {
		strcpy(aux, cause);
		perror(strcat(aux, err));
		exit(1);
	}
}

void delete_newline(char * string)
{
	char * seek = strchr(string,'\n');
	if (seek)
		*seek = (char) 0;
}

void fflushin(void)
{
	int aux, i;
	aux = stdin->_IO_read_end - stdin->_IO_read_ptr;
	for (i = 0; i < aux; i++)
		getchar();
}
