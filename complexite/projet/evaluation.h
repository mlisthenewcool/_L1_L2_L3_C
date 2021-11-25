// __________________________________ EVALUATION __________________________________ //

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
				printf("Malus d'incompatibilite entre %d et %d) --> %d\n", etudiants[i].id, etudiants[j].id, matrice_incompatibilites[etudiants[i].id][etudiants[j].id]);
				#endif
			}
		}
	}
	return valeur;
}

int evaluer_permutation(int etudiant, int groupe)
{
	//TODO
	return 0;
}