/**
 * _____________________________________________________________________
 *   Initialise la structure utilisée
 *     - en fonction des coûts d'affectations aux groupes
 *     - puis tri en fonction du poids total des incompatibilités
 *     - retourne le coût de la solution
 * _____________________________________________________________________
 */
int initialisation_etudiants(etudiant *etudiants, int **matrice_triee_affectations_groupes_par_etudiant, int rang)
{
	int i;
	for (i = 0; i < nb_etudiants; i++)
	{
		etudiants[i].id = i;
		etudiants[i].poids = etudiant_poids_incompatibilites(i);
		etudiants[i].groupe = etudiant_find_position_affectation2(i, matrice_triee_affectations_groupes_par_etudiant[rang][i]);
		
#ifdef DEBUG
		printf("Etudiant %d affecté au groupe %d\n", i, etudiants[i].groupe);
#endif
	}
	
	qsort(etudiants, nb_etudiants, sizeof(etudiants[0]), etudiant_compare_poids);
	
#ifdef DEBUG
	etudiant_afficher_poids(etudiants);
#endif
	
	return evaluer_etudiants(etudiants);
}

/**
 * _____________________________________________________________________
 * Algo
 * 
 * _____________________________________________________________________
 */ 
void algo(int *solution, int nb_executions, int rang)
{
	etudiant *etudiants = malloc (nb_etudiants * sizeof(etudiant));
	int      resultat;
	int      i, j;
	int      **matrice_triee_affectations_par_etudiant = malloc(nb_groupes * sizeof(int*));
	
	// copie de la matrice_affectations
	for (i = 0; i < nb_groupes; i++)
	{
		matrice_triee_affectations_par_etudiant[i] = malloc(nb_etudiants * sizeof(int));
		for (j = 0; j < nb_etudiants; j++)
			matrice_triee_affectations_par_etudiant[i][j] = matrice_affectations[i][j];
	}
	
	// tri copie
	for (i = 0; i < nb_etudiants; i++)
		tri_etudiant_affectations(i, matrice_triee_affectations_par_etudiant);
	
	// initialisation de la structure et évaluation de la solution
	resultat = initialisation_etudiants(etudiants, matrice_triee_affectations_par_etudiant, rang);
	
	int *tableau_composition_groupes = malloc(nb_groupes * sizeof(int));
	initialiser_poids_effectif_groupes(etudiants, tableau_composition_groupes);
	
	printf("* * * * * * * * * * * * * * * * * * * * * *\n");
	printf("Algorithme au rang %d\n", rang);
	printf("Resultat initial : %d\n", resultat);
	
	/* Permutations */
	int res_temp;								// résultat temporaire
	int repeat = 0;							// le nombre de fois où l'algo est exécuté
	int permutation_bool = 0;		// booléen indiquant si une boucle complète a permuté des étudiants
	int permutation_bool_temp;	// booléen permettant de sortir d'un minimum local bloquant
	
	/* Permutations 2-opt */
	int nb_permutations_2 = 0;	// le nombre de permutations 2-opt
	int permutation_2_bool = 0;	// booléen indiquant quand une permutation 2-opt a été trouvée
	int groupe_max;
	
	while (repeat < nb_executions)
	{
		permutation_bool = 0;
		
		/* Permutations d'un étudiant à la fois */
		for (i = 0; i < nb_etudiants; i++)
		{
			for (j = 0; j < nb_groupes ; j++)
			{
				res_temp = permuter_etudiant(etudiants[i].id, j, resultat, etudiants, tableau_composition_groupes);
				// on a réussi à améliorer le résultat
				if (res_temp != 0)
				{
					permutation_bool = 1;
					resultat = res_temp;
				}
			}
		}
		
		/* Si aucune permutation n'a été éffectuée */
		if (permutation_bool == 0)
		{
			printf("Plus d'améliorations après repeat %d\n", repeat);
			printf("La meilleure solution trouvée était %d\n", resultat);
			
			initialiser_poids_effectif_groupes(etudiants, tableau_composition_groupes);
			
			while (permutation_2_bool == 0)
			{
				groupe_max = groupe_find_max_poids_modif(tableau_composition_groupes);
				for (i = 0; i < nb_etudiants; i++)
				{
					for (j = i + 1; j < nb_etudiants; j++)
					{
						if (etudiants[i].groupe != etudiants[j].groupe)
						{
							res_temp = permuter_2_etudiants(i, j, resultat, etudiants, tableau_composition_groupes);
							
							// on a réussi à améliorer le résultat
							if (res_temp != 0)
							{
								permutation_2_bool = 1;
								permutation_bool = 1;
								resultat = res_temp;
					
								printf("Permutations 2-opt %d\n", nb_permutations_2);
								nb_permutations_2++;
							}
						}
					}
				}
			}
		}
		repeat++;
	}
	
	// copie des solutions depuis la structure vers le tableau de solutions
	for (i = 0; i < nb_etudiants; i++)
		solution[etudiants[i].id] = etudiants[i].groupe;
	
	free(matrice_triee_affectations_par_etudiant);
	free(etudiants);
}