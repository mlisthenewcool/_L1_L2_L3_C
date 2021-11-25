#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char* argv[]) {
	//Taille du tableau (toujours positif -> unsigned); unsigned char -> [0..255]
	unsigned char tailleTableau = 10;
	//version avec int si le tableau est trop grand
	//int tailleTableau 
	
	//Allocation d'un tableau de <tailleTableau> 'cases' du type entier 
	int* tableau = malloc(tailleTableau * sizeof(int));
	
	//Verification de l'allocation
	if(tableau != NULL) {
		//Allocation reussie
		srand(time(NULL)); //Initialisation du generateur de nombre pseudo-aletaoires
		
		//Remplissage du tableau avec des valeurs aleatoires
		unsigned char position;
		for(position = 0; position < tailleTableau; position++) {
			tableau[position] = rand(); //Remplisage de la case d'index 'position' du tableau avec une valeur pseudo-aleatoire
		}
		
		//Affichage du tableau
		for(position = 0; position < tailleTableau; position++) {
			printf("Tableau[%d] = %d\n", position, tableau[position]);
		}
		
		//Liberation de la memoire occupee par le tableau
		free(tableau);
		tableau = NULL;
			
		return 0;		
	} else {
		//Un probleme est survenu lors de l'allocation du tableau
		printf("Le tableau n'a pas pu etre aloue !\n");
		return 1;
	}	
}
