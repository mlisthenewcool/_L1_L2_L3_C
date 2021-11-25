/** @author MagicBanana */

void tri_comptage(int *tab, int taille, int max)
{
	unsigned int i, j = 0, k, compteur[max];

	// Mise à zéro du compteur
	for(i = 0; i < max; i++)
		compteur[i] = 0;

	// Dénombrement des éléments
	for(i = 0; i < taille; i++)
		compteur[tab[i]]++;

	// On replace les éléments dans le tableau
	for(i = 0; i < max; i++)
	{
		// Il y a compteur[i] éléments ayant la valeur i
		for(k = 0; k < compteur[i]; k++, j++)
			tab[j] = i;
	}
}