#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main (int argc, char *argv[]) {
	if (mkfifo(argv[1], 0644) != 0) {
		perror("mkfifo");
		exit(1);
	}
	
	char message[10];
	scanf ("%s", message);
	
	int fd = open(argv[1], O_WRONLY);
	
	sleep(1);
	printf("Ouverture\n");
	int write_size = write (fd, message, 10);
	printf("Continue\n");
	
	close (fd);
}