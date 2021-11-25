// __________________________________ ETUDIANT __________________________________ //
/**
 * Permet de trier les étudiants par poids décroissant grâce à qsort()
 */
int etudiant_compare_poids(const void *a, const void *b)
{
	etudiant *a1 = (etudiant *) a;
	etudiant *b1 = (etudiant *) b;
	
	return a1->poids < b1->poids;
}

int etudiant_compare_poids_actuel(const void *a, const void *b)
{
	etudiant *a1 = (etudiant *) a;
	etudiant *b1 = (etudiant *) b;
	
	return (a1->poids / a1->poids_actuel) > (b1->poids / b1->poids_actuel);
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
 * @param  int id : l'identifiant de l'étudiant
 * @return int    : le poids total des incompatibilités de l'étudiant
 */ 
int etudiant_poids_actuel(int etu, etudiant *etudiants)
{
	int i;
	int valeur = 0;
	
	for (i = 0; i < nb_etudiants; i++)
	{
		if (etudiants[etu].groupe == etudiants[i].groupe)
			valeur += matrice_incompatibilites[etudiants[etu].id][etudiants[i].id];
	}
	
	return valeur;
}

/**
 * Permet de trier les affectations des étudiants par cout d'affectation
 */
void tri_etudiant_affectations(int id, int **matrice)
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

int etudiant_find_position_affectation(int etudiant, int cout_affectation)
{
	int debut = 0;
	int fin = nb_groupes - 1;
	int milieu = (debut + fin) / 2;
	
	while (debut <= fin)
	{
		if (matrice_affectations[milieu][etudiant] < cout_affectation)
			debut = milieu + 1;
		else if (matrice_affectations[milieu][etudiant] > cout_affectation)
			debut = milieu - 1;
		else
			return milieu;
		
		milieu = (debut + fin) / 2;
	}
	
	return -1; // valeur non trouvée
}

int etudiant_find_position_affectation2(int etudiant, int affectation)
{
	//TODO à remplacer par le 1
	int i;
	for (i = 0; i < nb_groupes; i++)
	{
		if (matrice_affectations[i][etudiant] == affectation)
			return i;
	}
	
	return 0;
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