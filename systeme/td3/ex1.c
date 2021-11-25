#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *tab;
} tableau;

void *init_thread (void *arg) {
	
	tableau *temp = (tableau*) arg;
	
	int i;	
	for (i = 0; i < 20; i++)
		printf ("%d\n", temp->tab[i]);

	pthread_exit(NULL);
}

int main (int argc, char argv[]) {
	
	srand((unsigned int)time(NULL));
	tableau t;
	int size;
	
	printf("Choisir la taille du tableau : ");
	scanf("%d", &size);
	
	t.tab = malloc(size * sizeof(int));
	
	int i;
	for (i = 0; i < size ; i++) {
		t.tab[i] = rand() % 100 + 1;
	}
	
	pthread_t my_thread1;
	int ret = pthread_create (&my_thread1, NULL, init_thread, (void*) &t);
	
	if (ret == -1)
		printf("Une erreur est survenue lors de la création du thread\n");
	else
		printf("Thread créé\n");
	
	pthread_join(my_thread1, NULL);
}