/** @author MagicBanana */

void fusionner(int *tab, int a, int m, int b)
{
	int i, j, k, n;
	n = m - a + 1; 	// n : nombre d'éléments de la première partition
	int save[n];
	
	for(i = 0; i < n; i++) 	// on recopie la première partition en mémoire
		save[i] = tab[a+i];
	
	i = a; 	// i : décrit le tableau
	j = 0; 	// j : décrit la sauvegarde de la première partition
	k = m + 1; // k : décrit la seconde partition
	
	while(j < n)	// tant qu'il reste des éléments dans la première partition
	{
		if(k <= b && tab[k] < save[j]) 	// s'il y en a des plus petits dans la seconde
		{
			tab[i] = tab[k];	// on les écrit
			k++;
		}
		else	// sinon, on recopie la première partition
		{
			tab[i] = save[j];
			j++;
		}
			
		i++;
	}
}

void tri_fusion(int *tab, int a, int b)
{
	int milieu;
	
	if (a < b)
	{
		milieu = (a + b) / 2;
		tri_fusion(tab, a, milieu);
		tri_fusion(tab, milieu + 1, b);
		fusionner(tab, a, milieu, b);
	}
}
