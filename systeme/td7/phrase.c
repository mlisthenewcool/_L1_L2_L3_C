#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if (argc < 2)
		printf("Usage : ./phrase entrez votre phrase...\n");
	
	else
		printf("Phrase : %s\n", argv[1]);
}