#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **arv)
{
	int fds[2][2], statut;
	pid_t pid[2];
	char msg[30];
	unsigned char i;
	
	if (pipe(fds[0]) < 0 || pipe(fds[1]) < 0)
	{
		perror("ERROR on pipe() ");
		exit(1);
	}

	for (i = 0; i < 2; i++)
	{
		if ((pid[i] = fork()) < 0)
		{
			perror("ERROR on fork() ");
			exit(1);
		}
		else if (pid[i] == 0)
		{
			/* Premier fils */
			if (i == 0)
			{
				close(fds[0][0]);
				close(fds[1][1]);
				
				printf("Veuillez saisir le message à envoyer : ");
				scanf("%s", msg);
				write(fds[0][1], &msg, sizeof(msg));
				close(fds[0][1]);
				
				read(fds[1][0], &msg, sizeof(msg));
				close(fds[1][0]);
				printf("Message reçu après renvoi dans le 1er fils : %s\n", msg);
			}
			/* Second fils */
			else
			{
				close(fds[0][1]);
				close(fds[1][0]);
				
				read(fds[0][0], &msg, sizeof(msg));
				close(fds[0][0]);
				printf("Message reçu dans le 2ème fils : %s\n", msg);
				
				write(fds[1][1], &msg, sizeof(msg));
				close(fds[1][1]);
			}
			
			exit(0);
		}
	}
	
	close(fds[0][0]);
	close(fds[0][1]);
	close(fds[1][0]);
	close(fds[1][1]);
	
	for (i = 0; i < 2; i++)
	{
		waitpid(pid[i], &statut, 0);
		if(WIFEXITED(statut))
			printf("Fils %d terminé avec le statut %d\n", i, WEXITSTATUS(statut));
	}
	exit(0);
}