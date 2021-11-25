#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
	unsigned short int i;
	int pid, statut;
	
	printf("\n-- Terminal --> pid : %d\n-- Main --> pid : %d\n", getppid(), getpid());
	
	if (argc < 2)
		printf("\tVous n'avez précisé aucun programme à exécuter\n");
	
	else {
		// création des fils
		for (i = 0; i < argc - 1; i++) {
			pid = fork();
		
			// erreur lors du fork
			if (pid < 0) {
				printf("La création du fils %d a échoué\n", i);
				exit(EXIT_FAILURE);
			}
		
			// code fils
			else if (pid == 0) {
				printf("-- Bonjour, fils n°%d --> pid : %d / pid du père : %d\n", i+1, getpid(), getppid());
			
				char nom_programme[100] = "";
				strcat(nom_programme, "./");
				strcat(nom_programme, argv[i+1]);
			
				execve(nom_programme, NULL, NULL);
				perror("\tEchec lors du lancement du programme ");
				exit(EXIT_SUCCESS);
			}
		
			// code père
			else {
				waitpid(pid, &statut, 0);
				printf("-- Adieu, fils n°%d\n", i+1);
			}
		}
	}
	
	printf("-- Fin du main\n");
	exit(EXIT_SUCCESS);
}