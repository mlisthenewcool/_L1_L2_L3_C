#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define MAX_PROCCESS 2
#define BUFFER_SIZE 255

int pid[MAX_PROCCESS];

void fils_1()
{
	char buffer[BUFFER_SIZE];
	
	printf("Bonjour, entrez votre message :\n");
	scanf("%s", buffer);
	printf("Message saisi : %s\n", buffer);
}

void fils_2()
{
	char buffer[BUFFER_SIZE];
	
	printf("Bonjour, entrez votre message :\n");
	scanf("%s", buffer);
	printf("Message saisi : %s\n", buffer);
}

int main(int argc, char **arv)
{
	unsigned int i;
	int statut;
	
	for (i = 0; i < MAX_PROCCESS; i++)
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
				signal(2, fils_1);
			else if (i == 1)
				signal(3, fils_2);
			
			exit(1);
		}
	}
	
	while(1)
	{
		signal(2, fils_1);
		signal(3, fils_2);
		pause();
	}
	//sleep(1);
	//printf("Saisir le PID du 2ème fils : ");
	//scanf("%d", &pid[1]);
	
	for (i = 0; i < MAX_PROCCESS; i++)
		waitpid(pid[i], &statut, 0);

	exit(0);
}