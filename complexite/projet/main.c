#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>

int **matrice_affectations;
int **matrice_incompatibilites;

int nb_groupes;
int nb_etudiants;
int nb_affectations;
int nb_incompatibilites;

typedef struct
{
	int id;
	int poids;
	int poids_actuel;
	int groupe;
} etudiant;

#define MAX_RAND 1000
//#define AFFICHAGE_MATRICE
//#define AFFICHAGE_FICHIER
//#define AFFICHAGE_EVALUATION
//#define DEBUG

#include "main.h"
#include "etudiant.h"
#include "groupe.h"
#include "permutation.h"
#include "evaluation.h"

#include "algo4.c"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("\nUsage invalide !\n\t--> %s instance nombre_d_executions\n\n", argv[0]);
		exit(1);
	}
	
	char fichier[20] = "instances/";
	strcat(fichier, argv[1]);
	strcat(fichier, ".ist");
	lire_fichier(fichier);
	
	srand(time(NULL));
	
	printf("\n");
#ifdef AFFICHAGE_MATRICE
	afficher_matrices();
#endif
	
	/* Evalutations */
	float    temps;
	clock_t  t1, t2;
	int      *solution = malloc(nb_etudiants * sizeof(int));
	if (solution == NULL)
	{
		printf("Erreur malloc solution, abording\n");
		exit(1);
	}
	int      resultat = INT_MAX;
	int      count_processus;
	int      i, j, k;
	
	if (nb_groupes < 4)
		count_processus = nb_groupes;
	else
		count_processus = 4;
	
	pid_t    pid[count_processus];
	int      fds[count_processus][2];
	int      statut;
	
	/* Tubes */
	for (i = 0; i < count_processus; i++)
	{
		if (pipe(fds[i]) < 0)
		{
			perror("ERREUR pipe, abording ");
			exit(1);
		}
	}
	
	/* Forks */
	for (i = 0; i < count_processus; i++)
	{
		if ((pid[i] = fork()) < 0)
		{
			perror("ERREUR fork, abording ");
			exit(1);
		}
		
		// fils
		else if (pid[i] == 0)
		{
			// ferme tubes lecture
			for (j = 0; j < count_processus; j++)
			{
				close(fds[j][0]);
				// ferme tubes écriture autres que le sien
				if (i != j)
					close(fds[j][1]);
			}
			
			sleep(i);
			
			printf("* * * * * * * * * * * * * * * * * * * * * *\n");
			printf("Algorithme %d\n", i);
			
			/* Exécute l'algorithme */
			t1 = clock();
		
			algo(solution, atoi(argv[2]), i);
			resultat = evaluer(solution);
			
			t2 = clock();
			temps = (float)(t2 - t1) / CLOCKS_PER_SEC;
		
			printf("Solution : %d\n", resultat);
			printf("Temps    : %f secondes\n", temps);
			printf("* * * * * * * * * * * * * * * * * * * * * *\n");
			
			write(fds[j][1], &solution, sizeof(solution));
			close(fds[j][1]);
			
			free(solution);
			liberer();
			
			exit(0);
		}
		
		// parent
		else
		{
			// ferme tubes écriture
			for (j = 0; j < count_processus; j++)
			{
				close(fds[j][1]);
				// ferme tubes lecture autres que le sien
				if (i != j)
					close(fds[j][0]);
			}
		}
	}
	
	// on sera dans le parent à partir d'ici
	int *solution_temp = malloc(nb_etudiants * sizeof(int));
	if (solution_temp == NULL)
	{
		printf("Erreur malloc solution_temp, abording\n");
		exit(1);
	}
	
	//TODO recevoir les valeurs + tableau solution des forks
	for (j = 0; j < count_processus; j++)
	{
		read(fds[j][0], &solution_temp, sizeof(solution_temp));
		close(fds[j][0]);
		
		printf("\nSolution trouvée algo %d --> %d\n", j, evaluer(solution_temp));
		
		if (evaluer(solution_temp) < evaluer(solution))
		{
			// sauvegarde de la répartition
			for (k = 0; k < nb_etudiants; k++)
				solution[i] = solution_temp[i];
		}
	}
	
	// fermeture des fils
	for (j = 0; j < count_processus; j++)
	{
		waitpid(pid[i], &statut, 0);
		if (WIFEXITED(statut))
			printf("Fils %d terminé avec le statut %d\n", i, WEXITSTATUS(statut));
	}
	
	//if (resultat < 2185421)  // 20_500
	//if (resultat < 107429)   // 2_30
	//if (resultat < 1111)     // 10_10
	//if (resultat < 20405579)   // 25_1600
	ecrire_solution(argv[1], solution, evaluer(solution));
	
	free(solution_temp);
	free(solution);
	liberer();
	
	return 0;
}

/*
 t1 = clock();
 
 while(1)
 {
 for (i = 0; i < nb_etudiants; i++)
	 solution_temp[i] = rand() % nb_groupes;
 
 resultat_temp = evaluer(solution_temp);
 if (resultat_temp < resultat)
 {
 resultat = resultat_temp;
 for (i = 0; i < nb_etudiants; i++)
	 solution[i] = solution_temp[i];
 printf("amélio : %d\n", resultat);
 }
 
 t2 = clock();
 temps = (float)(t2 - t1) / CLOCKS_PER_SEC;
 
 if (temps > 600)
	 break;
 }
 
 printf("Solution : %d\n", resultat);
 printf("Temps    : %f secondes\n", temps);
 printf("* * * * * * * * * * * * * * * * * * * * * *\n");
*/