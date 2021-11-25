#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h> // INADDR_ANY
#include <unistd.h> // close()

#include "helpers.h"
#include "server.h"

int main(int argc, char **argv)
{
	printf("\n************************************************************\nConnecting server...\n\n");

	/* Server structure declaration */
	Server server;
	/* Initialisation */
	server.lg_addr_client = sizeof(server.addr_client);
	server.count_clients = 0;
	server.sockets_client = malloc(sizeof(int));

	/** @see server.h */
	create_socket_server(&server);
	connection(&server);

	printf("************************************************************\n\n");
	
	/* Initialize descriptors */
	FD_ZERO(&server.master_fds);
	FD_ZERO(&server.read_fds);
	FD_SET(server.socket_server, &server.master_fds);

	unsigned int x; // to loop

	/* Eternal server */
	while(1)
	{
		server.read_fds = server.master_fds;	// we use read_fds as temporary

		if (select(FD_SETSIZE, &server.read_fds, NULL, NULL, NULL) < 0)
			error("ERROR on select() ");

		for (x = 0; x < FD_SETSIZE; x++)
			if (FD_ISSET(x, &server.read_fds))
			{
				if (x == server.socket_server)
					new_client(&server);
				else
					connected_client(x, &server);
			}
	}

	free(server.sockets_client);
	return 0;
}