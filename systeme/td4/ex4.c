#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Verrous pour générer des identifiants
// uniques pour les clients et les vendeurs
pthread_mutex_t mutex_compteur_client;
pthread_mutex_t mutex_compteur_vendeur;
// Verrou pour la quantité d'un article
pthread_mutex_t *mutex_quantite;

// Condition pour savoir si le stock est insuffisant
pthread_cond_t *stock_insuffisant;

// Condition pour savoir si le stock a été rechargé
pthread_cond_t *stock_recharge;

typedef struct {
	int **articles;
	int id_vendeur;
	int id_client;
	int nb_article;
} magasin;

void *fonction_thread_client (void *arg) {
	magasin *temp = (magasin*) arg;
	
	// On bloque le verrou pour forcer
	// l'incrémentation unique des clients
	pthread_mutex_lock(&mutex_compteur_client);
	int id = temp->id_client++;
	pthread_mutex_unlock(&mutex_compteur_client);
	
	while (1) {		
		int random = rand() % 10 + 1;
		int article_choisi = rand() % temp->nb_article;
		
		// On bloque le verrou sur la quantité
		pthread_mutex_lock(&mutex_quantite[article_choisi]);
		
		if (temp->articles[article_choisi] > random) {
			temp->articles[article_choisi] -= random;
			printf("Le client n°%i a acheté l'article %i %i fois, (%i restants)\n", id, article_choisi, random, temp->articles[article_choisi]);
		}
		else {
			printf("Plus assez de stock pour l'article %i\n", article_choisi);
			// On envoie le signal pour le magasin
			pthread_cond_signal(&stock_insuffisant[article_choisi]);
			pthread_cond_wait(&stock_recharge[article_choisi], &mutex_quantite[article_choisi]);
		}
		
		// On débloque le verrou
		pthread_mutex_unlock(&mutex_quantite[article_choisi]);
		sleep(1);
	}
}

void *fonction_thread_vendeur (void *arg) {
	magasin *temp = (magasin*) arg;
	
	// On bloque le verrou pour forcer
	// l'incrémentation unique des vendeurs
	pthread_mutex_lock(&mutex_compteur_vendeur);
	int id = temp->id_vendeur++;
	pthread_mutex_unlock(&mutex_compteur_vendeur);
	
	temp->articles[id] = 100;
	
	// On bloque le verrou sur la quantité
	// pour empêcher les clients de se servir
	// lorsque on recharge le stock
	pthread_mutex_lock(&mutex_quantite[id]);
	
	while (1) {
		pthread_cond_wait(&stock_insuffisant[id], &mutex_quantite[id]);
		
		temp->articles[id] += 100;
		printf("Le vendeur n°%i a ajouté 100 articles à son rayon (%d restants)\n", id, temp->articles[id]);
		
		pthread_cond_signal(&stock_recharge[id]);
	}
	
	pthread_mutex_unlock(&mutex_quantite[id]);
}

int main (int argc, char argv[]) {
	
	// Initialiser le rand à chaque exécution
	srand((unsigned int)time(NULL));
	
	// Déclaration structure
	magasin shop;
	
	// Initialisation des identifiants
	shop.id_client = 0;
	shop.id_vendeur = 0;
	
	// Initialisation du nombre de clients
	int nb_client;
	printf ("Veuillez saisir le nombre de clients : ");
	scanf("%d", &nb_client);
	
	// Initialisation du nombre d'articles
	int nb_article;
	printf ("Veuillez saisir le nombre d'articles : ");
	scanf("%d", &nb_article);
	
	// Allocation dynamique des articles pour la structure
	shop.articles = malloc (nb_article * sizeof(int));
	shop.nb_article = nb_article;
	
	// Allocation dynamique des conditions et verrous
	mutex_quantite = malloc (nb_article * sizeof(pthread_mutex_t));
	stock_insuffisant = malloc (nb_article * sizeof(pthread_cond_t));
	stock_recharge = malloc (nb_article * sizeof(pthread_cond_t));
	
	// Initialiser les verrous
	pthread_mutex_init(&mutex_compteur_client, NULL);
	pthread_mutex_init(&mutex_compteur_vendeur, NULL);
	
	int i;
	for (i = 0; i < nb_article; i++) {
		// Verrou quantité
		pthread_mutex_init(&mutex_quantite[i], NULL);
		
		// Initialiser les conditions
		pthread_cond_init(&stock_insuffisant[i], NULL);
		pthread_cond_init(&stock_recharge[i], NULL);
	}
	
	// Déclaration des threads
	pthread_t thread_vendeur[nb_article];
	pthread_t thread_client[nb_client];
	
	// On crée les threads vendeurs
	for (i = 0; i < nb_article; i++) {
		int retour = pthread_create (&thread_vendeur[i], NULL, fonction_thread_vendeur, (void*) &shop);
		
		// Vérification
		if (retour < 0) {
			perror("Erreur lors de la création du thread vendeur\n");
			exit(0);
		}
	}
	printf ("Tous les vendeurs ont bien été initialisés\n");
	
	// On créé les threads clients
	for (i = 0; i < nb_client; i++) {
		int retour = pthread_create (&thread_client[i], NULL, fonction_thread_client, (void*) &shop);
		
		// Vérification
		if (retour < 0) {
			perror ("Erreur lors de la création du thread client \n");
			exit(0);
		}
	}
	printf ("Tous les clients ont bien été initialisés\n");
	
	// On s'assure que les threads soient fermés
	for (i = 0; i < nb_article; i++) {
		int retour = pthread_join(thread_vendeur[i], NULL);
		
		// Vérification
		if (retour < 0) {
			perror ("Erreur lors de la fermeture du thread client \n");
			exit(0);
		}
	}
	
	for (i = 0; i < nb_client; i++) {
		int retour = pthread_join(thread_client[i], NULL);
		
		// Vérification
		if (retour < 0) {
			perror ("Erreur lors de la fermeture du thread vendeur \n");
			exit(0);
		}
	}
	
	pthread_exit(NULL);
	return(1);	
	exit(0);
}