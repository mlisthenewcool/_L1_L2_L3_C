#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

//Definition de la structure "coordonnees"
typedef struct {
	int x;
	int y;
	int z;
} coordonnees;

//Fonction qui iniatialise la structure du type "coordonnees"
//Entree :
//	- un pointeur sur une structure du type "coordonnees"
void initialise(coordonnees* pCoordonnees) {
	pCoordonnees->x = 10;
	pCoordonnees->y = 5;
	pCoordonnees->z = 2;
}

//Affiche le contenu de la structure du type "coordonnees"
//Entree :
//	- un pointeur sur une structure du type "coordonnees"
void affichage(coordonnees* pCoordonnees) {
	printf("Coordonnees [x = %d, y = %d, z = %d]\n", pCoordonnees->x, pCoordonnees->y, pCoordonnees->z);
}

//Stocke le produit du membre x et du membre y dans le membre z de la structure du type "coordonnees"
//Entree :
//	- un pointeur sur une structure du type "coordonnees"
void multiplication(coordonnees* pCoordonnees) {
	printf("--- MULTIPLICATION ---\n");
	pCoordonnees->z = pCoordonnees->x * pCoordonnees->y;
	//Ici, on dispose deja d'un poiteur sur une structure du type coordonnees : il n'y a pas besoin d'obtenir l'adresse de la variable avec l'operateur '&'
	affichage(pCoordonnees);
}

//Stocke la somme du membre x et du membre y dans le membre z de la structure du type "coordonnees"
//Entree :
//	- un pointeur sur une structure du type "coordonnees"
void addition(coordonnees* pCoordonnees) {
	printf("--- ADDITION ---\n");
	pCoordonnees->z = pCoordonnees->x + pCoordonnees->y;
	//Ici, on dispose deja d'un pointeur sur une structure du type coordonnees : il n'y a pas besoin d'obtenir l'adresse de la variable avec l'operateur '&'
	affichage(pCoordonnees);
}

int main(int argc, char* argv[]) {
	//Creation d'une variable de type coordonnees nommee "coords"
	coordonnees coords;

	//Initialisation des membre x, y, et z de la variable cords de type "coordonnees" (attetnion au passage par reference !)
	initialise(&coords);
	
	//Realisation des traitements (attention au passage par reference !)
	multiplication(&coords);
	addition(&coords);

	return 0;
}
