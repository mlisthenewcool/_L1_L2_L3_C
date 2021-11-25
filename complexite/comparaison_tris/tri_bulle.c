/** @author MagicBanana */

void tri_bulle(int *tab, int taille)
{
	int i, temp, est_trie = 0;//, nb_op = 0;
	
	while(est_trie == 0)
	{
		est_trie = 1;
		
		for(i = 0; i < taille - 1; i++)
		{
			if(tab[i] > tab[i+1])
			{
				temp = tab[i+1];
				tab[i+1] = tab[i];
				tab[i] = temp;
				est_trie = 0;
				//nb_op++;
			}
		}
	}
	
	//return nb_op;
}