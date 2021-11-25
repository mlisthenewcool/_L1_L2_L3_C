#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define MAX_CHILD 2

pid_t pid[MAX_CHILD];

void ping(int signal)
{
	printf("PING\n");
	kill(pid[1], 4);
}

void pong(int signal)
{
	printf("PONG\n");
	kill(pid[0], 3);
}

int main(int argc, char **arv)
{
	unsigned int i;
	int fds[2];
	pid_t pid_frere;
	
	pipe(fds);
	
	for (i = 0; i < MAX_CHILD; i++)
	{
		if ((pid[i] = fork()) < 0)
		{
			perror("ERROR during main() on fork()\n");
			exit(1);
		}
		else if (pid[i] == 0)
		{
			printf("PID fils n°%d : %d\n", i, getpid());
			
			if (i == 0)
			{
				close(fds[1]);
				
				read(fds[0], &pid[1], sizeof(pid_t));
				printf("1er fils, pid du 2eme : %d\n", pid[1]);
				
				signal(3, ping);
			}
			else
			{
				close(fds[0]);
				
				pid_frere = getpid();
				write(fds[1], &pid_frere, sizeof(pid_t));
				printf("2eme fils, pid du 1er : %d\n", pid[0]);
				
				signal(4, pong);
			}
			
			while(1)
			{
				pause();
			}
			
			exit(1);
		}
	}

	sleep(1);
	
	printf("Le père lance la partie !\n");
	kill(pid[0], 3);
	
	/* On arrête la partie après 10 secondes */
	sleep(10);
	kill(pid[0], 9);
	kill(pid[1], 9);
	printf("Partie stoppée !\n");
	exit(0);
}