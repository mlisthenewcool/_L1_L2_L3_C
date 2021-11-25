#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUF_SIZ 100

/*
* argc : 1 + nombre d'arguments passés à la commande
* argv : liste des arguments passés à la commande 
* /!\ argv[0] = <nom de la commande>
*/
int main(int argc, char* argv[]) {
	if(argc != 3) {
		printf("Utilisation de la commande %s :\n", argv[0]);
		printf("%s <fichier source> <fichier cible>\n", argv[0]);
		exit(1);
	} else {
		char* nom_fichier_source = argv[1];
		char* nom_fichier_cible = argv[2];
		char buffer[BUF_SIZ];
		int fd_source, fd_cible, taille_lu;
		
		//Ouverture du fichier source
		fd_source = open(nom_fichier_source, O_RDONLY);
		if(fd_source<0) {
			printf("Attention Impossible d'ouvrir le fichier\n");
			exit(0);
		}
		if(fd_source != -1) {
			//Creation du second fichier
			int test_creat=creat(nom_fichier_cible, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			if(test_creat<0) {
				printf("Attention Impossible d'ouvrir le fichier\n");
				exit(0);
			}
			//Ouverture du fichier cible
			fd_cible = open(nom_fichier_cible, O_WRONLY);
			if(fd_cible != -1) {
				//Tant que l'on reussi a lire au mois BUF_SIZ caractere du fichier source,
				//on les ecrit dans le fichier cible
				//Lorsque l'on ne parvient plus a lire au moins BUF_SIZ caracteres, c'est que l'on a atteint la fin du fichier...
				do {
					taille_lu = read(fd_source, buffer, BUF_SIZ);
					if(taille_lu > 0) {
						write(fd_cible, buffer, taille_lu);
					}
				} while(taille_lu >= BUF_SIZ);
				//Fermeture des fichier et suppression du fichier source
				close(fd_source);
				close(fd_cible);
				unlink(nom_fichier_source);
			} else {
				printf("Erreur lors de l'ouverture du fichier cible '%s'\n", nom_fichier_source);
				close(fd_source);
				exit(1);
			}
		} else {
			printf("Erreur lors de l'ouverture du fichier source '%s'\n", nom_fichier_source);
			exit(1);
		}
	}
}