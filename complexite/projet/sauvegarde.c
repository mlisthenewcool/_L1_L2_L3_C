typedef struct
{
	int id;
	int poids;
	int groupe;
} etudiant;

#include "etudiant.h"
#include "evaluation.h"
#include "groupe.h"

// ____________________________________ GLOUTON  __________________________________ //
/**
 * Initialise la structure utilisée pour trier les étudiants par poids
 * 
 * @param  etudiant* etudiants : la structure vide
 * @return int                 : la valeur de la solution initiale
 */
int initialisation_etudiants_min(etudiant *etudiants)
{
#ifdef DEBUG
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Affectations initiales des étudiants pour chaque meilleur groupe\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
#endif
	
	int i;
	for (i = 0; i < nb_etudiants; i++)
	{
		etudiants[i].id = i;
		etudiants[i].poids = etudiant_poids_incompatibilites(i);
		
		// choix meilleur groupe pour les affectations
		etudiants[i].groupe = etudiant_get_min_affectation(i);
		
#ifdef DEBUG
		printf("Etudiant %d --> Groupe %d\n", i, etudiants[i].groupe);
#endif
	}
	
	return evaluer_etudiants(etudiants);
}

int initialisation_etudiants_min2(etudiant *etudiants, int **matrice)
{
	#ifdef DEBUG
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Affectations initiales des étudiants pour chaque meilleur groupe\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	#endif
	
	int i;
	for (i = 0; i < nb_etudiants; i++)
	{
		etudiants[i].id = i;
		etudiants[i].poids = etudiant_poids_incompatibilites(i);
		
		// choix meilleur groupe pour les affectations
		etudiants[i].groupe = position_groupe(i, matrice[1][i]);
		
		#ifdef DEBUG
		printf("Etudiant %d --> Groupe %d\n", i, etudiants[i].groupe);
		#endif
	}
	
	return evaluer_etudiants(etudiants);
}

int initialisation_etudiants_min3(etudiant *etudiants, int **matrice)
{
	#ifdef DEBUG
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Affectations initiales des étudiants pour chaque meilleur groupe\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	#endif
	
	int i;
	for (i = 0; i < nb_etudiants; i++)
	{
		etudiants[i].id = i;
		etudiants[i].poids = etudiant_poids_incompatibilites(i);
		
		// choix meilleur groupe pour les affectations
		etudiants[i].groupe = position_groupe(i, matrice[2][i]);
		
		#ifdef DEBUG
		printf("Etudiant %d --> Groupe %d\n", i, etudiants[i].groupe);
		#endif
	}
	
	return evaluer_etudiants(etudiants);
}

// ____________________________________ PERMUTATION  __________________________________ //
int permute_etudiant(int id, etudiant *etudiants, int min_solution)
{
	//TODO evaluer le cout pour replacer les groupes dans le tableau trié des groupes par poids actuels
	int nouveau_cout = min_solution;
	int random = rand() % nb_groupes;
	
	while(random == etudiants[id].groupe)
		random = rand() % nb_groupes;
	
	int meilleur_groupe = random;
	int i;
	
	// matrice affectations
	nouveau_cout -= matrice_affectations[etudiants[id].groupe][etudiants[id].id];
	nouveau_cout += matrice_affectations[meilleur_groupe][etudiants[id].id];
	
	// matrice incompatibilités
	for (i = 0; i < nb_etudiants; i++)
	{
		// suppressions des incompatibilités avant permutation
		if (etudiants[i].id != etudiants[id].id && etudiants[id].groupe == etudiants[i].groupe)
			nouveau_cout -= matrice_incompatibilites[etudiants[id].id][etudiants[i].id];
		
		// ajouts des incompatibilités arpès permutation
		if (etudiants[i].id != etudiants[id].id && meilleur_groupe == etudiants[i].groupe)
			nouveau_cout += matrice_incompatibilites[etudiants[id].id][etudiants[i].id];
	}
	
	// test si meilleure solution
	if (nouveau_cout < min_solution)
	{
#ifdef DEBUG
		printf("Amélioration : étudiant %d depuis %d vers %d\n", etudiants[id].id, etudiants[id].groupe, meilleur_groupe);
#endif
		etudiants[id].groupe = meilleur_groupe;
		return nouveau_cout;
	}
	else
		return 0;
}

int permute_etudiant2(int id, int groupe, etudiant *etudiants, int min_solution)
{
	//TODO evaluer le cout pour replacer les groupes dans le tableau trié des groupes par poids actuels
	if (groupe == etudiants[id].groupe)
		return;
	
	int nouveau_cout = min_solution;
	int meilleur_groupe = groupe;
	
	// matrice affectations
	nouveau_cout -= matrice_affectations[etudiants[id].groupe][etudiants[id].id];
	nouveau_cout += matrice_affectations[meilleur_groupe][etudiants[id].id];
	
	int i;
	// matrice incompatibilités
	for (i = 0; i < nb_etudiants; i++)
	{
		// suppressions des incompatibilités avant permutation
		if (etudiants[i].id != etudiants[id].id && etudiants[id].groupe == etudiants[i].groupe)
			nouveau_cout -= matrice_incompatibilites[etudiants[id].id][etudiants[i].id];
		
		// ajouts des incompatibilités arpès permutation
		if (etudiants[i].id != etudiants[id].id && meilleur_groupe == etudiants[i].groupe)
			nouveau_cout += matrice_incompatibilites[etudiants[id].id][etudiants[i].id];
	}
	
	// test si meilleure solution
	if (nouveau_cout < min_solution)
	{
#ifdef DEBUG
		printf("Amélioration : étudiant %d depuis %d vers %d\n", etudiants[id].id, etudiants[id].groupe, meilleur_groupe);
#endif
		etudiants[id].groupe = meilleur_groupe;
		return nouveau_cout;
	}
	else
		return 0;
}

// __________________________________ ALGO ________________________________________ //
void algo(int *solution, int nb_executions)
{
	/* Malloc de la structure etudiant + initialisation + tri */
	etudiant *etudiants = malloc (nb_etudiants * sizeof(etudiant));
	int resultat = initialisation_etudiants_min(etudiants);
	qsort(etudiants, nb_etudiants, sizeof(etudiants[0]), etudiant_compare_poids);
	
#ifdef DEBUG
	etudiant_afficher_poids(etudiants);
#endif
	
	printf("* * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Algorithme 1\n");
	printf("\nResultat initial : %d\n", resultat);
	
	/* Permutations */
	int i;
	int compteur;							// le nombre de permutation par étudiant
	int res_temp;							// résultat temporaire
	int repeat = 0;						// le nombre de fois où l'algo est exécuté
	int permutations = 0;			// le nombre d'améliorations trouvées
	int permutations_temp;
	while (repeat < nb_executions)
	{
		if (permutations == permutations_temp)
			printf("Plus d'améliorations après repeat %d\n", repeat);
		permutations_temp = permutations;
		
		for (i = 0; i < nb_etudiants; i++)
		{
			compteur = 0;
			while(compteur < nb_groupes)
			{
				// permutation
				res_temp = permute_etudiant2(i, compteur, etudiants , resultat);
				// on a réussi à améliorer le résultat
				if (res_temp != 0)
				{
					permutations++;
					resultat = res_temp;
				}
				// on incrémente compteur des groupes
				compteur++;
			}
		}
		repeat++;
	}
	
	printf("Nombre d'améliorations : %d\n", permutations);
	
	/* Copie des résultats depuis la structure étudiants vers le tableau solution */
	for (i = 0; i < nb_etudiants; i++)
		solution[etudiants[i].id] = etudiants[i].groupe;
	
	free(etudiants);
}

void algo2(int *solution, int nb_executions)
{
	// Malloc de la structure etudiant
	etudiant *etudiants = malloc (nb_etudiants * sizeof(etudiant));
	
	// copie matrice
	int i, j;
	int **matrice = malloc(nb_groupes * sizeof(int*));
	for (i = 0; i < nb_groupes; i++)
	{
		matrice[i] = malloc(nb_etudiants * sizeof(int));
		for (j = 0; j < nb_etudiants; j++)
			matrice[i][j] = matrice_affectations[i][j];
	}
	
	// tri matrice
	for (i = 0; i < nb_etudiants; i++)
		tri_etudiants_to_groupe(i, matrice);
	
	// solution initiale
	int resultat = initialisation_etudiants_min2(etudiants, matrice);
	
	qsort(etudiants, nb_etudiants, sizeof(etudiants[0]), etudiant_compare_poids);
	
	printf("* * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Algorithme 2\n");
	printf("\nResultat initial : %d\n", resultat);
	
	// permutations
	int nb_essais_permutation;	// le nombre d'essais de permutation par étudiant
	int res_temp;								// résultat temporaire
	int repeat = 0;							// le nombre de fois où l'algo est exécuté
	int ameliorations = 0;
	while (repeat < nb_executions)
	{
		for (i = 0; i < nb_etudiants; i++)
		{
			nb_essais_permutation = 5;
			while(nb_essais_permutation != 0)
			{
				// permutation
				res_temp = permute_etudiant(i, etudiants , resultat);
				// on a réussi à améliorer le résultat, on passe à l'étudiant suivant
				if (res_temp != 0)
				{
					ameliorations += 1;
					nb_essais_permutation = 0;
					resultat = res_temp;
				}
				// sinon on décrémente le nombre d'essais restants
				else
					nb_essais_permutation--;
			}
		}
		repeat++;
	}
	
	printf("Nombre d'améliorations : %d\n", ameliorations);
	
	for (i = 0; i < nb_etudiants; i++)
		solution[etudiants[i].id] = etudiants[i].groupe;
	
	free(matrice);
	free(etudiants);
}

void algo3(int *solution, int nb_executions)
{
	// Malloc de la structure etudiant
	etudiant *etudiants = malloc (nb_etudiants * sizeof(etudiant));
	
	// copie matrice
	int i, j;
	int **matrice = malloc(nb_groupes * sizeof(int*));
	for (i = 0; i < nb_groupes; i++)
	{
		matrice[i] = malloc(nb_etudiants * sizeof(int));
		for (j = 0; j < nb_etudiants; j++)
			matrice[i][j] = matrice_affectations[i][j];
	}
	
	// tri matrice
	for (i = 0; i < nb_etudiants; i++)
		tri_etudiants_to_groupe(i, matrice);
	
	// solution initiale
	int resultat = initialisation_etudiants_min3(etudiants, matrice);
	
	qsort(etudiants, nb_etudiants, sizeof(etudiants[0]), etudiant_compare_poids);
	
	printf("* * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Algorithme 3\n");
	printf("\nResultat initial : %d\n", resultat);
	
	// permutations
	int nb_essais_permutation;	// le nombre d'essais de permutation par étudiant
	int res_temp;								// résultat temporaire
	int repeat = 0;							// le nombre de fois où l'algo est exécuté
	int ameliorations = 0;
	while (repeat < nb_executions)
	{
		for (i = 0; i < nb_etudiants; i++)
		{
			nb_essais_permutation = 10;
			while(nb_essais_permutation != 0)
			{
				// permutation
				res_temp = permute_etudiant(i, etudiants , resultat);
				// on a réussi à améliorer le résultat
				if (res_temp != 0)
				{
					ameliorations += 1;
					resultat = res_temp;
				}
				nb_essais_permutation--;
			}
		}
		repeat++;
	}
	
	printf("Nombre d'améliorations : %d\n", ameliorations);
	
	for (i = 0; i < nb_etudiants; i++)
		solution[etudiants[i].id] = etudiants[i].groupe;
	
	free(matrice);
	free(etudiants);
}