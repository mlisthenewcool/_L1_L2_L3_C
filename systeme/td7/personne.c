#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	char prenom[30], nom[30];
	
	printf("\tSaisir le prénom : ");
	scanf("%s", prenom);
	printf("\tSaisir le nom : ");
	scanf("%s", nom);
	
	printf("\tSalut %s %s\n", prenom, nom);
}