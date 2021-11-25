#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char** argv) {
	int pid, statut;
	
  while(1) {
		pid = fork();
		
  	if(pid < 0) {
    	perror("pid");
    	exit(EXIT_FAILURE);
  	}
  	
  	else if(pid == 0) {
      char nom_programme[100];
			
      printf("Veuillez saisir un programme à entrer : ");
      scanf("%s",nom_programme);
			
      execve(nom_programme, NULL, NULL);
      perror("Erreur de lancement du programme");
			exit(EXIT_FAILURE);
    }
    else
      waitpid(pid, &statut, 0);
  }
  
  exit(EXIT_SUCCESS);
}