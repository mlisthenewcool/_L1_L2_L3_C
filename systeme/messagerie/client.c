/**
 * ******************************************************************
 * Custom C client to chat with other connected people
 * A simple ./telnet <ip> <port> while server is on will do the same
 * without pagination and signals
 * 
 * @author MagicBanana
 * *****************************************************************
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h> // INADDR_ANY
#include <signal.h> // sig_atomic_t
#include <unistd.h> // _exit(), close(), getpid(), getppid(), fork()
#include <arpa/inet.h> // innet_addr()

#define SIGNAL_DISPLAY_PAUSE 2
#define SIGNAL_DISPLAY_AGAIN 20
#define SIGNAL_SHOW_OLD_MESSAGES 21
#define SIGNAL_QUIT 3

#define MAX_TEMP_MESSAGES 100

#include "helpers.h"
#include "client.h"

int main(int argc, char **argv)
{
	/* Binary usage */
	if (argc != 3)
	{
		printf("\nINVALID USAGE !\n--> %s <ip> <port>\n\n", argv[0]);
		exit(1);
	}

	printf("\n**********************************************************************\nConnection to server...\n\n");

	connection(argv[1], argv[2], (socketfd = create_socket())); // see client.h

	printf("-- PID --\n");
	printf("\t* Terminal : %d\n", getppid());
	printf("\t* Process : %d\n", getpid());

	pid_t pid;
	/* Fork to receive and send messages at same time */
	/* 1. Error */
	if ((pid = fork()) < 0)
		error("ERROR on fork() ");
	/* 2. Child => Receive */
	else if (pid == 0)
	{
		signal(SIGNAL_DISPLAY_PAUSE, display_pause);
		signal(SIGNAL_DISPLAY_AGAIN, display_again);
		signal(SIGNAL_SHOW_OLD_MESSAGES, show_old_messages);
		signal(SIGNAL_QUIT, quit);
		
		receive_msg(socketfd); // see client.h
	}
	/* 3. Parent => Send */
	else
	{
		signal(SIGNAL_DISPLAY_PAUSE, nothing);
		signal(SIGNAL_DISPLAY_AGAIN, nothing);
		signal(SIGNAL_SHOW_OLD_MESSAGES, nothing);
		signal(SIGNAL_QUIT, quit);

		send_msg(socketfd, pid); // see client.h
	}
	
	// Normally we won't be there but...
	return 0;
}