#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUF_SIZ 500

int main(int argc, char* argv[]) {
	char buffer[BUF_SIZ];

	if(mkdir("TD1", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) { //chmod 773
		printf("Impossible de creer le dossier TD1\n");
		exit(1);
	}
	printf("Le dossier TD1 a ete cree\n");

	if(link("test2.txt", "t_link")) {
		printf("Impossible de creer le lien symbolique\n");
		exit(1);
	}
	printf("Lien symbolique cree. Merci de verifier sa creation grace a un ls -l. Appuyez sur une 'ENTREE' pour continuer...\n");
	getchar();

	if(unlink("t_link")) {
		printf("Impossible de supprimer le lien symbolique\n");
		exit(1);	
	}
	printf("Lien symbolique supprime !\n");

	if(chdir("TD1")) {
		printf("Impossible de se rendre dans le repertoire TD1\n");
		exit(1);
	}
	getcwd(buffer, BUF_SIZ);
	printf("Changement de repertoire reussi ! [nouveau repertoire = %s]\n", buffer);

	if(creat("test_td1", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0) {
		printf("Impossible de creer le fichier test_td1\n");
		exit(1);
	}
	printf("Fichier test_td1 cree !\n");

	if(chdir("..")) {
		printf("Impossible de se rendre dans le repertoire parent\n");
		exit(1);
	}
	getcwd(buffer, BUF_SIZ);
	printf("Changement de repertoire reussi ! [nouveau repertoire = %s]\n", buffer);

	if(rmdir("TD1")) {
		//Erreur normale : le repertoire n'est pas vide !
		//Pour supprimer le repertoire TD1, il faut tout d'abord supprimer le fichier test_td1 qu'il contient
		printf("Impossible de supprimer le repertoire TD1\n");
		exit(1);
	}
	printf("Repertoire TD1 supprime !\n");

	exit(0);
}