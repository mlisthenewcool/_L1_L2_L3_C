typedef struct
{
	int id;
	int poids;
	int groupe;
} etudiant;

// _______________________________ EVALUATION _____________________________________ //

int evaluer_etudiants(etudiant *etudiants)
{
	int i, j;
	int valeur = 0;
	for(i = 0; i < nb_etudiants; i++)
	{
		valeur += matrice_affectations[etudiants[i].groupe][etudiants[i].id];
		#ifdef AFFICHAGE_EVALUATION
		printf("Affectation de l'etudiant %d au groupe %d --> %d\n", i, etudiants[i].groupe, matrice_affectations[etudiants[i].groupe][i]);
		#endif
		for(j = i + 1; j < nb_etudiants; j++)
		{
			if(etudiants[i].groupe == etudiants[j].groupe)
			{
				valeur += matrice_incompatibilites[etudiants[i].id][etudiants[j].id];
				#ifdef AFFICHAGE_EVALUATION
				printf("Malus d'incompatibilite (%d,%d) ; (%d,%d) --> %d\n", i, etudiants[i].groupe, j, etudiants[j].groupe, matrice_incompatibilites[i][j]);
				#endif
			}
		}
	}
	return valeur;
}

// _________________________________ ETUDIANTS _______________________________________ //

/**
 * Permet de trier les étudiants par poids décroissant grâce à qsort()
 */
int etudiant_compare_poids(const void *a, const void *b)
{
	etudiant *a1 = (etudiant *) a;
	etudiant *b1 = (etudiant *) b;
	
	return a1->poids < b1->poids;
}

/**
 * @param  int id : l'identifiant de l'étudiant
 * @return int    : le poids total des incompatibilités de l'étudiant
 */ 
int etudiant_poids_incompatibilites(int id)
{
	int i, j;
	int valeur = 0;
	
	for (i = 0; i < nb_etudiants; i++)
	{
		for (j = i + 1; j < nb_etudiants; j++)
		{
			if (i == id || j == id)
				valeur += matrice_incompatibilites[i][j];
		}
	}
	
	return valeur;
}

/**
 * @param  int   id      : l'identifiant de l'étudiant
 * @param  int** matrice : la matrice d'affectations
 * @return int           : la position du groupe 
 */ 
int etudiant_get_min_affectation(int id)
{
	int i;
	int pos;
	int min = MAX_RAND;
	
	for (i = 0; i < nb_groupes; i++)
	{
		if (matrice_affectations[i][id] < min)
		{
			min = matrice_affectations[i][id];
			pos = i;
		}
	}
	
	return pos;
}

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

/**
 * @param etudiant* etudiants : la structure des étudiants à afficher
 */ 
void etudiant_afficher_poids(etudiant *etudiants)
{
	int i;
	
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Poids total des incompatibilités des étudiants\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	
	for (i = 0; i < nb_etudiants; i++)
		printf("Etudiant %d --> Poids %d\n", etudiants[i].id, etudiants[i].poids);
}

/**
 * @param  int id : l'identifiant de l'étudiant
 * @return int    : la valeur de l'affectation au groupe de l'étudiant id
 */ 
int etudiant_get_affectation(int id, etudiant *etudiants)
{
	int i;
	for (i = 0; i < nb_groupes; i++)
	{
		if (etudiants[id].groupe == i)
			return matrice_affectations[i][id];
	}
	
	return 0;
}

// _________________________________ GROUPES ______________________________________ //

/**
 * @param  int       id        : l'identifiant du groupe
 * @param  etudiant* etudiants : la structure etudiants
 * @return int                 : le poids d'incompatibilités du groupe id
 */ 
int groupe_get_poids(int id, etudiant *etudiants)
{
	int i, j;
	int poids = 0;
	for (i = 0; i < nb_etudiants; i++)
	{
		for (j = i + 1; j < nb_etudiants; j++)
		{
			if (etudiants[i].groupe == id && etudiants[i].groupe == etudiants[j].groupe)
				poids += matrice_incompatibilites[etudiants[i].id][etudiants[j].id];
		}
	}
	
	return poids;
}

/**
 * 
 */ 
int permute_etudiant(int id, etudiant *etudiants, int min_solution)
{
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
		{
			#ifdef DEBUG
			printf("- avant : %d\n", nouveau_cout);
			#endif
			nouveau_cout -= matrice_incompatibilites[etudiants[id].id][etudiants[i].id];
			#ifdef DEBUG
			printf("- %d avec %d : %d enlevé --> new : %d\n", etudiants[id].id, etudiants[i].id, matrice_incompatibilites[etudiants[id].id][etudiants[i].id], nouveau_cout);
			#endif
		}
		
		// ajouts des incompatibilités arpès permutation
		if (etudiants[i].id != etudiants[id].id && meilleur_groupe == etudiants[i].groupe)
		{
			#ifdef DEBUG
			printf("+ avant : %d\n", nouveau_cout);
			#endif
			nouveau_cout += matrice_incompatibilites[etudiants[id].id][etudiants[i].id];
			#ifdef DEBUG
			printf("+ %d avec %d : %d enlevé --> new : %d\n", etudiants[id].id, etudiants[i].id, matrice_incompatibilites[etudiants[id].id][etudiants[i].id], nouveau_cout);
			#endif
		}
	}
	
	if (nouveau_cout < min_solution)
	{
		#ifdef DEBUG
		printf("Amélioration : etudiant %d depuis %d vers %d\n", etudiants[id].id, etudiants[id].groupe, meilleur_groupe);
		#endif
		etudiants[id].groupe = meilleur_groupe;
		return nouveau_cout;
	}
	else
		return 0;
}

// _____________________________ SOLUTION_INITIALE ________________________________ //
/**
 * Permet de trier les affectations des étudiants par cout d'affectation
 */
void tri_etudiants_to_groupe(int id, int **matrice)
{
	int i, j = 0, k;
	
	int compteur[MAX_RAND];
	for (i = 0; i < MAX_RAND; i++)
		compteur[i] = 0;
	
	for (i = 0; i < nb_groupes; i++)
		compteur[matrice[i][id]]++;
	
	for (i = 0; i < MAX_RAND; i++)
	{
		for (k = 0; k < compteur[i]; k++, j++)
			matrice[j][id] = i;
	}
}

int position_groupe(int etudiant, int affectation)
{
	int i;
	for (i = 0; i < nb_groupes; i++)
	{
		if (matrice_affectations[i][etudiant] == affectation)
			return i;
	}
	
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
	int ameliorations = 0;		// le nombre d'améliorations trouvées
	while (repeat < nb_executions)
	{
		for (i = 0; i < nb_etudiants; i++)
		{
			compteur = 0;
			while(compteur < nb_groupes)
			{
				// permutation
				res_temp = permute_etudiant(i, etudiants , resultat);
				// on a réussi à améliorer le résultat
				if (res_temp != 0)
				{
					ameliorations++;
					resultat = res_temp;
				}
				// on incrémente le nombre d'essais restants
				compteur++;
			}
		}
		repeat++;
	}
	
	printf("Nombre d'améliorations : %d\n", ameliorations);
	
	/* Copie des résultats depuis la structure étudiants vers le tableau solution */
	for (i = 0; i < nb_etudiants; i++)
		solution[etudiants[i].id] = etudiants[i].groupe;
}

/* _________________________________ */
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

void algo2(int *solution, int nb_executions)
{
	// Malloc de la structure etudiant
	// + initialisation
	// + tri
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
	
	#ifdef DEBUG
	etudiant_afficher_poids(etudiants);
	printf("\nResultat initial : %d\n", resultat);
	#endif
	
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
	
	printf("Solution finale : %d\n", resultat);
}

/* _________________________________ */
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

void algo3(int *solution, int nb_executions)
{
	// Malloc de la structure etudiant
	// + initialisation
	// + tri
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
	
	#ifdef DEBUG
	etudiant_afficher_poids(etudiants);
	printf("\nResultat initial : %d\n", resultat);
	#endif
	
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
	
	printf("Solution finale : %d\n", resultat);
}