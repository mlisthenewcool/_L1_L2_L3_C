// __________________________________ GROUPE __________________________________ //
int groupe_compare_poids(const void *a, const void *b)
{
	return *(int*) b - *(int*) a;
}

/**
 * @param  int       id_groupe : l'identifiant du groupe
 * @param  etudiant* etudiants : la structure etudiants
 * @return int                 : le poids d'incompatibilités du groupe id
 */
int groupe_get_poids(int id_groupe, etudiant *etudiants)
{
	int i, j;
	int poids = 0;
	for (i = 0; i < nb_etudiants; i++)
	{
		for (j = i + 1; j < nb_etudiants; j++)
		{
			if (etudiants[i].groupe == id_groupe && etudiants[i].groupe == etudiants[j].groupe)
				poids += matrice_incompatibilites[etudiants[i].id][etudiants[j].id];
		}
	}
	
	return poids;
}

void initialiser_poids_effectif_groupes(etudiant *etudiants, int *tableau_poids_effectif_groupes)
{
	int i, j;
	
	for (i = 0; i < nb_groupes; i++)
		tableau_poids_effectif_groupes[i] = 0;
	
	for (i = 0; i < nb_etudiants; i++)
	{
		for (j = i + 1; j < nb_etudiants; j++)
		{
			if (etudiants[i].groupe == etudiants[j].groupe)
			{
				//printf("etudiant %d avec %d (groupe %d) --> %d\n", etudiants[i].id, etudiants[j].id, etudiants[i].groupe, matrice_incompatibilites[etudiants[i].id][etudiants[j].id]);
				tableau_poids_effectif_groupes[etudiants[i].groupe] += matrice_incompatibilites[etudiants[i].id][etudiants[j].id];
			}
		}
	}
	
	//qsort(tableau_poids_effectif_groupes, nb_groupes, sizeof(tableau_poids_effectif_groupes[0]), groupe_compare_poids);
}

int groupe_find_position_poids(int *tableau_trie_poids_effectif_groupes, int poids)
{
	int debut = 0;
	int fin = nb_groupes - 1;
	int milieu;
	int pos = -1;
	
	while (debut <= fin)
	{
		milieu = debut + (fin - debut) / 2;
		
		if (tableau_trie_poids_effectif_groupes[milieu] < poids)
			debut = milieu + 1;
		else if (tableau_trie_poids_effectif_groupes[milieu] > poids)
			fin = milieu - 1;
		else
		{
			pos = milieu;
			break;
		}
	}
	
	return pos;
}

int groupe_find_max_poids(int *tableau_poids_effectif_groupes)
{
	int i;
	int pos;
	int max, max_temp = INT_MAX;
	
	for (i = 0; i < nb_groupes; i++)
	{
		max_temp = tableau_poids_effectif_groupes[i];
		if (max_temp > max)
		{
			max = max_temp;
			pos = i;
		}
	}
	
	return pos;
}

int groupe_find_max_poids_modif(int *tableau_poids_effectif_groupes)
{
	int i;
	int pos;
	int max, max_temp = INT_MAX;
	
	for (i = 0; i < nb_groupes; i++)
	{
		max_temp = tableau_poids_effectif_groupes[i];
		if (max_temp > max)
		{
			max = max_temp;
			pos = i;
		}
	}
	
	tableau_poids_effectif_groupes[pos] = -1;
	return pos;
}