#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUF_SIZ 100
#define TUBE_ID "tube_nomme"

int main(int argc, char* argv[]) {
	char message[BUF_SIZ];

	if(mkfifo(TUBE_ID, 0644) != 0) {
		perror("Une erreur est survenue lors de la creation du tube nomme\n");
		exit(1);
	}

	int fd_tube_nomme = open(TUBE_ID, O_WRONLY);
	if(fd_tube_nomme <= 0) {
		perror("Impossible d'acceder au tube nomme !\n");
		exit(1);
	}

	printf("Saisissez votre message...\n");
	scanf("%s", message);

	if(write(fd_tube_nomme, message, BUF_SIZ) > 0) {
		printf("Message envoye '%s'!\n", message);
		close(fd_tube_nomme);
		unlink(TUBE_ID);
		exit(0);
	}
	
	else {
		perror("Erreur lors de l'ecriture du message\n");
		close(fd_tube_nomme);
		exit(1);
	}
}