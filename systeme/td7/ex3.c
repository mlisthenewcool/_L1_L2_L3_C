#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	printf("\nDémarrage du main\n\n");
	printf("Je suis le terminal (%d)\n\n", getppid());
	printf("Je suis le main (%d)\n\n", getpid());
	
	int pid_1, pid_2;
	
	// création du premier fils
	pid_1 = fork();
	
	// erreur lors du fork (premier fils)
	if (pid_1 < 0) {
		perror("La création du premier fils a échoué\n\n");
		exit(EXIT_FAILURE);
	}
	
	// code premier fils
	else if (pid_1 == 0) {
		while (1) {
			sleep(1);
			printf("Je suis le premier fils (%d) -- (pid du père : %d)\n\n", getpid(), getppid());
		}
	}
		
	// code père (terminal)
	else {
		pid_2 = fork();
		
		// erreur lors du fork (deuxième fils)
		if (pid_2 < 0) {
			perror("La création du deuxième fils a échoué\n\n");
			exit(EXIT_FAILURE);
		}
		
		// code deuxième fils
		else if (pid_2 == 0) {
			while (1) {
				sleep(1);
				printf("Je suis le deuxième fils (%d) -- (pid du père : %d)\n\n", getpid(), getppid());
			}
		}
		
		else {
			int statut;
			waitpid(pid_1, &statut, 0);
			waitpid(pid_2, &statut, 0);
			printf("Tous les fils sont morts\n");
		}
	}
}