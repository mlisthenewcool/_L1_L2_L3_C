#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

typedef struct {
	int x;
	int y;
	int z;
} coordonnees;

typedef struct {
	int nbCoordonnees;
	coordonnees* pCoordonnees;
} tousLesEntiers;

void initialise(tousLesEntiers* pTousLesEntiers) {
	//Initialisation du tableau de pointeurs sur des strucutures du type "coordonnees"
	pTousLesEntiers->pCoordonnees = malloc(pTousLesEntiers->nbCoordonnees * sizeof(coordonnees));
	if(pTousLesEntiers->pCoordonnees == NULL) {
		printf("Erreur lors de l'allocation du tableau de pointeurs sur des structures du type \"Coordonnees\"\n");
		exit(1);//Arret du programme avec un code de reoutr != 0 -> indique une erreur
	}
	
	//Initialisation des structures
	int position;
	for(position = 0; position < pTousLesEntiers->nbCoordonnees; position++) {
		pTousLesEntiers->pCoordonnees[position].x = 10;
		pTousLesEntiers->pCoordonnees[position].y = 5;
		pTousLesEntiers->pCoordonnees[position].z = 2;
	}
}

void detruit(tousLesEntiers* pTousLesEntiers) {
	free(pTousLesEntiers->pCoordonnees);
}

void affichage(tousLesEntiers* pTousLesEntiers) {
	int position;
	printf("Tous les entiers : [\n");
	for(position = 0; position < pTousLesEntiers->nbCoordonnees; position++) {
		printf(
			"\tCoordonnees [x = %d, y = %d, z = %d]\n",
			((pTousLesEntiers->pCoordonnees) + position)->x,
			(*pTousLesEntiers).pCoordonnees[position].y,
			(*((pTousLesEntiers->pCoordonnees) + position)).z
		);
	}
	printf("]\n");
}

void multiplication(tousLesEntiers* pTousLesEntiers) {
	int position;
	for(position = 0; position < pTousLesEntiers->nbCoordonnees; position++) {
		pTousLesEntiers->pCoordonnees[position].z = pTousLesEntiers->pCoordonnees[position].x * pTousLesEntiers->pCoordonnees[position].y;
	}
}

void addition(tousLesEntiers* pTousLesEntiers) {
	int position;
	for(position = 0; position < pTousLesEntiers->nbCoordonnees; position++) {
		pTousLesEntiers->pCoordonnees[position].z = pTousLesEntiers->pCoordonnees[position].x + pTousLesEntiers->pCoordonnees[position].y;
	}
}

int main(int argc, char* argv[]) {
	tousLesEntiers tls;
	tls.nbCoordonnees = 3;

	initialise(&tls);
	
	affichage(&tls);
	multiplication(&tls);
	affichage(&tls);
	addition(&tls);
	affichage(&tls);

	detruit(&tls);

	return 0;
}
