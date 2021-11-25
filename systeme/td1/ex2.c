#include <stdio.h>

typedef struct {
	int x;
	int y;
	int z;
}coordonnees;

void initialise (coordonnees *la) {
	la->x = 10;
	la->y = 5;
	la->z = 2;
}

void plus (coordonnees *la) {
	la->z = la->x + la->y;
}

void moins (coordonnees *la) {
	la->z = la->x - la->y;
}

void fois (coordonnees *la) {
	la->z = la->x * la->y;
}

void afficher (coordonnees *la) {
	printf("Coordonnées de la structure : x = %d, y = %d, z = %d\n", la->x, la->y, la->z);
}

void afficher_cases(int **matrice, int longueur, int largeur)
{
	int i, j;
	
	for (i = 0; i < longueur; i++)
	{
		for (j = 0; j < largeur; j++)
		{
			printf("|%3d", matrice[i][j]);
			if (j == largeur - 1)
				printf("|\n");
		}
	}
}

int main (int argc, char *argv[]) {
	coordonnees ici;
	
	int **matrice = malloc(10 *sizeof(int*));
	int i, j;
	for (i = 0; i < 10; i++)
	{
		matrice[i] = malloc(10 * sizeof(int));
		for (j = 0; j < 10; j++)
			matrice[i][j] = rand() % 50;
	}
	
	afficher_cases(matrice, 10, 10);
	
	initialise(&ici);
	afficher (&ici);
	plus(&ici);
	afficher(&ici);
}