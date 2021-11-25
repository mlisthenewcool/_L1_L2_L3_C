#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

void plus(int* pA, int* pB, int* pResultat) {
	//On ecrit dans la variable pointee par le pointeur resultat
	//le resultat de l'operation (contenu de la variable pointee par a) + (contenue de la variable pointee par b)
	*pResultat = *pA + *pB;
}


void moins(int* pA, int* pB, int* pResultat) {
	//On ecrit dans la variable pointee par le pointeur resultat
	//le resultat de l'operation (contenu de la variable pointee par a) - (contenue de la variable pointee par b)
	*pResultat = *pA - *pB;
}


void fois(int* pA, int* pB, int* pResultat) {	
	//On ecrit dans la variable pointee par le pointeur resultat
	//le resultat de l'operation (contenu de la variable pointee par a) * (contenue de la variable pointee par b)
	*pResultat = *pA * *pB;
}

int main(int argc, char* argv[]) {
	int x = 2;
	int y = 3;
	int z;

	//Test de l'addition
	//Attention : passage des arguments par reference !
	plus(&x, &y, &z);
	printf("%d + %d = %d\n", x, y, z);

	//Test de la soustraction
	//Passage des arguments par reference !
	moins(&x, &y, &z);
	printf("%d - %d = %d\n", x, y, z);


	//Test de la multiplication
	//Passage des arguments par reference !
	fois(&x, &y, &z);
	printf("%d * %d = %d\n", x, y, z);

	return 0;
}
