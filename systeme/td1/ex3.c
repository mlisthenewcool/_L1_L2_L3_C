#include <stdio.h>

typedef struct {
	int x;
	int y;
	int z;
}coordonnees;

void initialise (coordonnees *la) {
	la->x = 10;
	la->y = 5;
	la->z = 2;
}

void afficher (coordonnees *la) {
	printf("Coordonnées de la structure : x = %d, y = %d, z = %d\n", la->x, la->y, la->z);
}

void plus (coordonnees *la) {
	la->z = la->x + la->y;
	afficher (la);
}

void moins (coordonnees *la) {
	la->z = la->x - la->y;
	afficher (la);
}

void fois (coordonnees *la) {
	la->z = la->x * la->y;
	afficher (la);
}

int main (int argc, char *argv[]) {
	coordonnees ici;
	
	initialise(&ici);
	afficher (&ici);
	plus(&ici);
}