#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex;
int compteur = 1;

typedef struct {
	int *entiers;
	int size;
	int x;
} tab;

void tri_tab (tab *a_trier) {
	int i;
	for (i = 0; i < a_trier->size; i++) {
		printf("%d\t", a_trier->entiers[i]);
	}
	printf("\n");
}

void *thread (void *arg) {
	tab *temp = (tab*) arg;
	
	// int id = pthread_self();
	temp->x = compteur++;
	printf("Thread N°%d\n", temp->x);
	
	tri_tab(temp);

	pthread_exit(NULL);
}

int main (int argc, char argv[]) {
	
	srand((unsigned int)time(NULL));
	tab t;
	printf ("Veuillez saisir la taille du tableau : ");
	scanf("%d", &t.size);
	
	int nb_valeurs;
	printf ("Veuillez saisir le nombre de threads : ");
	scanf("%d", &nb_valeurs);
	
	t.entiers = malloc(t.size * sizeof(int));
	
	int i;
	for (i = 0; i < t.size; i++) {
		t.entiers[i] = rand() % 10 + 1;
		printf("%d\t", t.entiers[i]);
	}
	printf("\n");
	
	pthread_t my_thread;
	pthread_mutex_init(&mutex, NULL);
	
	for (i = 0; i < nb_valeurs; i++) {
		sleep(1);
		int ret = pthread_create (&my_thread, NULL, thread, (void*) &t);
	}
	
	pthread_join(my_thread, NULL);
}