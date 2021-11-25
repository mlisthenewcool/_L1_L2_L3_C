#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int compteur;
pthread_mutex_t mutex_compteur;

typedef struct {
  int * newsocketfd;
} socketdata;

void * message_client(void* arg) {
  socketdata *temp = (socketdata *) arg;
  pthread_mutex_lock(&mutex_compteur);
  int id = compteur;
  compteur++;
  pthread_mutex_unlock(&mutex_compteur);
  
  while (1) {
    char msg[100];
    char msg2[100];
    
    read(temp->newsocketfd[id], msg, sizeof(msg));
    printf(" Le message reçu est %s \n",msg);
    
    scanf("%s", msg2);
    write(temp->newsocketfd[id], msg2, sizeof(msg2));
    printf(" message envoyé \n");
  }
}

int main()
{
  /* Déclaration des variables */
  int sockserveur,newsockfd, lg;
  struct sockaddr_in coord_client;
  struct sockaddr_in mes_coord;
  struct tm *m;
  char* pc;
  char msg[100];
  
  /* Création d'un socket */
  sockserveur = socket(AF_INET, SOCK_STREAM, 0);
  
  /* Serveur : appel BIND */
  bzero(&mes_coord,sizeof(mes_coord));
  mes_coord.sin_family=AF_INET;
  mes_coord.sin_port = htons(2002);
  mes_coord.sin_addr.s_addr = htonl(INADDR_ANY);
  
  if( bind (sockserveur,(struct sockaddr*) &mes_coord, sizeof(mes_coord)) < 0) {
    printf("Erreur BIND\n");
    exit(0);
  }
  
  /* Serveur : appel LISTEN */
  if (listen(sockserveur, 5) < 0) {
    printf("Erreur LISTEN\n");
    exit(0);
  }

/* Serveur : appel ACCEPT */
  while(1) {
    lg = sizeof(coord_client);
    
    // Les clients sont gérés dans un thread séparé (un par client)
    pthread_t *clients;
    int nbre_clients = 100;
    clients = malloc (nbre_clients * sizeof(pthread_t));
    
    // Mutex compteur des threads
    pthread_mutex_t mutex_compteur;
    pthread_mutex_init(&mutex_compteur, NULL);
    
    int i;
    
    newsockfd = accept(sockserveur, (struct sockaddr*) &coord_client, &lg);
    
    for (i = 0; i < nbre_clients; i++) {
      pthread_create(&clients[i], NULL, message_client, NULL);
    }
    
    if( newsockfd == -1) {
      printf("Erreur ACCEPT\n");
      exit(0);
    }
    
    while (1) {
      //lire la socket
      read(newsockfd,msg,sizeof(msg));
      printf(" message recu %s \n",msg);
      
      char msg2[100];
      scanf("%s",msg2);
      write(newsockfd,msg2,sizeof(msg2));
      printf(" message envoye \n");
    }
      close(newsockfd);
  }
  
  close(sockserveur);
}