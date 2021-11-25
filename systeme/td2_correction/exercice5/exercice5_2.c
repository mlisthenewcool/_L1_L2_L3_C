#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUF_SIZ 100
#define TUBE_ID "tube_nomme"

int main(int argc, char* argv[]) {
	char message[BUF_SIZ];

	int fd_tube_nomme = open(TUBE_ID, O_RDONLY);
	if(fd_tube_nomme <= 0) {
		perror("Impossible d'acceder au tube nomme !\n");
		exit(1);
	}

	if(read(fd_tube_nomme, message, BUF_SIZ) > 0) {
		printf("Message reçu '%s'\n", message);
		close(fd_tube_nomme);
		exit(0);
	} else {
		perror("Erreur lors de la lecture du message\n");
		close(fd_tube_nomme);
		exit(1);
	}
}