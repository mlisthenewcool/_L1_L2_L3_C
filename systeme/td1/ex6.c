 #include <stdio.h>
 #include <stdlib.h>
 
int main (int argc, char *argv[]) {

	 // Taille initiale de la matrice
	 int lignes = 10;
	 int colonnes = 10;
	 
	 // Pour que rand() s'initialise à chaque exécution
	 srand((unsigned int)time(NULL));
	 
	 int** matrice = NULL;
	 int x = 1;
	 int i, j;
	 
	 matrice = (int**) malloc(lignes* sizeof(int*));
	 
	 if(matrice != NULL) {
		 matrice[0] = (int*) malloc(lignes* colonnes* sizeof(int));
		 
		 if(matrice[0] != NULL) {
			 for(x; x < lignes; i++) {
				 matrice[x] = matrice[0] + x * colonnes;
			 }
			 printf ("La matrice a été créée\n");
		 }
			 else {
				 free(matrice);
				 matrice = NULL;
			 }
	 }
	 else {
		 free(matrice);
		 printf ("La matrice n'a pas pu être créée\n");
	 }
	 
	 for (i = 0; i < lignes; i++) {
		 for (j = 0; j < colonnes; j++) {
			 *matrice[j] = rand() % 100 + 1;
			 
			 if (*matrice[j] < 10)
				 printf ("  %d  ", *matrice[j]);
			 
			 else if (*matrice[j] < 100)
				 printf (" %d  ", *matrice[j]);
			 
			 else
				 printf ("%d  ", *matrice[j]);
		 }
		 printf ("\n");
	 }
	 
	 /*
	 int* matrice = malloc (lignes* colonnes* sizeof(int));
	 
	 if (matrice == NULL)
		 printf ("La matrice n'a pas pu être créée\n");
	 else
		 printf ("La matrice a été créée\n");
	 
	 // Choix de la taille du tableau par l'utilisateur
	 printf ("Taille de la matrice\n");
	 
	 printf ("Lignes : ");
	 scanf("%d", &lignes);
	 
	 printf ("Colonnes : ");
	 scanf ("%d", &colonnes);
	 
	 /*
	 int *matrice_tmp = realloc (matrice, lignes, colonnes);
	 if (matrice_tmp == NULL) {
		 printf ("La matrice n'a pas pu être redimensionnée\n");
		 free(matrice_tmp);
	 }
	 else {
		 printf ("La matrice a été redimensionnée\n");
		 matrice = matrice_tmp;
	 }
	 
	 // Valeurs aléatoires pour la matrice
	 int i;
	 int j;
	 
	 for (i = 0; i < lignes; i++) {
		 for (j = 0; j < colonnes; j++) {
			 matrice[j] = rand() % 100 + 1;
			 
			 if (matrice[j] < 10)
			 	printf ("  %d  ", matrice[j]);
			 
			 else if (matrice[j] < 100)
				 printf (" %d  ", matrice[j]);
			 
			 else
				 printf ("%d  ", matrice[j]);
		 }
		 printf ("\n");
	 }
	 
	 free(matrice);
	 matrice = NULL;
	 */
 }