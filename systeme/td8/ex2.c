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
	
	for (i = 0; i < NSIG; i++)
	{
		if (signal(i, afficher) == SIG_ERR)
		{
			perror("ERROR during main() on signal() ");
			exit(1);
		}
	}
	
	while(1)
	{
		pause();
	}
	
	exit(0);
}