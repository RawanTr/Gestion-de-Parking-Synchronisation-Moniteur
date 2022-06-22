#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "utils.h"


char message[10][64];

extern int NbPlacesAbo;
extern int NbPlaces;

extern int NbAboOccupees;
extern int NbOccupees;
extern int MINUTES;
extern bool bool_infini; 
extern int dureeSimulation;
extern int tempsRestant;

extern bool bool_attendre;


int random_int(int min, int max)
{
   return min + rand() % (max - min);
}


void header(){
	
	system("clear");
	
	printf("                      -------------------------------------------------------------------\n");
	printf("                      -                                                                 -\n");
	printf("                      -                                                                 -\n");
	printf("                      -                             PARKING                             -\n");
	printf("                      -                                                                 -\n");
	printf("                      -                                                                 -\n");
	printf("                      -------------------------------------------------------------------\n");	
	printf("                                                   %d:%d:%d\n", instant.tm_hour, instant.tm_min, instant.tm_sec);
	
	printf("\n\n");
	if (bool_infini == false) {
		printf("                                         Temps restant : %d secondes", tempsRestant);
	}
	printf("\n\n");
	printf("                 Places abonnées : %d     Places non abonnées : %d    Total places disponible : %d\n\n\n", NbPlacesAbo - NbAboOccupees, NbPlaces - NbOccupees, NbPlacesAbo + NbPlaces - NbAboOccupees - NbOccupees);
	printf("                      -------------------------------------------------------------------\n\n\n");
	
	if(tempsRestant == 0 && bool_attendre == true) {
		printf("                              On attend que le parking se vide pour teminer la simulation\n\n\n");
	}else {
		printf("                                                     ...\n\n\n");
	}
	
}


void menu(){
	
	char userC[1];
	int userI;
	
	header();
	
	
	while ( strcmp(userC, "O") != 0 && strcmp(userC, "o") != 0 && strcmp(userC, "N") != 0 && strcmp(userC, "n") != 0){
		printf("Conserver les paramètres par defauts ? [O/N] : ");
		scanf("%s", userC);
		
	}
	
	if(strcmp(userC,"N") == 0 || strcmp(userC, "n") == 0){
		
		strcpy(userC, "");
		while ( strcmp(userC, "O") != 0 && strcmp(userC, "o") != 0 && strcmp(userC, "N") != 0 && strcmp(userC, "n") != 0){
			printf("Configurer le nombre de places du parking ? [O/N] : ");
			scanf("%s", userC);
			
		}
		
		if(strcmp(userC,"O") == 0 || strcmp(userC, "o") == 0){
			
			printf("\nNombre de places abonnées [Entier] : ");
			scanf("%d", &userI);
			NbPlacesAbo = userI;
			printf("\nNombre de places non abonnées [Entier] : ");
			scanf("%d", &userI);
			NbPlaces = userI;
			
			header();
		}
		
		strcpy(userC, "");
		while ( strcmp(userC, "O") != 0 && strcmp(userC, "o") != 0 && strcmp(userC, "N") != 0 && strcmp(userC, "n") != 0){
			
			printf("Changer l'heure ? [O/N] : ");
			scanf("%s", userC);
		
		}
		
		if(strcmp(userC,"O") == 0 || strcmp(userC, "o") == 0){
			
			printf("\nHeures [Entier] : ");
			scanf("%d", &userI);
			instant.tm_hour = userI;
			printf("\nMinutes [Entier] : ");
			scanf("%d", &userI);
			instant.tm_min = userI;
			
			printf("\n1 seconde pour [Entier] : ");
			scanf("%d", &userI);
			MINUTES = userI;
			header();
			
		}
		
		strcpy(userC, "");
		while ( strcmp(userC, "O") != 0 && strcmp(userC, "o") != 0 && strcmp(userC, "N") != 0 && strcmp(userC, "n") != 0){
			
			printf("Changer la duree de la simulation (aucune limite par defaut) ? [O/N] : ");
			scanf("%s", userC);
		
		}
		
		if(strcmp(userC,"O") == 0 || strcmp(userC, "o") == 0){
			
			bool_infini = false; 
			
			printf("\nDuree de la simulation en secondes(reelles) [Entier] : ");
			scanf("%d", &userI);
			dureeSimulation = userI;
			tempsRestant = dureeSimulation;
			
			header();
			
		}
		
		
		strcpy(userC, "");
		while ( strcmp(userC, "O") != 0 && strcmp(userC, "o") != 0 && strcmp(userC, "N") != 0 && strcmp(userC, "n") != 0){
			
			printf("Attendre que le parking se vide pour terminer la simulation (non par defaut) ? [O/N] : ");
			scanf("%s", userC);
		
		}
		
		if(strcmp(userC,"O") == 0 || strcmp(userC, "o") == 0){
			
			bool_attendre = true; 
			
			header();
			
		}
	}
	
	
	
	
}


void afficher(){
	
	header();
	
	for (int i = 0; i < 10; i++){
		printf("                                   %s\n\n", message[i]);
	}
	
	printf("\n\n\n");
	
}


void console(char * msg, int j, bool abo){

	char datetime[32];
	
	if (abo == true) {
		sprintf(datetime, "[%d:%d] voiture %d ABONNEE : ", instant.tm_hour, instant.tm_min, j);
	} else {
		sprintf(datetime, "[%d:%d] voiture %d : ", instant.tm_hour, instant.tm_min, j);
	}
	

	for (int i = 1; i <10; i++){

			strcpy(message[i-1], message[i]);

	}

	strcat(strcpy(message[9], datetime), msg);


}
