#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	
	int size = 20;
	srand((unsigned int)time(NULL));
	
	int *pointeur = malloc(size * sizeof(int));
	if (pointeur == NULL)
		printf ("L'allocation n'a pu être réalisée\n");
	else {
		printf ("L'allocation a été un succès\n");
	}
	
	int i;
	for (i = 0; i < size ; i++) {
		pointeur[i] = rand() % 100 + 1;
		printf ("%d\n", pointeur[i]);
	}
	
	free(pointeur);
	pointeur = NULL;
}