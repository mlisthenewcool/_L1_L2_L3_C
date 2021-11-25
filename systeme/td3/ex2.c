#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int var;
} tableau;

void *thread1 (void *arg) {
	tableau *temp = (tableau*) arg;
	
	temp->var +=4;
	printf ("valeur (thread 1) : %d\n", temp->var); 

	pthread_exit(NULL);
}

void *thread2 (void *arg) {
	tableau *temp = (tableau*) arg;
	
	temp->var = temp->var / 2;
	printf ("valeur (thread 2) : %d\n", temp->var); 
	
	pthread_exit(NULL);
}

void *thread3 (void *arg) {
	tableau *temp = (tableau*) arg;
	
	temp->var = temp->var * 4;
	printf ("valeur (thread 3) : %d\n", temp->var); 
	
	pthread_exit(NULL);
}

void *thread4 (void *arg) {
	tableau *temp = (tableau*) arg;
	
	temp->var = temp->var - 5;
	printf ("valeur (thread 4) : %d\n", temp->var); 
	
	pthread_exit(NULL);
}

int main (int argc, char argv[]) {
	
	tableau t;
	t.var = 10;
	
	pthread_t my_thread1, my_thread2, my_thread3, my_thread4;
	
	int ret1 = pthread_create (&my_thread1, NULL, thread1, (void*) &t);
	int ret2 = pthread_create (&my_thread2, NULL, thread2, (void*) &t);
	int ret3 = pthread_create (&my_thread3, NULL, thread3, (void*) &t);
	int ret4 = pthread_create (&my_thread4, NULL, thread4, (void*) &t);
	
	/*
	if (ret1 == -1)
		printf("Une erreur est survenue lors de la création du thread\n");
	else
		printf("Thread créé\n");
	*/
	
	pthread_join(my_thread1, NULL);
	pthread_join(my_thread2, NULL);
	pthread_join(my_thread3, NULL);
	pthread_join(my_thread4, NULL);
}