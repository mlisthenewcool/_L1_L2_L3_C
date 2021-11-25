#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define NB_CLIENTS 100
#define NB_CASES_PANNEAU 1000
#define NB_PLACES_PANNEAU 10
#define VALEUR_MIN_CASE_PANNEAU 0
#define VALEUR_MAX_CASE_PANNEAU 256
#define TEMPS_ATTENTE_MIN_CLIENT 1
#define TEMPS_ATTENTE_MAX_CLIENT 20
#define TEMPS_LECTURE_CLIENT_MIN 3
#define TEMPS_LECTURE_CLIENT_MAX 10

/******************************************************************************
* Pour compiler ce programme, il est necessaire d'utiliser l'option -lpthread *
* ex : gcc exercice1.c -o exercice1 -lpthread                                 *
******************************************************************************/

pthread_mutex_t mutex_compteur_clients; //verrou pour le compteur client (utilise pour chaque client dispose d'un numero unique)
int compteur_client; //compteur client (utilise pour chaque client dispose d'un numero unique)
sem_t semaphore_panneau; //semaphore utilisé pour limiter le nombre de places devant le panneau

typedef struct {
	int places[NB_CASES_PANNEAU];
} panneau_affichage;

//Retourne un nombre entier aleatoire compris dans l'interval [min, max[
int alea_entre_bornes(int min, int max) {
	return (rand() % (min - max)) + min;
}

void* fct_thread_client(void* arg) {
	int mon_identifiant;
	int position_case_a_lire;
	int valeur_lu;

	panneau_affichage* panneau = (panneau_affichage*) arg;
	
	pthread_mutex_lock(&mutex_compteur_clients);
	mon_identifiant = compteur_client++;
	pthread_mutex_unlock(&mutex_compteur_clients);

	while(1) {
		sleep(alea_entre_bornes(TEMPS_ATTENTE_MIN_CLIENT, TEMPS_ATTENTE_MAX_CLIENT + 1));
		position_case_a_lire = alea_entre_bornes(0, NB_CASES_PANNEAU);
		sem_wait(&semaphore_panneau);
		printf("Client n°%d\t\t : \"Je lis la case n°%d du tableau\"\n", mon_identifiant, position_case_a_lire);
		sleep(alea_entre_bornes(TEMPS_LECTURE_CLIENT_MIN, TEMPS_LECTURE_CLIENT_MAX));
		printf("Client n°%d\t\t : \"La case n°%d est égale à %d\"\n", mon_identifiant, position_case_a_lire, panneau->places[position_case_a_lire]);
		sem_post(&semaphore_panneau);
	}
}

int main(int argc, char* argv[]) {
	panneau_affichage panneau;
	pthread_t clients[NB_CLIENTS];
	int position;

	srand(time(NULL));
	compteur_client = 0;
	for(position = 0; position < NB_CASES_PANNEAU; position++) {
		panneau.places[position] = alea_entre_bornes(VALEUR_MIN_CASE_PANNEAU, VALEUR_MAX_CASE_PANNEAU);
	}

	if(pthread_mutex_init(&mutex_compteur_clients, NULL) != 0) {
        perror("Impossible d'initialiser le verrou d'exclusion mutuelle du compteur client !\n");
        exit(EXIT_FAILURE);
    }

	if(sem_init(&semaphore_panneau, 0, NB_PLACES_PANNEAU) != 0) {
        perror("Impossible d'initialiser le semaphore du panneau d'affichage !\n");
        exit(EXIT_FAILURE);
    }	

	//Lancement des threads
    printf("Lancement des threads clients...\n");
    for(position = 0; position < NB_CLIENTS; position++) {
        if(pthread_create(clients + position, NULL, fct_thread_client, (void*)& panneau)) {
            perror("Impossible de creer un des threads client\n");
            exit(EXIT_FAILURE);
        }
    }
	printf("\t-> OK !\n");

    //Attente des threads
    printf("Attente des threads clients...\n");
    for(position = 0; position < NB_CLIENTS; position++) {
        pthread_join(clients[position], NULL);
    }
    printf("Programme termine...\n");
    exit(0);
}
