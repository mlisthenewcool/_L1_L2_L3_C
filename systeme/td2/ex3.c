#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main (int argc, char *argv[]) {
	
	// Si l'exécution ne comporte pas le bon nombre d'arguments
	if (argc != 3) {
		printf ("Veuillez renseigner deux champs : un pour le fichier source, un pour le fichier source\n");
		exit(0);
	}
	
	// Ouverture en lecture seule du fichier source
	int fd_read = open(argv[1], O_RDONLY);
	
	// Ouverture en écriture seule du fichier cible
	int fd_write = open(argv[2], O_WRONLY);
	
	// Si le fichier source n'existe pas
	if (fd_read < 0) {
		printf("Attention, le fichier %s n'existe pas\n", argv[1]);
		exit(0);
	}
	
	// Si le fichier cible n'existe pas
	else if (fd_write < 0) {
		creat (argv[2], 0740);
		printf ("Le fichier %s a été créé par le système\n", argv[2]);
	}
	
	else {
		printf ("Les fichiers %s et %s ont été ouverts correctement\n", argv[1], argv[2]);
	}
	
	// On se place à partir du 5ème caractère
	lseek(fd_read, 90, SEEK_CUR);
	
	// On lit les caractères 5 par 5
	char buffer [5];
	int read_size = 5;
	int write_size;
	
	// Copie les caractères 5 par 5 depuis le fichier source vers le fichier cible
	do {
		read_size = read (fd_read, buffer, 5);
		//printf("%s\n", buffer);
		write_size = write (fd_write, buffer, 5);
	} while (5 == read_size);
	
	// Fermeture des fichiers
	close (argv[1]);
	close (argv[2]);
	
	// Supprime le fichier source
	//unlink (argv[1]);
	
	return 0;
}