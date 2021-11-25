/**
 * Header pour nim.c
 */ 

typedef struct
{
	int i, j, nimber; /* Ligne, colonne, nimber */
} T_Case;

void Lire_Parametres (int *N, int *M, int *R, int *Next, int *Niveau);

int Lire_Entier (int borne_inf, int borne_sup);

void Init_Grille (int R, T_Case T_Tab_Case[]);

int Contient_Pion (int R, int x, int y, T_Case T_Tab_Case[]);

void Affiche_Grille (int N, int M, int R, T_Case T_Tab_Case[]);

int Nimber (int N, int M, int l, int c);

int Nim_Addition (int R, T_Case T_Tab_Case[]);

void Tab_Voisines (int N, int M, int l, int c, int *nbre_voisins, T_Case T_Voisine[]);

int Hasard (int borne_max);

void Maj_Grille (int N, int M, int *R, int pion_choisi, int deplacement, T_Case T_Tab_Case[], T_Case T_Voisines[], T_Case T_Tab_Sauve[]);

void Move_Joueur (int N, int M, int *R, int nbre_voisins, T_Case T_Tab_Case[], T_Case T_Voisines[], T_Case T_Tab_Sauve[]);

void Move_Hasard (int N, int M, int *R, int nbre_voisins, T_Case T_Tab_Case[], T_Case T_Voisines[], T_Case T_Tab_Sauve[]);

void Move_Gagnant (int N, int M, int *R, int nbre_voisins, T_Case T_Tab_Case[], T_Case T_Voisines[], T_Case T_Tab_Sauve[]);