#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	printf("\nDémarrage du main\n\n");
	printf("Je suis le terminal (%d)\n\n", getppid());
	
	int pid_1 = fork();
	
	// erreur lors du fork (premier fils)
	if (pid_1 < 0) {
		perror("La création du premier fils a échoué\n\n");
		exit(EXIT_FAILURE);
	}
	
	// code deuxième rond
	else if (pid_1 > 0) {
		printf("Je suis le deuxième rond (%d) -- (pid du terminal : %d)\n\n", getpid(), getppid());
		
		int pid_2 = fork();
		
		// erreur lors du fork troisième rond gauche
		if (pid_2 < 0) {
			perror("La création du troisième rond à gauche a échoué\n\n");
			exit(EXIT_FAILURE);
		}
		
		// code père
		else if (pid_2 > 0)
			printf("Papa a le pid --> %d (pid du père : %d)\n\n", getpid(), getppid());
		
		else
			printf("Je suis le troisième rond à gauche (%d)\n\n", getpid());
	}
	
	// code fils
	else
		printf("Je suis le premier fils (%d)\n\n", getpid());
}