#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#include "tri_bulle.c"
#include "tri_insertion.c"
#include "tri_fusion.c"
#include "tri_quicksort.c"
#include "tri_comptage.c"

int N;
#include "main.h"

#define MIN_SLEEP 150
#define MAX_TAB 100

int main (int argc, char **argv)
{

	if (argc == 2)
		N = atoi(argv[1]);
	
	else
	{
		printf("\nUsage invalide !\n\t%s taille_matrice\n\n", argv[0]);
		exit(1);
	}
	
	/**
	 * Création d'une matrice pour augmenter les temps de calcul
	 */ 
	int i, j, **matrice = malloc(N * sizeof(int*));
	
	srand(time(NULL));
	
	for (i = 0; i < N; i++)
	{
		matrice[i] = malloc(N * sizeof(int));
		for (j = 0; j < N; j++)
			matrice[i][j] = rand() % MAX_TAB;
	}
	
	if (N < 21)
	{
		printf("\n-----------------------------------\n");
		printf("MATRICE INITIALE NON TRIEE\n");
		printf("-----------------------------------\n");
		afficher(matrice);
	}

	/**
	 * Tests sur les différents algorithmes de tri
	 */ 
	
	float temps;
	clock_t t1, t2;
	int pid[5], statut; //, total_op = 0;
	
	for (i = 0; i < 5; i++)
	{
		// 1. Erreur fork()
		if ((pid[i] = fork()) < 0)
		{
			perror("Erreur fork() : ");
			exit(1);
		}
		
		// 2. Processus fils
		else if (pid[i] == 0)
		{
			switch (i)
			{
				/*
				 * 2.1. Tri_fusion
				 */
				case 0 :
					t1 = clock();
					
					for (j = 0; j < N; j++)
						tri_fusion(matrice[j], 0, N-1);
						//total_op = total_op + tri_fusion(matrice[j], 0, N - 1);
					
					t2 = clock();
					temps = (float)(t2 - t1) / CLOCKS_PER_SEC;

					printf("\n-----------------------------------\n");
					printf("TRI FUSION    : %f secondes\n", temps);
					//printf("              : %d opérations\n", total_op);
					printf("-----------------------------------\n");
					
					if (N < 21)
						afficher(matrice);
					
					liberer(matrice);
					exit(0);
				break;
				/*
				 * 2.2. Tri_insertion
				 */
				case 1 :
					t1 = clock();
					
					for (j = 0; j < N; j++)
						tri_insertion(matrice[j], N);
					
					t2 = clock();
					temps = (float)(t2-t1)/CLOCKS_PER_SEC;
					
#if MIN_SLEEP
					if (N < MIN_SLEEP)
						sleep(1);
#endif
					
					printf("\n-----------------------------------\n");
					printf("TRI INSERTION : %f secondes\n", temps);
					printf("-----------------------------------\n");
					
					if (N < 21)
						afficher(matrice);
					
					liberer(matrice);
					exit(0);
				break;
				/*
				 * 2.3. Tri_bulle
				 */
				case 2 :
					t1 = clock();
					for (j = 0; j < N; j++)
						tri_bulle(matrice[j], N);
						//total_op = total_op + tri_bulle(matrice[j]);
					
					t2 = clock();
					temps = (float)(t2-t1)/CLOCKS_PER_SEC;
					
#if MIN_SLEEP
					if (N < MIN_SLEEP)
						sleep(2);
#endif

					printf("\n-----------------------------------\n");
					printf("TRI BULLE     : %f secondes\n", temps);
					//printf("              : %d opérations\n", total_op);
					printf("-----------------------------------\n");
					
					if (N < 21)
						afficher(matrice);
					
					liberer(matrice);
					exit(0);
				break;
				/*
				 * 2.4. Tri_quicksort
				 */
				case 3 :
					t1 = clock();
					for (j = 0; j < N; j++)
						quick_sort(matrice[j], 0, N-1);
					
					t2 = clock();
					temps = (float)(t2-t1)/CLOCKS_PER_SEC;
					
					#if MIN_SLEEP
					if (N < MIN_SLEEP)
						sleep(3);
					#endif
					
					printf("\n-----------------------------------\n");
					printf("TRI QUICKSORT : %f secondes\n", temps);
					printf("-----------------------------------\n");
					
					if (N < 21)
						afficher(matrice);
					
					liberer(matrice);
					exit(0);
					break;
					/*
					 * 2.5. Tri_comptage
					 */
					case 4 :
						t1 = clock();
						for (j = 0; j < N; j++)
							tri_comptage(matrice[j], N, MAX_TAB);
						
						t2 = clock();
						temps = (float)(t2-t1)/CLOCKS_PER_SEC;
						
						#if MIN_SLEEP
						if (N < MIN_SLEEP)
							sleep(4);
						#endif
						
						printf("\n-----------------------------------\n");
						printf("TRI COMPTAGE : %f secondes\n", temps);
						printf("-----------------------------------\n");
						
						if (N < 21)
							afficher(matrice);
						
						liberer(matrice);
						exit(0);
						break;
			}
		}
	}
	
	for (i = 0; i < 5; i++)
	{
		waitpid(pid[i], &statut, 0);
		//if(WIFEXITED(statut))
			//printf("Fils %d terminé avec le statut %d\n", i, WEXITSTATUS(statut));
	}
	
	return 0;
}

