#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define COUNT_PROCESS 10

int main(int argc, char **arv)
{
	int fds[COUNT_PROCESS][2], statut;
	pid_t pid[COUNT_PROCESS];
	char msg[30];
	unsigned char i, j;
	
	/* Pipe pour tous les processus */
	for (i = 0; i < COUNT_PROCESS; i++)
	{
		if (pipe(fds[i]) < 0)
		{
			perror("ERROR on pipe() ");
			exit(1);
		}
	}
	
	printf("Veuillez saisir le message à envoyer à tous les clients : ");
	scanf("%s", msg);

	/* Fork() pour tous les processus */
	for (i = 0; i < COUNT_PROCESS; i++)
	{
		/* 1. Erreur */
		if ((pid[i] = fork()) < 0)
		{
			perror("ERROR on fork()\n");
			exit(1);
		}
		/* 2. Child */
		else if (pid[i] == 0)
		{
			/* Ferme tous les tubes d'écriture */
			for (j = 0; j < COUNT_PROCESS; j++)
			{
				close(fds[j][1]);
				/* Ferme tous les tubes de lecture autres que le sien */
				if (i != j)
					close(fds[j][0]);
			}
			
			read(fds[i][0], &msg, sizeof(msg));
			close(fds[i][0]);
			printf("Fils %d (PID : %d) --> %s\n", i, getpid(), msg);
			
			exit(0);
		}
		/* 3. Parent */
		else
		{
			/* Ferme tous les tubes de lecture */
			for (j = 0; j < COUNT_PROCESS; j++)
			{
				close(fds[j][0]);
				/* Ferme tous les tubes d'écriture autres que le sien */
				if (i != j)
					close(fds[j][1]);
			}
			
			for (j = 0; j < COUNT_PROCESS; j++)
			{
				write(fds[j][1], &msg, sizeof(msg));
				close(fds[j][1]);
			}
		}
	}
	
	for (i = 0; i < COUNT_PROCESS; i++)
	{
		waitpid(pid[i], &statut, 0);
		if(WIFEXITED(statut))
			printf("Fils %d terminé avec le statut %d\n", i, WEXITSTATUS(statut));
	}
	exit(0);
}