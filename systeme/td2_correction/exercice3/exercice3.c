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
	if(argc != 2) {
		printf("Utilisation de la commande %s :\n", argv[0]);
		printf("%s <fichier source>\n", argv[0]);
		exit(1);
	} else {
		char* nom_fichier_source = argv[1];
		char buffer[BUF_SIZ];
		int fd_source, position_initiale = 15, nombre_a_lire = 10, taille_lu;
		
		fd_source = open(nom_fichier_source, O_RDONLY);
		if(fd_source != -1) {
			if(lseek(fd_source, position_initiale, SEEK_SET) == position_initiale) {
				if((taille_lu = read(fd_source, buffer, nombre_a_lire)) > 0) {
					buffer[taille_lu] = '\0';
					printf("Le programme a lu :\n%s\n", buffer);
				} else {
					printf("Rien a lire apres la position n°%d\n", position_initiale);
					close(fd_source);
					exit(0);
				}
			} else {
				printf("Impossible de placer la tete de lecture a la position n°%d du fichier\n", position_initiale);
				close(fd_source);
				exit(1);
			}

		} else {
			printf("Erreur lors de l'ouverture du fichier source '%s'\n", nom_fichier_source);
			exit(1);
		}
	}
}