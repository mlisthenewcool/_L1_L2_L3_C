#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **arv)
{
	int fds[2], statut;
	pid_t pid_fils;
	char msg[30];
	
	if (pipe(fds) < 0)
	{
		perror("ERROR on pipe() ");
		exit(1);
	}

	if ((pid_fils = fork()) < 0)
	{
		perror("ERROR on fork() ");
		exit(1);
	}
	else if (pid_fils == 0)
	{
		//printf("PID fils : %d\n", getpid());
		close(fds[1]);
		read(fds[0], &msg, sizeof(msg));
		close(fds[0]);
		printf("Message reçu dans le fils : %s\n", msg);
		
		exit(0);
	}
	else
	{
		//printf("PID père : %d\n", getpid());
		close(fds[0]);
		printf("Saisir le mot à envoyer au fils : ");
		scanf("%s", msg);
		write(fds[1], &msg, sizeof(msg));
		close(fds[1]);
	}
	
	waitpid(pid_fils, &statut, 0);
	if(WIFEXITED(statut))
		printf("Fils terminé avec le statut %d\n", WEXITSTATUS(statut));
	
	exit(0);
}