#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main (int argc, char *argv[]) {
	
	char fichier1[] = "test1.txt";
	char fichier2[] = "test2.txt";
	
	// Créer un fichier test2.txt
	creat(fichier1, 0740);
	
	// Ouverture
	int fd_read = open(fichier1, O_RDONLY);
	int fd_write = open(fichier2, O_WRONLY);
	
	char buffer[10];
	
	// Lecture
	int read_size = read (fd_read, buffer, 10);
	
	// Ecriture
	int write_size = write (fd_write, buffer, 10);
	
	// Fermeture
	close (fd_read);
	close (fd_write);
	
	// Renommer
	rename (fichier2, "test3.txt");
	
	// Supprimer
	unlink (fichier1);
}