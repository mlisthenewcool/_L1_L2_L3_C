#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#include "liste.c"
#include "binary_tree.c"
#include "arbre_binaire.c"

#define MAX_VALUE 100

int main (int argc, char **argv)
{
	int N;
	
	if (argc == 2)
		N = atoi(argv[1]);
	
	else
	{
		printf("\nUsage invalide !\n\t%s taille_tableau\n\n", argv[0]);
		exit(1);
	}
	
	srand(1);
	int i, *tableau = malloc(N * sizeof(int)), nb_elements = (N/2) + rand() % (N/3);
	
	for (i = 0; i < N; i++)
		tableau[i] = rand() % MAX_VALUE;
	
	float temps;
	clock_t t1, t2;
	
	/**
	 * Tests
	 */
	
	/* Liste */
	printf("--------------------------------------------\n");
	printf("LISTE\n");
	printf("--------------------------------------------\n");
	
	// initialisation
	list_t *list = malloc(sizeof(list_t));
	list->value = 0;
	list->next = NULL;
	
	// ajout
	t1 = clock();
	for(i = 0; i < nb_elements; i++)
		list = list_add(list, tableau[i]);
	t2 = clock();
	temps = (float)(t2-t1) / CLOCKS_PER_SEC;
	printf("Temps AJOUT : %f secondes\n", temps);
	
	// recherche
	t1 = clock();
	for(i = 0; i < nb_elements; i++)
		list_search(list, tableau[i]);
	t2 = clock();
	temps = (float)(t2-t1) / CLOCKS_PER_SEC;
	printf("Temps RECHERCHE : %f secondes\n", temps);
	
	if (N < 21)
		list_display(list);
	
	// delete
	t1 = clock();
	for(i = 0; i < nb_elements; i++)
		list = list_delete(list, tableau[i]);
	t2 = clock();
	temps = (float)(t2-t1) / CLOCKS_PER_SEC;
	printf("Temps SUPPRIMER : %f secondes\n", temps);
	
	/* Arbre binaire */
	printf("--------------------------------------------\n");
	printf("ARBRE BINAIRE\n");
	printf("--------------------------------------------\n");
	
	// initialisation
	node_t *tree = NULL;
	// arbre_binaire_t *arbre = malloc(sizeof(arbre_binaire_t));
	
	// ajout
	t1 = clock();
		for(i = 0; i < nb_elements; i++) {
			// arbre = ajouter(arbre, tableau[i]);
			tree = insert_bis(tree, tableau[i]);
		}
	t2 = clock();
	temps = (float)(t2-t1) / CLOCKS_PER_SEC;
	printf("Temps AJOUT : %f secondes\n", temps);
	
	// recherche
	t1 = clock();
	//for(i = 0; i < nb_elements; i++)
	
	if (N < 21) {
		// afficher(arbre);
		display(tree);
	}

	t2 = clock();
	temps = (float)(t2-t1) / CLOCKS_PER_SEC;
	printf("Temps RECHERCHE : %f secondes\n", temps);
	printf("\tTODO\n");
	
	// delete
	t1 = clock();
	//for(i = 0; i < nb_elements; i++)

	t2 = clock();
	temps = (float)(t2-t1) / CLOCKS_PER_SEC;
	printf("Temps SUPPRIMER : %f secondes\n", temps);
	printf("\tTODO\n");
	
	return 0;
}

