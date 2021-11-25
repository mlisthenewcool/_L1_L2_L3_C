/**
 * PROJET GUARSSIFI CHARRON DEBERNARDI
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nim.h"

#define BUFFER_SIZE 255

/********** DEBUT MAIN **********/
int main(int argc, char **argv) 
{
	int N, M, R, Next, Niveau, nbre_voisins, rejouer = 1;
	
	srand((unsigned int) time(NULL));
	
	/* Une partie */
	while (rejouer == 1)
	{
		Lire_Parametres(&N, &M, &R, &Next, &Niveau);
		
		T_Case T_Tab_Case[R];
		
		T_Case T_Tab_Sauve[1];
		T_Case T_Voisines[4];
		
		Init_Grille(R, T_Tab_Case);
		Affiche_Grille(N, M, R, T_Tab_Case);
		
		/* Tant qu'il reste un pion */
		while(R > 0)
		{
			/* Coup de l'ordi */
			if (Next == 1)
			{
				/* Niveau 1 */
				if (Niveau == 1)
				{
					if (Hasard(10) < 9)
						Move_Hasard (N, M, &R, nbre_voisins, T_Tab_Case, T_Voisines, T_Tab_Sauve);
					else
						Move_Gagnant (N, M, &R, nbre_voisins, T_Tab_Case, T_Voisines, T_Tab_Sauve);
				}
				/* Niveau 2 */
				else if (Niveau == 2)
				{
					if (Hasard(10) < 5)
						Move_Hasard (N, M, &R, nbre_voisins, T_Tab_Case, T_Voisines, T_Tab_Sauve);
					else
						Move_Gagnant (N, M, &R, nbre_voisins, T_Tab_Case, T_Voisines, T_Tab_Sauve);
				}
				/* Niveau 3 */
				else
				{
					if (Hasard(10) == 9)
						Move_Hasard (N, M, &R, nbre_voisins, T_Tab_Case, T_Voisines, T_Tab_Sauve);
					else
						Move_Gagnant (N, M, &R, nbre_voisins, T_Tab_Case, T_Voisines, T_Tab_Sauve);
				}
				
				/* L'ordi a fini son tour, on affiche la grille et c'est au tour du joueur */
				Affiche_Grille (N, M, R, T_Tab_Case);
				Next++;
			}
			/* Coup du joueur */
			else if (Next == 2)
			{
				Move_Joueur(N, M, &R, nbre_voisins, T_Tab_Case, T_Voisines, T_Tab_Sauve);
				Affiche_Grille(N, M, R, T_Tab_Case);
				Next--;
			}
		}
		/* Il ne reste plus de pion --> Fin de la partie */
		if (R == 0)
		{
			if (Next == 2)
			{
				printf ("\t   C'EST TERMINE, TU AS PERDU !\n\n\t\tVeux-tu rejouer ?\n\t\tOui (1) Non (2) : ");
				rejouer = Lire_Entier(1, 2);
			}
			else if (Next == 1)
			{
				printf ("\t   FELICITATIONS, TU AS GAGNE !\n\n\t\tVeux-tu rejouer ?\n\t\tOui (1) Non (2) : ");
				rejouer = Lire_Entier(1, 2);
			}
		}
	}
	
	return 0;
}  
/********** FIN MAIN **********/

int Lire_Entier(int borne_inf, int borne_sup)
{
	int x, est_un_nombre;
	char temp[BUFFER_SIZE];
	
	do
	{
		do
		{
			char saisie[BUFFER_SIZE];
			fflush(stdout);
			fgets(saisie, sizeof (saisie), stdin);
			est_un_nombre = sscanf(saisie, "%[0-9-]s", temp);
			if (est_un_nombre != 1)
				printf("Erreur, veuillez saisir un entier correct : ");
		} while(est_un_nombre != 1);
		
		x = strtol (temp, NULL, 10);
		
		if (x < borne_inf || x > borne_sup)
			printf("Erreur, le nombre doit etre compris entre %i et %i : ", borne_inf, borne_sup);
	} while(x < borne_inf || x > borne_sup);
	
	return x;
}

void Lire_Parametres(int *N, int *M, int *R, int *Next, int *Niveau)
{
	printf("\n------------------------------------------------------");
	printf("\n\n\t\t**** JEU DE NIM ****\n\n");
	printf("\t   ***** Parametres du jeu *****\n\n");
	printf("------------------------------------------------------\n");
	
	printf("Nombre de lignes (compris entre 3 et 30 inclus)   : ");
	*N = Lire_Entier(3, 30);
	
	printf("Nombre de colonnes (compris entre 3 et 30 inclus) : ");
	*M = Lire_Entier(3, 30);
	
	if (*N < 10)
	{
		printf("Nombre de pions (compris entre 1 et %i inclus)     : ", *N);
		*R = Lire_Entier(1, *N);
	}
	else
	{
		printf("Nombre de pions (compris entre 1 et %i inclus)    : ", *N);
		*R = Lire_Entier(1, *N);
	}
	
	printf("Niveau (1, 2 ou 3)                                : ");
	*Niveau = Lire_Entier(1, 3);
	
	printf("\n\t\t  Qui commence ?\nL'ordinateur (1) ou le joueur (2)                 : ");
	*Next = Lire_Entier(1, 2);
	
	printf("------------------------------------------------------\n");
	printf ("\n\t\t  C'EST PARTI !\n\n");
}

void Init_Grille(int R, T_Case T_Tab_Case[])
{
	int L;
	
	for (L = 0; L < R; L++)
	{
		T_Tab_Case[L].i = L + 1;
		T_Tab_Case[L].j = 1;
	}
}

int Contient_Pion(int R, int x, int y, T_Case T_Tab_Case[])
{
	int bool = 0, k;
	/* x, y coordonnées d'un pion */
	for (k = 0; k < R; k++)
		if ((T_Tab_Case[k].i == x) && (T_Tab_Case[k].j == y)) 
			bool = 1;
	
	return bool;
}

void Affiche_Grille(int N, int M, int R, T_Case T_Tab_Case[])
{
	int x, y, c = 0;
	printf("  ");
	
	/*
	 * x --> ligne
	 * y --> colonne
	 */
	for(y = 1; y <= M; y++)
	{
		if (y < 10)
			printf("  %i ", y);
		else
			printf(" %i ", y);
	}
	
	for(x = 1; x <= N; x++)
	{
		if (x < 10)
			printf("\n%i |", x);
		else
			printf("\n%i|", x);
		
		for(y = 1; y < M + 1; y++)
		{
			if(Contient_Pion(R, x, y, T_Tab_Case) == 1)
			{
				c++;
				printf(" 0 |");
			}
			else
				printf("---|");
		}
	}
	
	printf ("\n\n");
}

int Nimber(int N, int M, int l, int c)
{
	/*
	 * l --> ligne
	 * c --> colonne
	 */
	return ((M - c) % 3) ^ ((N - l) % 3);
}

int Nim_Addition(int R, T_Case T_Tab_Case[])
{
	int x, nim_add = 0;
	
	for(x = 0; x < R; x++)
		nim_add = nim_add ^ (T_Tab_Case[x].nimber);
	
	return nim_add;
}

void Tab_Voisines (int N, int M, int l, int c, int *nbre_voisins, T_Case T_Voisines[])
{
	/*
	 * l --> ligne d'un pion
	 * c --> colonne d'un pion
	 */
	int k, compteur = 0, voisins_ligne = 0, voisins_colonne = 0; 
	
	if(N - l >= 2)
		voisins_ligne = 2;
	else if (N - l == 1)
		voisins_ligne = 1;
	if(M - c >= 2)
		voisins_colonne = 2;
	else if (M - c == 1)
		voisins_colonne = 1;
	
	for(k = 1; k < voisins_colonne + 1; k++)
	{
		T_Voisines[compteur].i = l;
		T_Voisines[compteur].j = c + k;
		compteur++;
	}
	
	for(k = 1; k < voisins_ligne + 1; k++)
	{
		T_Voisines[compteur].i = l + k;
		T_Voisines[compteur].j = c;
		compteur++;
	}
	
	*nbre_voisins = compteur;
}

int Hasard(int borne_max)
{
	return rand() % borne_max;
}

void Maj_Grille(int N, int M, int *R, int pion_choisi, int deplacement, T_Case T_Tab_Case[], T_Case T_Voisines[], T_Case T_Tab_Sauve[])
{
	T_Tab_Case[pion_choisi].i = T_Voisines[deplacement].i;
	T_Tab_Case[pion_choisi].j = T_Voisines[deplacement].j;
	T_Tab_Case[pion_choisi].nimber = Nimber(N, M, T_Tab_Case[pion_choisi].i, T_Tab_Case[pion_choisi].j); 
	T_Tab_Case[*R - 1].nimber = Nimber(N, M, T_Tab_Case[*R - 1].i, T_Tab_Case[*R - 1].j);
	
	/* Si on se trouve en case (N, M) après le coup joué */
	if((T_Tab_Case[pion_choisi].i == N) && (T_Tab_Case[pion_choisi].j == M))
	{
		T_Tab_Sauve[0].i = T_Tab_Case[*R - 1].i;
		T_Tab_Sauve[0].j = T_Tab_Case[*R - 1].j;
		T_Tab_Sauve[0].nimber = T_Tab_Case[*R - 1].nimber;
		
		T_Tab_Case[*R - 1].i = T_Tab_Case[pion_choisi].i;
		T_Tab_Case[*R - 1].j = T_Tab_Case[pion_choisi].j;
		T_Tab_Case[*R - 1].nimber = T_Tab_Case[pion_choisi].nimber;
		
		T_Tab_Case[pion_choisi].i = T_Tab_Sauve[0].i;
		T_Tab_Case[pion_choisi].j = T_Tab_Sauve[0].j;
		T_Tab_Case[pion_choisi].nimber = T_Tab_Sauve[0].nimber;
		
		*R = *R - 1;
	}
}

void Move_Joueur(int N, int M, int *R, int nbre_voisins, T_Case T_Tab_Case[], T_Case T_Voisines[], T_Case T_Tab_Sauve[])
{
	int k, q, pion_choisi, deplacement;
	
	/* On fait choisir un pion au joueur */
	printf ("\t\tA TOI DE JOUER !\n\nChoisis un pion > ");
	
	for (k = 1; k <= *R; k++)
		printf ("%i : (%i, %i) ", k, T_Tab_Case[k-1].i, T_Tab_Case[k-1].j);
	
	printf ("\n---> ");
	
	pion_choisi = Lire_Entier(1, *R) - 1;
	
	printf("Choisis la destination > ");
	
	/* Puis on lui fait choisir la destination parmi les voisines */
	Tab_Voisines (N, M, T_Tab_Case[pion_choisi].i, T_Tab_Case[pion_choisi].j, &nbre_voisins, T_Voisines);
	for (q = 0; q < nbre_voisins; q++)
		printf ("%i : (%i, %i) ", q + 1, T_Voisines[q].i, T_Voisines[q].j);
	
	printf ("\n---> ");
	
	deplacement = Lire_Entier(1, nbre_voisins) - 1;
	
	printf ("\n");
	printf("Tu as joue le pion %i : (%i,%i) en case (%i,%i)\n\n", pion_choisi + 1, T_Tab_Case[pion_choisi].i, T_Tab_Case[pion_choisi].j, T_Voisines[deplacement].i, T_Voisines[deplacement].j);
	
	/* On met à jour la grille après le coup */
	Maj_Grille (N, M, R, pion_choisi, deplacement, T_Tab_Case, T_Voisines, T_Tab_Sauve);
}

void Move_Hasard (int N, int M, int *R, int nbre_voisins, T_Case T_Tab_Case[], T_Case T_Voisines[], T_Case T_Tab_Sauve[])
{
	Tab_Voisines(N, M, T_Tab_Case[Hasard(*R)].i, T_Tab_Case[Hasard(*R)].j, &nbre_voisins, T_Voisines);
	
	printf("L'ordinateur joue le pion %i : (%i,%i) en case (%i,%i)\n\n", Hasard(*R) + 1, T_Tab_Case[Hasard(*R)].i, T_Tab_Case[Hasard(*R)].j, T_Voisines[Hasard(nbre_voisins)].i, T_Voisines[Hasard(nbre_voisins)].j);
	
	/* On met à jour la grille après le coup */
	Maj_Grille(N, M, R, Hasard(*R), Hasard(nbre_voisins), T_Tab_Case, T_Voisines, T_Tab_Sauve);
}

void Move_Gagnant(int N, int M, int *R, int nbre_voisins, T_Case T_Tab_Case[], T_Case T_Voisines[], T_Case T_Tab_Sauve[])
{
	int nimad, m, k, l, sauve1, sauve2;
	
	for(m = 0; m < *R; m++)
		T_Tab_Case[m].nimber = Nimber(N, M, T_Tab_Case[m].i, T_Tab_Case[m].j);
	
	/* On calcule la Nim_Addition de l'ensemble des pions de la partie */
	nimad = Nim_Addition(*R, T_Tab_Case);
	
	/* Si on peut jouer un coup gagnant */
	if(nimad != 0)
	{
		for(k = 0; k < *R; k++)
		{
			Tab_Voisines(N, M, T_Tab_Case[k].i, T_Tab_Case[k].j, &nbre_voisins, T_Voisines);
			
			for(l = 0; l < nbre_voisins; l++)
			{
				T_Voisines[l].nimber = Nimber(N, M, T_Voisines[l].i, T_Voisines[l].j);
				
				if(((T_Tab_Case[k].nimber) ^ nimad) == (T_Voisines[l].nimber))
				{
					sauve1 = k;
					sauve2 = l;
				}
			}
		}
		
		Tab_Voisines(N, M, T_Tab_Case[sauve1].i, T_Tab_Case[sauve1].j, &nbre_voisins, T_Voisines);
		
		printf("L'ordinateur (g) joue le pion %i : (%i,%i) en case (%i,%i)\n\n", sauve1 + 1, T_Tab_Case[sauve1].i, T_Tab_Case[sauve1].j, T_Voisines[sauve2].i, T_Voisines[sauve2].j);
		
		/* On met à jour la grille après le coup */
		Maj_Grille (N, M, R, sauve1, sauve2, T_Tab_Case, T_Voisines, T_Tab_Sauve);
	}
	
	/* Sinon on joue un coup au hasard */
	else
		Move_Hasard(N ,M, R, nbre_voisins, T_Tab_Case, T_Voisines, T_Tab_Sauve);
}