#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *entiers;
	int taille;
	int x;
} tableau;

pthread_mutex_t mutex;

void *thread1 (void *arg) {	
	tableau *temp = (tableau*) arg;
	
	int i;
	for (i = 0; i < temp->taille ; i++) {
		pthread_mutex_lock(&mutex);
		temp->entiers[i] = rand() % 5 + 1;
		// Pour vérifier que le mutex fonctionne, l'exécution ne doit permettre
		// l'affichage du tableau qu'une fois ce dernier rempli de valeurs aléatoires
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}

	pthread_exit(NULL);
}

void *thread2 (void *arg) {
	tableau *temp = (tableau*) arg;
	
	int i;
	for (i = 0; i < temp->taille ; i++) {
		pthread_mutex_lock(&mutex);
		printf ("%d\n", temp->entiers[i]);
		pthread_mutex_unlock(&mutex);
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
	
	pthread_mutex_init(&mutex, NULL);
	
	int ret1 = pthread_create (&my_thread1, NULL, thread1, (void*) &t);
	int ret2 = pthread_create (&my_thread2, NULL, thread2, (void*) &t);
	
	pthread_join(my_thread1, NULL);
	pthread_join(my_thread2, NULL);
}