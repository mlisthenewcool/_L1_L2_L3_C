#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc,char** argv) {
  struct sockaddr_in coord_serveur;
  int sockclient;
  struct tm *m;
  char* pc;
  u_short port;
  int nb;
  
  //création de la socket
  if(argc != 3) {
    printf("Usage: ./client <adresse ip> <port>\n");
    return 0;
  }

  port = atoi(argv[2]);
  sockclient = socket(AF_INET, SOCK_STREAM, 0);

  //Partie connect ()

  //préparation de la structure permettant de connecter le serveur
  bzero(&coord_serveur,sizeof(coord_serveur));
  coord_serveur.sin_family = AF_INET;
  coord_serveur.sin_port = htons(port);
  coord_serveur.sin_addr.s_addr = inet_addr(argv[1]);
  
  if(connect(sockclient, (struct sockaddr *) &coord_serveur, sizeof(coord_serveur)) < 0) { 
    printf ("erreur de connexion \n");
    exit(0);
  }
  
  while (1) {
    //Traitement
    char  msg[100];
    scanf("%s", msg);
    
    write(sockclient,msg,sizeof(msg));
    printf("message envoye \n");
    
    char msg2[100];
    read(sockclient, msg2, sizeof(msg2));
    printf("message recu %s\n",msg2);
  }

  close(sockclient);
}