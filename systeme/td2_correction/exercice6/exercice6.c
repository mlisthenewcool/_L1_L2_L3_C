#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define BUF_SIZ 100
#define TUBE_ID "tube_nomme"

int lire(int fd_tube_nomme) {
	char message[BUF_SIZ];
	if(read(fd_tube_nomme, message, BUF_SIZ) > 0) {
		printf("<---[received]---(%s)\n", message);
		return 0;
	}
	return 1;
}

int ecrire(int fd_tube_nomme) {
	char message[BUF_SIZ];
	printf("Saisissez votre message puis appuyez sur 'ENTREE' pour l'envoyer ('--sortir--' permet de fermer le programme)...\n");
	fgets(message, BUF_SIZ, stdin); //utilisation de fgets pour capturer les espaces
	if ((strlen(message)>0) && (message[strlen (message) - 1] == '\n')) {
        message[strlen (message) - 1] = '\0';
	}
	if(strcmp(message, "--sortir--") == 0) {
		return 2;
	}
	if(write(fd_tube_nomme, message, BUF_SIZ) > 0) {
		printf("---[send]--->(%s)\n", message);
		return 0;
	}
	return 1;
}

void prio(char* tube_id_1_2, char* tube_id_2_1) {
	if(mkfifo(tube_id_1_2, 0644) != 0) {
		perror("Une erreur est survenue lors de la creation du premier tube nomme\n");
		exit(1);
	}
	int fd_tube_nomme_1_2, fd_tube_nomme_2_1, statut;
	fd_tube_nomme_1_2 = open(tube_id_1_2, O_WRONLY);
	if(fd_tube_nomme_1_2 <= 0) {
		perror("Impossible d'acceder au tube nomme !\n");
		exit(1);
	}
	fd_tube_nomme_2_1 = open(tube_id_2_1, O_RDONLY);
	if(fd_tube_nomme_2_1 <= 0) {
		perror("Impossible d'acceder au tube nomme !\n");
		close(fd_tube_nomme_1_2);
		unlink(tube_id_1_2);
		exit(1);
	}
	do {
		statut = ecrire(fd_tube_nomme_1_2); 
		switch (statut) 	{
			case 1 :
				perror("Erreur lors de l'ecriture!\n");
				close(fd_tube_nomme_1_2);
				close(fd_tube_nomme_2_1);
				unlink(tube_id_1_2);
				exit(1);
			case 2 :
				perror("Fin du programme !\n");
				close(fd_tube_nomme_1_2);
				close(fd_tube_nomme_2_1);
				unlink(tube_id_1_2);
				exit(0);
		}
		if(lire(fd_tube_nomme_2_1) == 1) {
			perror("Erreur lors de la lecture !\n");
			close(fd_tube_nomme_1_2);
			close(fd_tube_nomme_2_1);
			unlink(tube_id_1_2);
			exit(1);
		}
	} while(1);
}

void classique(char* tube_id_1_2, char* tube_id_2_1) {
	if(mkfifo(tube_id_2_1, 0644) != 0) {
		perror("Une erreur est survenue lors de la creation du premier tube nomme\n");
		exit(1);
	}
	int fd_tube_nomme_1_2, fd_tube_nomme_2_1, statut;
	fd_tube_nomme_1_2 = open(tube_id_1_2, O_RDONLY);
	if(fd_tube_nomme_1_2 <= 0) {
		perror("Impossible d'acceder au tube nomme !\n");
		exit(1);
	}
	fd_tube_nomme_2_1 = open(tube_id_2_1, O_WRONLY);
	if(fd_tube_nomme_2_1 <= 0) {
		perror("Impossible d'acceder au tube nomme !\n");
		close(fd_tube_nomme_1_2);
		unlink(tube_id_2_1);
		exit(1);
	}
	do {
		if(lire(fd_tube_nomme_1_2) == 1) {
			perror("Erreur lors de la lecture !\n");
			close(fd_tube_nomme_1_2);
			close(fd_tube_nomme_2_1);
			unlink(tube_id_2_1);
			exit(1);
		}
		statut = ecrire(fd_tube_nomme_2_1);
		switch (statut) 	{
			case 1 :
				perror("Erreur lors de l'ecriture!\n");
				close(fd_tube_nomme_1_2);
				close(fd_tube_nomme_2_1);
				unlink(tube_id_2_1);
				exit(1);
			case 2 :
				perror("Fin du programme !\n");
				close(fd_tube_nomme_1_2);
				close(fd_tube_nomme_2_1);
				unlink(tube_id_2_1);
				exit(0);
		}
	} while(1);
}

int main(int argc, char* argv[]) {
	if(argc != 4) {
		printf("Utilisation de la commande %s :\n", argv[0]);
		printf("%s <ordre> <nom_tube_1> <nom_tube_2>\n", argv[0]);
		printf("ordre = 1 ou 2 : 1 indique que le programme est lance en premier (c'est lui qui devra creer le tube nomme et qui ecrira en premier dedans !) \n");
		printf("nom_tube_[1|2] : nom des tubes nommes) \n");
		exit(1);
	} else {
		char* tube_id_1_2 = argv[2];
		char* tube_id_2_1 = argv[3];
		if(strcmp(tube_id_1_2, tube_id_2_1) == 0) {
			perror("Les deux tubes doivent avoir des noms differents !\n");
			exit(1);
		}
		if(strcmp(argv[1], "1") == 0) {
			//Mode prioritaire
			printf("Programme lance en mode prioritaire\n");
			prio(tube_id_1_2, tube_id_2_1);
		} else {
			printf("Programme lance en mode classique\n");
			classique(tube_id_1_2, tube_id_2_1);
		}
	}
}