/**
 * ********************************************
 * Functions and structures used in <server.c>
 * 
 * @author MagicBanana
 * ********************************************
 */

/*
typedef struct
{
	char pseudo[BUFFER_SIZE], *messages[BUFFER_SIZE];
	unsigned int count_messages;
} Client;
*/

typedef struct
{
	struct sockaddr_in addr_server, addr_client;
	int socket_server, *sockets_client, lg_addr_client;
	unsigned int count_clients;
	//unsigned int count_clients, count_connections;
	//Client *clients;
	fd_set master_fds, read_fds;
} Server;

/**
 * *************************************************
 * Create the TCP socket used by server
 * 
 * @param Server *server : pointer struct of server
 * *************************************************
 */ 
void create_socket_server(Server *server)
{
	/* Let's go ! */
	if ((server->socket_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		error("ERROR on socket() ");

	printf("-- Socket OK --\n\t* ID : %d\n", server->socket_server);
}

/**
 * **************************************************
 * Connection to server
 * 
 * @param Server *server : pointer struct of server
 * **************************************************
 */ 
void connection(Server *server)
{
	unsigned int port = 2000;
	unsigned char is_port_ok = 0;
	
	/* Initialize connection structure */
	bzero((char *) &server->addr_server, sizeof(server->addr_server));
	server->addr_server.sin_family = AF_INET;
	server->addr_server.sin_addr.s_addr = INADDR_ANY;
	
	/* Bind call */
	while (is_port_ok == 0)
	{
		server->addr_server.sin_port = htons(port);
		
		if (bind(server->socket_server, (struct sockaddr *) &server->addr_server, sizeof(server->addr_server)) < 0)
			port++;
		else
			is_port_ok = 1;
	}
	printf("-- Connection OK --\n\t* IP address : %s\n\t* Port : %d\n", "127.0.0.1", port);
	
	/* Listen the socket */
	if (listen(server->socket_server, 10) < 0)
		error("ERROR on listen() ");
	printf("-- Listen OK --\n");
}

/**
 * *************************************************
 * Handle connection for a new client
 * 
 * @param Server *server : pointer struct of server
 * *************************************************
 */ 
void new_client(Server *server)
{
	unsigned int id = server->count_clients;
	
	if ((server->sockets_client[id] = accept(server->socket_server, (struct sockaddr *) &server->addr_client, (socklen_t *) &server->lg_addr_client)) < 0)
		error("ERROR on accept() ");

	printf("\t* Socket %d --> New connection (%d)\n", server->sockets_client[id], id);

	/* add the new socket to descriptors */
	FD_SET(server->sockets_client[id], &server->master_fds);

	server->count_clients++;

	/* realloc sockets_client */
	server->sockets_client = realloc(server->sockets_client, (server->count_clients + 1) * sizeof(int));
}

/**
 * *************************************************
 * Handle actions from a connected client
 * 
 * @param int socket : the socket used by client
 * @param Server *server : pointer struct of server
 * *************************************************
 */
void connected_client(int socket, Server *server) {
	char buffer[BUFFER_SIZE], message[BUFFER_SIZE]; // buffer used for messages
	int ret; // get the return value of recv()
	unsigned int i; // to loop
	
	bzero((char *) &buffer, sizeof(buffer)); // initialize buffer
	bzero((char *) &message, sizeof(message));
	
	/* Let's go ! */
	/* Error */
	if ((ret = recv(socket, buffer, sizeof(buffer), 0)) < 0)
		error("ERROR on recv() ");
	/* Disconnection of a client */
	else if (ret == 0)
	{
		printf("\t* Socket %d --> Disconnection\n", socket);
		close(socket);
		FD_CLR(socket, &server->master_fds); // clear socket from descriptors
	}
	/* We got a message from a client */
	else
	{
		/* Just tell which socket send the message */
		sprintf(message, "Socket %d : ", socket);
		strcat(message, buffer);
		
		for (i = 0; i < FD_SETSIZE; i++) // loop all descriptors
			if (FD_ISSET(i, &server->master_fds) && i != server->socket_server && i != socket) // send to all except sender and server
				if (send(i, message, ret + 10 + sizeof(int), 0) < 0) // send error
					error("ERROR on send() ");
	}
}