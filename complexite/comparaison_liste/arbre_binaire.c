typedef struct arbre_binaire
{
	int valeur;
	struct arbre_binaire *gauche;
	struct arbre_binaire *droite;
} arbre_binaire_t;

/**
 * 
 */ 
arbre_binaire_t* creer (int val)
{
	arbre_binaire_t *new = malloc(sizeof(arbre_binaire_t));
	
	if (new == NULL)
	{
		perror ("Erreur malloc creer() ");
		exit(1);
	}
	
	new->valeur = val;
	new->gauche = NULL;
	new->droite = NULL;
	
	return new;
}

/*
 * 
 */
arbre_binaire_t* ajouter (arbre_binaire_t *arbre, int val)
{
	if(arbre == NULL)
		arbre = creer(val);
	
	else
	{
		int gauche = 0, existe = 0;
		arbre_binaire_t *curseur = arbre, *pred = NULL;
		
		while (curseur != NULL && existe == 0)
		{
			pred = curseur;
			
			if (val < curseur->valeur)
			{
				gauche = 1;
				curseur = curseur->gauche;
			}
			else if (val > curseur->valeur)
				curseur = curseur->droite;
			else
				existe = 1;
		}
		
		if(gauche == 0)
			pred->gauche = creer(val);
		
		else
			pred->droite = creer(val);
		
	}
	
	return arbre;
}

int search (arbre_binaire_t *arbre, int key)
{
	// arbre_binaire_t *arbre_cpy = malloc(
	return 0;
}

void afficher(arbre_binaire_t *arbre) {
	if (arbre != NULL) {
		afficher(arbre->gauche);
		printf("%d\n", arbre->valeur);
		afficher(arbre->droite);
	}
}
