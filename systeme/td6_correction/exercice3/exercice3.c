#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define NB_CLIENTS 50
#define NB_PANNEAUX 5
#define NB_CASES_PANNEAU 1000
#define NB_PLACES_PANNEAU_MIN 10
#define NB_PLACES_PANNEAU_MAX 20
#define VALEUR_MIN_CASE_PANNEAU 0
#define VALEUR_MAX_CASE_PANNEAU 256
#define TEMPS_ATTENTE_MIN_CLIENT 10
#define TEMPS_ATTENTE_MAX_CLIENT 20
#define TEMPS_ATTENTE_MIN_COLLEUR_AFFICHES 5
#define TEMPS_ATTENTE_MAX_COLLEUR_AFFICHES 10
#define TEMPS_LECTURE_CLIENT_MIN 0
#define TEMPS_LECTURE_CLIENT_MAX 2
#define TEMPS_CHANGEMENT_AFFICHES_MIN 3
#define TEMPS_CHANGEMENT_AFFICHES_MAX 7

/******************************************************************************
* Pour compiler ce programme, il est necessaire d'utiliser l'option -lpthread *
* ex : gcc exercice1.c -o exercice1 -lpthread                                 *
******************************************************************************/

pthread_mutex_t mutex_compteur_clients; //verrou pour le compteur client (utilise pour chaque client dispose d'un numero unique)
int compteur_client; //compteur client (utilise pour chaque client dispose d'un numero unique)
sem_t semaphore_panneau[NB_PANNEAUX]; //semaphores utilisés pour limiter le nombre de places devant le panneau

typedef struct {
	int places[NB_CASES_PANNEAU];
	int nb_places;
} panneau_affichage;

//Retourne un nombre entier aleatoire compris dans l'interval [min, max[
int alea_entre_bornes(int min, int max) {
	return (rand() % (min - max)) + min;
}

void initialise_panneau(panneau_affichage* panneau) {
	int position;
	for(position = 0; position < NB_CASES_PANNEAU; position++) {
		(panneau->places)[position] = alea_entre_bornes(VALEUR_MIN_CASE_PANNEAU, VALEUR_MAX_CASE_PANNEAU);
	}
}

void* fct_thread_client(void* arg) {
	int mon_identifiant;
	int panneau_a_lire;
	int position_case_a_lire;
	int valeur_lu;

	panneau_affichage* panneaux = (panneau_affichage*) arg;
	
	pthread_mutex_lock(&mutex_compteur_clients);
	mon_identifiant = compteur_client++;
	pthread_mutex_unlock(&mutex_compteur_clients);

	while(1) {
		sleep(alea_entre_bornes(TEMPS_ATTENTE_MIN_CLIENT, TEMPS_ATTENTE_MAX_CLIENT + 1));
		panneau_a_lire = alea_entre_bornes(0, NB_PANNEAUX);
		position_case_a_lire = alea_entre_bornes(0, NB_CASES_PANNEAU);
		sem_wait(&semaphore_panneau[panneau_a_lire]);
		printf("Client n°%d\t\t : \"Je lis la case n°%d du panneau n°%d\"\n", mon_identifiant, position_case_a_lire, panneau_a_lire);
		sleep(alea_entre_bornes(TEMPS_LECTURE_CLIENT_MIN, TEMPS_LECTURE_CLIENT_MAX));
		printf("Client n°%d\t\t : \"La case n°%d du panneau %d est égale à %d\"\n", mon_identifiant, position_case_a_lire, panneau_a_lire, (panneaux + panneau_a_lire)->places[position_case_a_lire]);
		sem_post(&semaphore_panneau[panneau_a_lire]);
	}
}

void* fct_thread_colleur_affiche(void* arg) {
	int numero_panneau, position;
	panneau_affichage* panneaux = (panneau_affichage*) arg;

	while(1) {
		sleep(alea_entre_bornes(TEMPS_ATTENTE_MIN_COLLEUR_AFFICHES, TEMPS_ATTENTE_MAX_COLLEUR_AFFICHES + 1));		
		for(numero_panneau = 0; numero_panneau < NB_PANNEAUX; numero_panneau++) {
			printf("Colleur d'affiches\t : \"Je vais changer les affiches du panneau n°%d....\"\n", numero_panneau);
			//Reservation des places
			for(position = 0; position < (panneaux + numero_panneau)->nb_places; position++) {
				printf("Colleur d'affiches\t : Reservation de la place n°%d du panneau n°%d....\n", position, numero_panneau);
				sem_wait(&semaphore_panneau[numero_panneau]);
				printf("Colleur d'affiches\t : Place n°%d du panneau n°%d reservee....\n", position, numero_panneau);
			}

			printf("Colleur d'affiches\t : Changement des affiches du panneau n°%d en cours....\n", numero_panneau);
			sleep(alea_entre_bornes(TEMPS_CHANGEMENT_AFFICHES_MIN, TEMPS_CHANGEMENT_AFFICHES_MAX));
			initialise_panneau(&panneaux[numero_panneau]);
			printf("Colleur d'affiches\t : Changement des affiches du panneau n°%d terminé !\n", numero_panneau);

			//Liberation des places
			for(position = 0; position < (panneaux + numero_panneau)->nb_places; position++) {
				printf("Colleur d'affiches\t : Liberation de la place n°%d du panneau n°%d....\n", position, numero_panneau);
				sem_post(&semaphore_panneau[numero_panneau]);
				printf("Colleur d'affiches\t : Place n°%d du panneau n°%d liberee....\n", position, numero_panneau);
			}
		}
	}
}

int main(int argc, char* argv[]) {
	panneau_affichage panneaux[NB_PANNEAUX];
	pthread_t clients[NB_CLIENTS];
	pthread_t colleur_affiche;
	int position;

	srand(time(NULL));
	compteur_client = 0;

	for(position = 0; position < NB_PANNEAUX; position++) {
		initialise_panneau(&panneaux[position]);
		panneaux[position].nb_places = alea_entre_bornes(NB_PLACES_PANNEAU_MIN, NB_PLACES_PANNEAU_MAX);
		if(sem_init(&semaphore_panneau[position], 0, panneaux[position].nb_places) != 0) {
	        perror("Impossible d'initialiser le semaphore d'un des panneaux d'affichage !\n");
	        exit(EXIT_FAILURE);
	    }	
	}

	if(pthread_mutex_init(&mutex_compteur_clients, NULL) != 0) {
        perror("Impossible d'initialiser le verrou d'exclusion mutuelle du compteur client !\n");
        exit(EXIT_FAILURE);
    }

	//Lancement des threads
	printf("Lancement du thread du colleur d'affiches...\n");
    if(pthread_create(&colleur_affiche, NULL, fct_thread_colleur_affiche, (void*) &panneaux)) {
        perror("Impossible de creer le thread du colleur d'affiches\n");
        exit(EXIT_FAILURE);
    }
	printf("\t-> OK !\n");

    printf("Lancement des threads clients...\n");
    for(position = 0; position < NB_CLIENTS; position++) {
        if(pthread_create(clients + position, NULL, fct_thread_client, (void*) &panneaux)) {
            perror("Impossible de creer un des threads client\n");
            exit(EXIT_FAILURE);
        }
    }
	printf("\t-> OK !\n");

    //Attente des threads
    printf("Attente du threads du colleur d'affiches...\n");
    pthread_join(colleur_affiche, NULL);
	printf("\t-> OK !\n");

    printf("Attente des threads clients...\n");
    for(position = 0; position < NB_CLIENTS; position++) {
        pthread_join(clients[position], NULL);
    }
	printf("\t-> OK !\n");

    printf("Programme termine...\n");
    exit(EXIT_SUCCESS);
}
