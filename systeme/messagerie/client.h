/**
 * *****************************
 * Functions used in <client.c>
 * 
 * @author MagicBanana
 * *****************************
 */

volatile sig_atomic_t pause_bool; // flag to handle pause's signal
int socketfd; // the socket's id we'll use

char messages[MAX_TEMP_MESSAGES][BUFFER_SIZE]; // messages temp for interruption
unsigned int count_messages, i = 1; // count messages temp || to loop

/**
 * ******************************************************************************************
 * Signals functions
 * 
 * @see link
 * http://stackoverflow.com/questions/16891019/how-to-avoid-using-printf-in-a-signal-handler
 * ******************************************************************************************
 */
void display_pause(int signal)
{
	pause_bool = 1;
}

void display_again(int signal)
{
	pause_bool = 0;
	kill(getpid(), SIGNAL_SHOW_OLD_MESSAGES);
}

void show_old_messages(int signal)
{
	if (pause_bool == 0 && count_messages > 1)
	{
		printf("-- Messages received during interruption --\n");
		for (i = 1; i < count_messages; i++)
			printf("\t%s\n", messages[i]);
	}
		
	count_messages = 1;
}

void quit(int signal)
{
	close(socketfd);
	_exit(0);
}

void nothing(int signal){}

/**
 * **************************************
 * Create a TCP socket
 * 
 * @return int : the created socket's id
 * **************************************
 */
int create_socket()
{
	/* Let's go ! */
	if ((socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		error("ERROR on socket() ");

	printf("-- Socket OK --\n\t* ID : %d\n", socketfd);
	return socketfd;
}

/**
 * ********************************************************************
 * Initialize connection to the ip address and port provided by socket
 * 
 * @param char *ip
 * @param char *port
 * @param int socket
 * ********************************************************************
 */ 
void connection(char *ip, char *port, int socket)
{
	struct sockaddr_in coord_server; // server
	u_short id_port = atoi(port); // port

	/* Initialize connection structure */
	bzero((char *) &coord_server, sizeof(coord_server));
	coord_server.sin_family = AF_INET;
	coord_server.sin_addr.s_addr = inet_addr(ip);
	coord_server.sin_port = htons(id_port);

	/* Let's go ! */
	if(connect(socket, (struct sockaddr *) &coord_server, sizeof(coord_server)) < 0)
		error("ERROR on connect() ");

	printf("-- Connection OK --\n\t* IP address : %s\n\t* Port : %d\n", ip, id_port);
}

/**
 * ********************************************
 * Send a message submitted by a client
 * => Parent process
 * 
 * @param int socket : destination socket's id
 * @param pid_t pid : pid of our child
 * ********************************************
 */ 
void send_msg(int socket, pid_t pid)
{
	printf("\t* Send message : %d\n", getpid());
	
	char buffer[BUFFER_SIZE];
	
	while(1)
	{
		bzero(buffer, BUFFER_SIZE); // initialize buffer
		fgets(buffer, BUFFER_SIZE, stdin); // get input from terminal

		/* Message isn't empty */
		if (buffer[0] != '\n' && buffer[1] != '\0')
		{
			// TODO test si la saisie dépasse la taille du buffer
			/* Let's go ! */
			/* 1. Error */
			if (send(socket, buffer, strlen(buffer), 0) < 0)
				error("ERROR on send() ");
			/* 2. Here we have send the message so we need to tell to our child that we can receive again */
			else
				kill(pid, SIGNAL_DISPLAY_AGAIN);
		}
	}
}

/**
 * *******************************************
 * Receive a message from server
 * => Child proccess
 * 
 * @param int socket : connection socket's id
 * *******************************************
 */
void receive_msg(int socket)
{
	printf("\t* Receive message : %d\n", getpid());
	printf("**********************************************************************\n");
	printf("-- Options --\n");
	printf("\t* Press CTRL + C to interrupt display of messages\n");
	printf("\t* Press CTRL + Z to display messages again (send a message does same)\n");
	printf("\t* Press CTRL + \\ to quit\n");
	printf("**********************************************************************\n");

	char buffer[BUFFER_SIZE];
	int ret;
	
	/* Initial malloc to get one message */
	//messages = malloc(sizeof(char *));
	//messages[0] = malloc(sizeof(BUFFER_SIZE * sizeof(char)));
	
	while(1)
	{
		bzero(buffer, BUFFER_SIZE); // initialize
		
		/* Let's go ! */
		/* 1. Error */
		if ((ret = recv(socket, buffer, BUFFER_SIZE, 0)) < 0)
			error("ERROR on recv() ");
		/* 2. Server is off */
		else if (ret == 0)
		{
			printf("Server is off !\n");
			kill(getppid(), SIGNAL_QUIT);
			kill(getpid(), SIGNAL_QUIT);
		}
		/* 3. Success */
		else
		{
			/* 3.1. There is no pause so just printf what we received */
			if (pause_bool == 0)
			{
				printf("-- %s\n", buffer);
				count_messages = 1;
				/*
				if ((temp = realloc(messages, count_messages * sizeof(char[BUFFER_SIZE]))) == NULL)
				{
					kill(getppid(), SIGNAL_QUIT);
					perror("ERROR on realloc() ");
					kill(getpid(), SIGNAL_QUIT);
				}
				else
					messages = temp;
				*/
			}
			/* 3.2. We are in pause, save messages to display them later */
			else
			{
				strcpy(messages[count_messages], buffer);
				count_messages++;
				/*
				if ((temp = realloc(messages, count_messages * sizeof(char *))) == NULL)
				{
					kill(getppid(), SIGNAL_QUIT);
					perror("ERROR on realloc() ");
					kill(getpid(), SIGNAL_QUIT);
				}
				else
					messages = temp;
				*/
			}
		}
	}
}