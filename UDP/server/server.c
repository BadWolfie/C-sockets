#include "server.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

void svr_init(udp_server * self, int listen_port)
{
	self->data.sin_family = AF_INET;
	self->data.sin_addr.s_addr = htonl(INADDR_ANY);
	self->data.sin_port = htons(listen_port);

	printf("\nCreating socket... ");
	self->sockd = socket(AF_INET, SOCK_DGRAM, 0);
	err_handler("(socket)", self->sockd);
	printf("Done.\n");
}

void svr_start_comm(udp_server self)
{
	int status;
	printf("Binding address... ");
	status = bind(self.sockd,
		(struct sockaddr *) &self.data,
		sizeof(self.data));
	err_handler("(bind)", status);
	printf("Done.\n");

	struct sockaddr_in client;
	int client_size = sizeof(client);
	char data_buffer[1024];

	while (true) {
		printf("\nWaiting for a message... ");
		memset(data_buffer, 0, sizeof(data_buffer));
		status = recvfrom(self.sockd,
			data_buffer,
			sizeof(data_buffer), 0,
			(struct sockaddr *) &client,
			(socklen_t *) &client_size);
		err_handler("(recv)", status);
		printf("Message received:\n %s\n", data_buffer);

		printf("\nSendind confirmation... ");

		if (!strcmp(data_buffer, "Close connection.")) {
			status = sendto(self.sockd,
				data_buffer,
				strlen(data_buffer), 0,
				(struct sockaddr *) &client,
				(socklen_t) client_size);
			err_handler("(send)", status);
			printf("Done.\n");
			continue;
		}

		memset(data_buffer, 0, sizeof(data_buffer));
		strcpy(data_buffer, "Your message have been received.");

		status = sendto(self.sockd,
			data_buffer,
			strlen(data_buffer), 0,
			(struct sockaddr *) &client,
			(socklen_t) client_size);
		err_handler("(send)", status);
		printf("Done.\n");
	}
}

void svr_shutdown(udp_server self)
{
	printf("\nShutting down the server... ");
	close(self.sockd);
	printf("Done.\n");
	exit(0);
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