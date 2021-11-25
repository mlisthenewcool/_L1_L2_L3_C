#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define MAX_PROCCESS 10

void afficher(int signal)
{
	printf("Signal %d reçu\n", signal);
}

int main(int argc, char **arv)
{
	unsigned int i;
	int pid[MAX_PROCCESS];
	
	for (i = 0; i < MAX_PROCCESS; i++)
	{
		if ((pid[i] = fork()) < 0)																				// error
		{
			perror("ERROR during main() on fork() ");
			exit(1);
		}
		else if (pid[i] == 0)																						// child
		{
			while(1)
			{
				//signal(2, afficher);
				printf("Je suis le fils %d, PID : %d\n", i, getpid());
				sleep(5);
			}
			exit(1);
		}
	}
	
	sleep(5);
	
	for (i = 0; i < MAX_PROCCESS; i++)
	{
		//kill(pid[i], 2);
		kill(pid[i], 9);
	}
	
	wait();
	exit(0);
}