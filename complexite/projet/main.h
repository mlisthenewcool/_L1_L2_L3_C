/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
void ecrire_solution(char *nom_fichier, int* solution, int valeur)
{
	FILE* fichier_sortie;
	
	if((fichier_sortie = fopen("toutes_les_solutions", "a")) == NULL )
	{
		printf("Fichier n'existe pas : %s\n", nom_fichier);
		exit(2);
	}
	
	fprintf(fichier_sortie, "%s\t", nom_fichier);
	fprintf(fichier_sortie, "%d\t", valeur);
	
	int i;
	for(i = 0; i < nb_etudiants; i++)
		fprintf(fichier_sortie, "%d\t", solution[i]);
	
	fprintf(fichier_sortie, "\n");
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
void lire_fichier(char *nom_fichier)
{
	FILE *fichier;
	int i, j;
	char contenu[255];
	
	/* 1. Ouverture du fichier */
	if((fichier = fopen(nom_fichier, "r")) == NULL)
	{
		printf("\nLe fichier %s n'a pas pu être ouvert !\n\n", nom_fichier);
		exit(2);
	}
	
	fscanf(fichier, "%s", contenu);
#ifdef AFFICHAGE_FICHIER
	printf("%s\n", contenu);
#endif
	
	/* 2. Enregistrement des variables */
	fscanf(fichier, "%d %d %d %d", &nb_groupes, &nb_etudiants, &nb_affectations, &nb_incompatibilites);
	
#ifdef AFFICHAGE_FICHIER
	printf("%3d %3d %3d %3d\n", nb_groupes, nb_etudiants, nb_affectations, nb_incompatibilites);
#endif
	
	fscanf(fichier, "%s", contenu);
	
#ifdef AFFICHAGE_FICHIER
	printf("%s\n", contenu);
#endif
	
	/* 3. Enregistrement de la matrice d'affectations */
	matrice_affectations = malloc(nb_groupes * sizeof(int*));
	for(i = 0; i < nb_groupes; i++)
	{
		matrice_affectations[i] = malloc(nb_etudiants * sizeof(int));
		for(j = 0; j < nb_etudiants; j++)
			matrice_affectations[i][j] = 0;
	}
	
	for(i = 0; i < nb_affectations; i++)
	{
		int v1, v2, v3;
		
		if(fscanf(fichier, "%d %d %d", &v1, &v2, &v3) != 3)
		{
			perror("Erreur lecture du graphe : ");
			exit(4);
		}
		
		if(v1 < 0 || v2 < 0 || v1 >= nb_groupes || v2 >= nb_etudiants)
		{
			printf("Erreur lecture du graphe : ensembles et sommets invalides.\n");
			exit(5);
		}
		
		matrice_affectations[v1][v2] = v3;
		
#ifdef AFFICHAGE_FICHIER
		printf("%3d %3d %3d\n", v1, v2, v3);
#endif
	}
	
	fscanf(fichier, "%s", contenu);
#ifdef AFFICHAGE_FICHIER
	printf("%s\n", contenu);
#endif
	
	/* 4. Enregistrement de la matrice d'incompatibilités */
	matrice_incompatibilites = malloc(nb_etudiants * sizeof(int*));
	for(i = 0; i < nb_etudiants; i++)
	{
		matrice_incompatibilites[i] = malloc(nb_etudiants * sizeof(int));
		for(j = 0; j < nb_etudiants; j++)
			matrice_incompatibilites[i][j] = 0;
	}
	
	for(i = 0; i < nb_incompatibilites; i++)
	{
		int v1, v2, v3;
		
		if(fscanf(fichier, "%d %d %d", &v1, &v2, &v3) != 3)
		{
			perror("Erreur lecture du graphe : ");
			exit(4);
		}
		
		if(v1 < 0 || v2 < 0 || v1 >= nb_etudiants || v2 >= nb_etudiants)
		{
			printf("Erreur lecture du graphe : ensembles et sommets invalides.\n");
			exit(5);
		}
		
		matrice_incompatibilites[v1][v2] = v3;
		matrice_incompatibilites[v2][v1] = v3;
		
#ifdef AFFICHAGE_FICHIER
		printf("%d %d %d\n", v1, v2, v3);
#endif
	}
	
	fclose(fichier);
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
int evaluer(int* solution)
{
	int i, j;
	int valeur = 0;
	for(i = 0; i < nb_etudiants; i++)
	{
		valeur += matrice_affectations[solution[i]][i];
#ifdef AFFICHAGE_EVALUATION
		printf("Affectation de l'etudiant %d au groupe %d --> %d\n", i, solution[i], matrice_affectations[solution[i]][i]);
#endif
		for(j = i + 1; j < nb_etudiants; j++)
		{
			if(solution[i] == solution[j])
			{
				valeur += matrice_incompatibilites[i][j];
#ifdef AFFICHAGE_EVALUATION
				printf("Malus d'incompatibilite (%d,%d) ; (%d,%d) --> %d\n", i, solution[i], j, solution[j], matrice_incompatibilites[i][j]);
#endif
			}
		}
	}
	return valeur;
}

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
void afficher_matrices()
{
	int i, j;
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Matrice des affectations (ligne : groupe, colonne : etudiant)\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	
	for(i = 0; i < nb_groupes; i++)
	{
		for(j = 0; j < nb_etudiants; j++)
			printf("%4d", matrice_affectations[i][j]);
		
		printf("\n");
	}
	
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Matrice des incompatibilites (ligne : etudiant, colonne : etudiant)\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	for(i = 0; i < nb_etudiants; i++)
	{
		for(j = 0; j < nb_etudiants; j++)
		{
			printf("%4d", matrice_incompatibilites[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
void liberer()
{
	int i;
	for(i = 0; i < nb_groupes; i++)
		free(matrice_affectations[i]);
	free(matrice_affectations);
	
	for(i = 0; i < nb_etudiants; i++)
		free(matrice_incompatibilites[i]);
	free(matrice_incompatibilites);
}