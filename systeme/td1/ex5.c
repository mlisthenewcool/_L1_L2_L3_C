#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	
	int size = 20;
	srand((unsigned int)time(NULL));
	
	int *pointeur = malloc(size * sizeof(int));
	if (pointeur == NULL)
		printf ("L'allocation n'a pu être réalisée\n");
	else
		printf ("L'allocation a été un succès\n");
	
	/* Choix de la taille du tableau par l'utilisateur */
	printf ("Veuillez choisir la taille du tableau : ");
	scanf("%d", &size);
	
	int *tmp = realloc (pointeur, size);
	if (tmp == NULL) {
		printf ("La réallocation n'a pu être réalisée\n");
		free(pointeur);
	}
	else {
		printf ("La réallocation a été un succès\n");
		pointeur = tmp;
	}
	
	int i;
	for (i = 0; i < size ; i++) {
		pointeur[i] = rand() % 100 + 1;
		printf ("%d\n", pointeur[i]);
	}
	
	free(pointeur);
	pointeur = NULL;
}