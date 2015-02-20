#include "server.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

void svr_init(tcp_server * self, int listen_port, int connections_no)
{
	self->connections_no = connections_no;

	self->data.sin_family = AF_INET;
	self->data.sin_addr.s_addr = htonl(INADDR_ANY);
	self->data.sin_port = htons(listen_port);

	printf("\nCreating socket... ");
	self->sockd = socket(AF_INET, SOCK_STREAM, 0);
	err_handler("(socket)", self->sockd);
	printf("Done.\n");
}

void svr_start_comm(tcp_server self)
{
	int status, channel;
	printf("Binding address... ");
	status = bind(self.sockd,
		(struct sockaddr *) &self.data,
		sizeof(self.data));
	err_handler("(bind)", status);
	printf("Done.\n");

	printf("\nListening for petitions... ");
	status = listen(self.sockd, self.connections_no);
	err_handler("(listen)", status);
	printf("Done.\n");

	struct sockaddr_in client;
	int client_size = sizeof(client);
	char data_buffer[1024];

	while (true) {
		printf("Petition received... ");
		channel = accept(self.sockd,
			(struct sockaddr *) &client,
			(socklen_t *) &client_size);
		err_handler("(accept)", channel);
		printf("Accepted on channel %d.\n", channel);

		while (true) {
			printf("\nWaiting for a message... ");
			memset(data_buffer, 0, sizeof(data_buffer));
			status = recv(channel, data_buffer, sizeof(data_buffer), 0);
			err_handler("(recv)", status);
			printf("Message received:\n %s\n", data_buffer);

			printf("\nSendind confirmation... ");

			if (!strcmp(data_buffer, "Close connection.")) {
				status = send(channel, data_buffer, strlen(data_buffer), 0);
				err_handler("(send)", status);
				printf("Done.\n");
				break;
			}

			memset(data_buffer, 0, sizeof(data_buffer));
			strcpy(data_buffer, "Your message have been received.");

			status = send(channel, data_buffer, strlen(data_buffer), 0);
			err_handler("(send)", status);
			printf("Done.\n");
		}

		printf("\nClosing channel... ");
		close(channel);
		printf("Done.\n");
	}
}

void svr_shutdown(tcp_server self)
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