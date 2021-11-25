#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void afficher(int signal)
{
	printf("Signal %d reçu\n", signal);
}

int main(int argc, char **arv)
{
	unsigned int i;
	
	for (i = 0; i < NSIG; i++)
		if (signal(i, afficher) == SIG_ERR)
			printf("Impossible de modifier le signal %d\n", i);
		
	while(1)
	{
		pause();
	}
	
	exit(0);
}