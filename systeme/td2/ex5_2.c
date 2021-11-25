#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main (int argc, char *argv[]) {
	
	printf ("Avant ouverture du fichier");
	sleep(1);
	
	int fd = open ("fichier.tube", O_RDONLY);
	sleep(1);
	printf("Ouverture\n");
	
	char buffer[10];
	int read_size = read(fd, buffer, 10);
	
	printf ("%s", buffer);
	close (fd);
}