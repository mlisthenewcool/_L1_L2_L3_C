#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	//Create d'un fichie test2.txt dans le repertoire courant
	//S_IRUSR : permission en lecture pour le proprietaire
	//S_IWUSR : permission en ecriture pour le proprietaire
	//S_IRGRP : permission en lecture pour le groupe
	//S_IROTH : permission en lecture pour les autres
	//------------------------------------------------------
	//droits : 622
	int test_creat=creat("test2.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	//int test_creat=creat("test2.txt", 0622);
	if(test_creat<0) {
		printf("Attention Impossible de créer le fichier\n");
		exit(0);
	}
	
	//Ouverture en lecture du fichier "test1.txt"
	int descripteur_fichier1 = open("test1.txt", O_RDONLY);
	if(descripteur_fichier1<0) {
		printf("Attention Impossible d'ouvrir le fichier\n");
		exit(0);
	}
	//Ouverture en ecriture du fichier "test2.txt"
	int descripteur_fichier2 = open("test2.txt", O_WRONLY);
	if(descripteur_fichier2<0) {
		printf("Attention Impossible d'ouvrir le fichier\n");
		exit(0);
	}
	//lecture des 10 premiers caracteres du fichier "text1.txt"
	unsigned char nombre_caracteres = 10;
	char buffer_fichier1[nombre_caracteres];
	int size_read = read(descripteur_fichier1, buffer_fichier1, nombre_caracteres);
	if(size_read<0) {
		printf("Attention problème de lecture\n");
		exit(0);
	}
	if(size_read == nombre_caracteres) {
		//Ecriture dans le second fichier
		int size_wrote = write(descripteur_fichier2, buffer_fichier1, nombre_caracteres);
		if(size_wrote != nombre_caracteres) {
			printf("Erreur lors de l'ecriture");
			exit(1);
		}
		//Fermeture du second fichier
		close(descripteur_fichier2);
		//Renommage : test2.txt -> test3.txt
		int test_rename=rename("test2.txt", "test3.txt");
		if(test_rename<0) {
			printf("Attention problème de lecture\n");
			exit(0);
		}
		//Suppression du premier fichier
		unlink("test1.txt");
	} else {
		close(descripteur_fichier1);
		printf("Erreur lors de la lecture du fichier");
		exit(1);
	}
	close(descripteur_fichier1);
	exit(0);
}
