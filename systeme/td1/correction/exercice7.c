#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char* argv[]) {
	//Taille du tableau (toujours positif -> unsigned); unsigned char -> [0..255]
	unsigned char tailleTableau = 3;

	//Allocation d'un tableau de <tailleTableau> 'cases' du type entier 
	char** tableau = malloc(tailleTableau * sizeof(char*));
	
	//Verification de l'allocation
	if(tableau != NULL) {
		//Allocation reussie
		srand(time(NULL)); //Initialisation du generateur de nombre pseudo-aletaoires
		
		//Remplissage du tableau avec les valeurs saisies par l'utilisateur au clavier
		unsigned char position;
		for(position = 0; position < tailleTableau; position++) {
			tableau[position] = malloc(100 * sizeof(char));
			printf("Merci de saisir la chaine de caractere a stocker a la position %d (/%d) du tableau\n", position + 1, tailleTableau);
			scanf("%100s", tableau[position]); //Limitation du nombre de caractere a lire ! -> si le nombre de caractere n'est pas limite, il y a un risque de buffer overflow !
		}
		
		//Affichage du tableau
		for(position = 0; position < tailleTableau; position++) {
			printf("Tableau[%d] = %s\n", position, tableau[position]);
		}
		
		//Liberation de la memoire occupee par le tableau
		for(position = 0; position < tailleTableau; position++) {
			free(tableau[position]);
			tableau[position] = NULL;
		}
		free(tableau);
		tableau = NULL;
			
		return 0;		
	} else {
		//Un probleme est survenu lors de l'allocation du tableau
		printf("Le tableau n'a pas pu etre aloue !\n");
		return 1;
	}	
}
