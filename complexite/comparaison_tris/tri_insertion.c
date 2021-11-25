/** @author MagicBanana */

void tri_insertion(int *tab, int taille)
{
	int i, j, temp;
	
	for (i = 1; i < taille; i++)
	{
		temp = tab[i];
		
		for (j = i; j > 0 && tab[j-1] > temp; j--)
			tab[j] = tab[j - 1];
		
		tab[j] = temp;
	}
}