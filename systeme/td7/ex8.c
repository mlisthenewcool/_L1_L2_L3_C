#include <stdio.h>
#include <stdlib.h>

int lire_entier();

int main(int argc, char** argv) {
	unsigned short int i, y;
	int pid, valeur_saisie, somme;
	
	printf("\n-- Terminal --> pid : %d\n-- Main --> pid : %d\n", getppid(), getpid());
	
	// création des fils
	for (i = 0; i < 3; i++) {
		pid = fork();
	
		// erreur lors du fork
		if (pid < 0) {
			printf("La création du fils %d a échoué\n", i);
			exit(EXIT_FAILURE);
		}
	
		// code fils
		else if (pid == 0) {
			printf("-- Bonjour, fils n°%d --> pid : %d / pid du père : %d\n", i+1, getpid(), getppid());
			// execve("./fils_ex8", 0, 0);
			// perror("Echec lors du lancement du programme ./fils_ex8");
			printf("\tVeuillez saisir 5 valeurs : \n");
			
			if (i == 0)
				somme = 0;
			
			for (y = 0; y < 5; y++) {
				printf("\t\t(%d) + ", somme);
				valeur_saisie = lire_entier();
				somme += valeur_saisie;
				
				if (y == 4)
					printf("\tRésultat final pour le fils n°%d : %d\n", i+1, somme);
			}
			exit(EXIT_SUCCESS);
		}
	
		// code père
		else {
			int statut;
			waitpid(pid, &statut, 0);
			printf("-- Adieu, fils n°%d\n", i+1);
		}
	}
	
	exit(EXIT_SUCCESS);
}

int lire_entier() {
	char temp[1024], saisie[1024];
	int est_un_nombre = 0;
	
	while (est_un_nombre != 1) {
		// fflush (stdout);
		fgets (saisie, sizeof (saisie), stdin);
		est_un_nombre = sscanf(saisie, "%[0-9]s", temp);
		
		if (est_un_nombre != 1)
			printf("\t\tentier incorrect : ");
	}
		
	return strtol (temp, NULL, 10);
}