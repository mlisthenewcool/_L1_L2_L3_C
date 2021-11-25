/*
int** copier(int **matrice)
{
	int i, j;
	int **copie = malloc(N * sizeof(int*));
	
	for(i = 0; i < N; i++)
	{
		copie[i] = malloc(N * sizeof(int));
		
		for(j = 0; j < N; j++)
			copie[i][j] = matrice[i][j];
	}
	
	return copie;
}
*/

void liberer(int **matrice)
{
	int i;
	
	for(i = 0; i < N; i++)
		free(matrice[i]);
	
	free(matrice);
}

void afficher(int **matrice)
{
	int i, j;
	//printf("---------- DEBUT ----------\n");
	
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
			printf("%3d", matrice[i][j]);
		
		printf("\n");
	}
	
	//printf("---------- FIN ----------\n");
}