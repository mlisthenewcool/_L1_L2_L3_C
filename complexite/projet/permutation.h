int appartiennent_au_groupe(int groupe, int pos1, int pos2, etudiant *etudiants)
{
	return (etudiants[pos1].groupe == groupe && etudiants[pos2].groupe == groupe);
}

/**
 * _____________________________________________________________________
 *   Permute l'étudiant dans le groupe passé en paramètre
 *     - recalcule la solution
 *         si amelioration alors on enregistre la permutation
 * 
 * _____________________________________________________________________
 */
int permuter_etudiant(int etu, int groupe, int solution_min, etudiant *etudiants, int *tableau_groupes_poids)
{
	if (groupe == etudiants[etu].groupe)
		return 0;
	
	int solution_temp = solution_min;
	int groupe_temp = groupe;
	int i;
	
	int *tableau_groupes_poids_temp = malloc(nb_groupes * sizeof(int));
	for (i = 0; i < nb_groupes; i++)
		tableau_groupes_poids_temp[i] = tableau_groupes_poids[i];
	
	// incompatibilités
	for (i = 0; i < nb_etudiants; i++)
	{
		// suppressions avant permutation
		if (etudiants[i].id != etudiants[etu].id && etudiants[etu].groupe == etudiants[i].groupe)
		{
			// solution
			solution_temp -= matrice_incompatibilites[etudiants[etu].id][etudiants[i].id];
			// tableau poids groupe
			tableau_groupes_poids_temp[etudiants[etu].groupe] -= matrice_incompatibilites[etudiants[etu].id][etudiants[i].id];
		}
		
		// ajouts après permutation
		if (etudiants[i].id != etudiants[etu].id && groupe_temp == etudiants[i].groupe)
		{
			// solution
			solution_temp += matrice_incompatibilites[etudiants[etu].id][etudiants[i].id];
			// tableau poids groupe
			tableau_groupes_poids_temp[groupe] += matrice_incompatibilites[etudiants[etu].id][etudiants[i].id];
		}
	}
	
	// affectations
	solution_temp -= matrice_affectations[etudiants[etu].groupe][etudiants[etu].id];
	solution_temp += matrice_affectations[groupe_temp][etudiants[etu].id];
	
	// si meilleure solution
	if (solution_temp < solution_min)
	{
		//printf("\nAmélioration : étudiant %4d depuis %2d vers %2d // Coût : %8d\n", etudiants[etu].id, etudiants[etu].groupe, groupe_temp, solution_temp);
		
		for (i = 0; i < nb_groupes; i++)
			tableau_groupes_poids[i] = tableau_groupes_poids_temp[i];
		
		etudiants[etu].groupe = groupe_temp;
		
		free(tableau_groupes_poids_temp);
		return solution_temp;
	}
	
	free(tableau_groupes_poids_temp);
	return 0;
}

/**
 * _____________________________________________________________________
 *   Permute 2 étudiants depuis le groupe passé en paramètre
 *     - recalcule la solution
 *         si amelioration alors on enregistre la permutation
 * 
 * _____________________________________________________________________
 */
int permuter_2_etudiants(int etu1, int etu2, int groupe, int solution_min, etudiant *etudiants, int *tableau_groupes_poids)
{
	int solution_temp = solution_min;
	int groupe_temp_1 = rand() % nb_groupes;
	int groupe_temp_2 = rand() % nb_groupes;
	
	while (groupe_temp_1 == groupe)
		groupe_temp_1 = rand() % nb_groupes;
	
	while(groupe_temp_2 == groupe)
		groupe_temp_2 = rand() % nb_groupes;
	
	//printf("Groupe %d\n", groupe);
	//printf("On va changer %d vers %d\n", etudiants[etu1].id, groupe_temp_1);
	//printf("On va changer %d vers %d\n", etudiants[etu1].id, groupe_temp_2);
		
	int i;
	int *tableau_groupes_poids_temp = malloc(nb_groupes * sizeof(int));
	for (i = 0; i < nb_groupes; i++)
		tableau_groupes_poids_temp[i] = tableau_groupes_poids[i];
	
	// incompatibilités etudiant 1
	for (i = 0; i < nb_etudiants; i++)
	{
		// suppressions avant permutation
		if (etudiants[i].id != etudiants[etu1].id && etudiants[etu1].groupe == etudiants[i].groupe)
		{
			// solution
			solution_temp -= matrice_incompatibilites[etudiants[etu1].id][etudiants[i].id];
			// tableau poids groupe
			tableau_groupes_poids_temp[groupe] -= matrice_incompatibilites[etudiants[etu1].id][etudiants[i].id];
		}
		
		// ajouts après permutations
		if (etudiants[i].id != etudiants[etu1].id && groupe_temp_1 == etudiants[i].groupe)
		{
			// solution
			solution_temp += matrice_incompatibilites[etudiants[etu1].id][etudiants[i].id];
			// tableau poids groupe
			tableau_groupes_poids_temp[groupe_temp_1] += matrice_incompatibilites[etudiants[etu1].id][etudiants[i].id];
		}
	}
	
	// incompatibilités etudiant 2
	for (i = 0; i < nb_etudiants; i++)
	{
		// suppressions avant permutation
		if (etudiants[i].id != etudiants[etu1].id && etudiants[etu2].groupe == etudiants[i].groupe)
		{
			// solution
			solution_temp -= matrice_incompatibilites[etudiants[etu2].id][etudiants[i].id];
			// tableau poids groupe
			tableau_groupes_poids_temp[groupe] -= matrice_incompatibilites[etudiants[etu2].id][etudiants[i].id];
		}
		
		// ajouts après permutations
		if (etudiants[i].id != etudiants[etu2].id && groupe_temp_2 == etudiants[i].groupe)
		{
			// solution
			solution_temp += matrice_incompatibilites[etudiants[etu2].id][etudiants[i].id];
			// tableau poids groupe
			tableau_groupes_poids_temp[groupe_temp_2] += matrice_incompatibilites[etudiants[etu2].id][etudiants[i].id];
		}
	}
	
	// affectations etudiant 1
	solution_temp -= matrice_affectations[etudiants[etu1].groupe][etudiants[etu1].id];
	solution_temp += matrice_affectations[groupe_temp_1][etudiants[etu1].id];
	
	// affectations etudiant 2
	solution_temp -= matrice_affectations[etudiants[etu2].groupe][etudiants[etu2].id];
	solution_temp += matrice_affectations[groupe_temp_2][etudiants[etu2].id];
	
	// si meilleure solution
	if (solution_temp < solution_min)
	{
		printf("Amélioration\n");
		
		for (i = 0; i < nb_groupes; i++)
			tableau_groupes_poids[i] = tableau_groupes_poids_temp[i];
		
		etudiants[etu1].groupe = groupe_temp_1;
		etudiants[etu2].groupe = groupe_temp_2;
		return solution_temp;
	}
	
	return 0;
}