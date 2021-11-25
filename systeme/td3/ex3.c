#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *entiers;
	int taille;
	int x;
} tableau;

void *thread1 (void *arg) {
	tableau *temp = (tableau*) arg;
	
	int i;
	for (i = 0; i < temp->taille ; i++) {
		temp->entiers[i] = rand() % 5 + 1;
		sleep(0);
	}

	pthread_exit(NULL);
}

void *thread2 (void *arg) {
	tableau *temp = (tableau*) arg;
	
	int i;
	for (i = 0; i < temp->taille ; i++) {
		printf ("%d\n", temp->entiers[i]);
		sleep(1);
	}
	
	pthread_exit(NULL);
}

int main (int argc, char argv[]) {
	
	srand((unsigned int)time(NULL));
	tableau t;
	printf ("Veuillez saisir la taille du tableau : ");
	scanf("%d", &(t.taille));
	
	t.entiers = malloc(t.taille * sizeof(int));
	
	int i;
	for (i = 0; i < t.taille; i++) {
		t.entiers[i] = 0;
	}
	
	pthread_t my_thread1, my_thread2;
	
	int ret1 = pthread_create (&my_thread1, NULL, thread1, (void*) &t);
	int ret2 = pthread_create (&my_thread2, NULL, thread2, (void*) &t);
	
	pthread_join(my_thread1, NULL);
	pthread_join(my_thread2, NULL);
}