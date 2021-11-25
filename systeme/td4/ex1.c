#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Verrou pour le numéro du thread client
pthread_mutex_t mutex_compteur;
// Verrou pour la quantité
pthread_mutex_t mutex_quantite;
// Verrou pour le remplissage de magasin
pthread_mutex_t mutex_magasin;

// Condition pour savoir si le stock est suffisant
pthread_cond_t stock_insuffisant;

typedef struct {
	int quantite;
	int id_client;
} magasin;

void *fonction_thread_client (void *arg) {
	magasin *temp = (magasin*) arg;
	
	// On bloque le verrou pour forcer
	// l'incrémentation unique des 
	pthread_mutex_lock(&mutex_compteur);
	int id = temp->id_client++;
	pthread_mutex_unlock(&mutex_compteur);
	
	while (1) {
		sleep(1);
		int random = rand() % 10 + 1;
		
		// On bloque le verrou sur la quantité
		pthread_mutex_lock(&mutex_quantite);
		
		if (temp->quantite > random) {
			temp->quantite -= random;
			printf("Thread/Client N°%d a acheté %d articles, (%d restants)\n", id, random, temp->quantite);
		}
		else {
			// On envoie le signal pour le magasin
			pthread_cond_signal(&stock_insuffisant);
			printf("Plus assez de stock ...\n");
		}
		
		// On débloque le verrou
		pthread_mutex_unlock(&mutex_quantite);
	}
	
	pthread_exit(NULL);
}

void *fonction_thread_magasin (void *arg) {
	magasin *temp = (magasin*) arg;
	
	while (1) {
		pthread_cond_wait(&stock_insuffisant, &mutex_magasin);
		
		// On bloque le verrou sur la quantité
		// pour empêcher les clients de se servir
		// lorsque on recharge le stock
		pthread_mutex_lock(&mutex_quantite);
		
		temp->quantite = 100;
		printf("1000 articles ajoutés, quantité actuelle : %d\n", temp->quantite);
		
		pthread_mutex_unlock(&mutex_quantite);
	}
}

int main (int argc, char argv[]) {
	
	// Initialiser le rand à chaque exécution
	srand((unsigned int)time(NULL));
	
	// Initialisation du stock
	magasin shop;
	shop.id_client = 0;
	
	printf("Veuillez saisir la quantité initiale du stock : ");
	scanf("%d", &shop.quantite);
	
	// Initialisation du nombre de clients/threads
	int nb_client;
	printf ("Veuillez saisir le nombre de clients : ");
	scanf("%d", &nb_client);
	
	// Initialiser les verrous
	pthread_mutex_init(&mutex_quantite, NULL);
	pthread_mutex_init(&mutex_compteur, NULL);
	pthread_mutex_init(&mutex_magasin, NULL);
	
	// Initialiser la condition
	pthread_cond_init(&stock_insuffisant, NULL);
	
	// Déclaration des threads
	pthread_t thread_magasin;
	pthread_t thread_client[nb_client];
	
	// On crée le thread magasin
	int retour = pthread_create (&thread_magasin, NULL, fonction_thread_magasin, (void*) &shop);
	
	// Vérification
	if (retour < 0) {
		printf ("Erreur lors de la création du thread magasin\n");
		exit(0);
	}
	else
		printf ("Le thread magasin a bien été créé\n");
	
	// On créé les threads clients
	int i;
	for (i = 0; i < nb_client; i++) {
		int retour = pthread_create (&thread_client[i], NULL, fonction_thread_client, (void*) &shop);
		
		// Vérification
		if (retour < 0) {
			printf ("Erreur lors de la création du thread client %i\n", i);
			exit(0);
		}
		else
			printf ("Le thread client %i a bien été créé\n", i);
	}
	
	// On s'assure que les threads soient fermés
	pthread_join(thread_magasin, NULL);
	
	for (i = 0; i < nb_client; i++) {
		pthread_join(thread_client[i], NULL);
	}
}