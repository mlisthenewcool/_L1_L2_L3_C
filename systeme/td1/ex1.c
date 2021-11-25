#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


void plus (int *x, int *y, int *z) {
	*z = *x + *y;
}

void moins (int *x, int *y, int *z) {
	*z = *x - *y;
	printf("z : %d\n", *z);
}

void fois (int *x, int *y, int *z) {
	*z = (*x) * (*y);
}

int main (int argc, char *argv[]) {
	
	/*
	printf("Saisissez le premier nombre :");
	int nb1 = scanf("%d", );
	
	printf("Saisissez le deuxième nombre :");
	int nb2 = scanf("%d");
	*/
	int nb1 = 5;
	int nb2 = 3;
	int res = 0;
	
	plus (&nb1, &nb2, &res);
	printf("Résultat plus : %d\n", res);
	
	moins (&nb1, &nb2, &res);
	printf("Résultat moins : %d\n", res);
	
	fois (&nb1, &nb2, &res);
	printf("Résultat fois : %d\n", res);
}