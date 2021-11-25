#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if (argc != 3)
		printf("Usage : ./ex5.c nom prénom\n");
	
	else
		printf("Nom : %s || Prénom : %s\n", argv[1], argv[2]);
}