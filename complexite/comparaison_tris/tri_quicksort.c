/** @author MagicBanana */

void quick_sort(int *tab, int debut, int fin)
{
	int pivot, temp, i, j;
	
	if(debut < fin)
	{
		pivot = debut;
		i = debut;
		j = fin;
		
		while(i < j)
		{
			while((tab[i] <= tab[pivot]) && (i < fin))
				i++;
			
			while(tab[j] > tab[pivot])
				j--;
			
			if(i < j)
			{ 
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
			}
		}
		
		temp = tab[pivot];
		tab[pivot] = tab[j];
		tab[j] = temp;
		
		quick_sort(tab, debut, j-1);
		quick_sort(tab, j+1, fin);
	}
}
