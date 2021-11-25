#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	printf("Démarrage du main, pid : %d\n", getpid());
	
	int pid_1 = fork();
	
	// erreur lors du fork (premier fils)
	if (pid_1 < 0) {
		perror("La création du premier fils a échoué\n");
		exit(EXIT_FAILURE);
	}
	
	// code père
	else if (pid_1 > 0) {
		printf("Papa (%d) vient de créer un premier enfant\n", getpid());
		
		int pid_2 = fork();
		
		// erreur lors du fork (deuxième fils)
		if (pid_2 < 0) {
			perror("La création du deuxième fils a échoué\n");
			exit(EXIT_FAILURE);
		}
		
		// code père
		else if (pid_2 > 0)
			printf("Papa (%d) vient de créer un deuxième enfant\n", getpid());
		
		else
			printf("Je suis le deuxième fils (%d)\n", getpid());
	}
	
	// code fils
	else
		printf("Je suis le premier fils (%d)\n", getpid());
}