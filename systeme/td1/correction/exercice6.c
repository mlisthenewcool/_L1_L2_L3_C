#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
	//Taille de la matrice (toujours positif -> unsigned); unsigned char -> [0..255]
	unsigned char nbLignes = 10;
	unsigned char tailleLigne = 20;
	unsigned char nbLignesAllouees = 0;

	//Allocation de la matrice
	printf("-- Allocation de la matrice\n");
	int** matrice = malloc(nbLignes * sizeof(int*));
	
	//Verification de l'allocation
	if(matrice != NULL) {
		printf("\tAllocation de la matrice OK\n");
		//Allocation reussie
		srand(time(NULL)); //Initialisation du generateur de nombre pseudo-aletaoires
		
		//Allocation des lignes de la matrice
		unsigned char position;
		printf("-- Allocation des lignes\n");
		for(position = 0; position < nbLignes; position++) {
			printf("\tAllocation de la ligne %d/%d\n", position, nbLignes);
			matrice[position] = malloc(tailleLigne * sizeof(int));
			//Verification
			if(matrice[position] == NULL) {
				printf("\tErreur lors de l'allocation de la ligne %d\n", position);
				break; //On sort de la boucle pour proceder a la desallocation
			} else {
				nbLignesAllouees++;
			}
		}

		if(nbLignesAllouees == nbLignes) {
			printf("\tLes lignes ont ete allouees avec succes !\n");
			//Nous avons reussi a tout alloue -> il n'y a pas eu d'erreur
			//Remplissage de la matrice avec des valeurs aleatoires			
			unsigned char positionLigne;
			unsigned char positionColonne;
			srand(time(NULL));
			for(positionLigne = 0; positionLigne < nbLignes; positionLigne++) {
				for(positionColonne = 0; positionColonne < tailleLigne; positionColonne++) {
					matrice[positionLigne][positionColonne] = rand() % 10;
				}
			}

			//Affichage de la matrice
			printf("-- Affichage de la matrice :\n");
			for(positionLigne = 0; positionLigne < nbLignes; positionLigne++) {
				for(positionColonne = 0; positionColonne < tailleLigne; positionColonne++) {
					printf("%d ",matrice[positionLigne][positionColonne]);
				}
				printf("\n");
			}
		}

		//Desallocation des lignes
		printf("-- Desallocation des lignes\n");
		unsigned char ligneDesallouee;
		for(ligneDesallouee = 0; ligneDesallouee < nbLignesAllouees; ligneDesallouee++) {
			printf("\tDesallocation de la ligne %d/%d\n", ligneDesallouee, nbLignesAllouees);
			free(matrice[ligneDesallouee]);
			matrice[ligneDesallouee] = NULL;
		}
		printf("\tLignes desallouees !\n");

		//Desallocation des lignes
		printf("-- Desalocation de la matrice\n");
		free(matrice);
		matrice = NULL;
		printf("\tMatrice desallouee !\n");
		return nbLignes - nbLignesAllouees; //nbLignes - nbLignesAllouees = 0 si tout c'est bien deroule !
	} else {
		//Erreur lors de l'allocation de la matrice -> desallocation de la matrice
		printf("Erreur d'allocation de la matrice !\n");
		free(matrice);
		matrice = NULL;
		return 1;
	}
}
