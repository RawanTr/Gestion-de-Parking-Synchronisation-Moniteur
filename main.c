#include<unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include<signal.h>


#include "utils.h"
#include "parking.h"


int NbPlacesAbo = 20;
int NbPlaces = 30;

int NbAboOccupees = 0;
int NbOccupees = 0;


pthread_t tid[NbTh+1];
pthread_t *th_time;

pthread_t *th_voitures;

pthread_mutex_t mutex;
pthread_cond_t entree;
pthread_cond_t sortie;

//initialisations

int MINUTES = 5;

int NbfileSortir = 0;

int BoolAbo = false;

bool bool_infini = true; 

bool bool_attendre = false;

int dureeSimulation = 0; 

int tempsRestant = -1;

int prob_voiture = 50; 

//Nombre de voitures en attente pour se  garer
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t entree = PTHREAD_COND_INITIALIZER;
pthread_cond_t sortie = PTHREAD_COND_INITIALIZER;


int main()
{

	int num = 0;
	int size = 0;

	signal(SIGUSR1, handler); 

	srand( time( NULL ) );

	instant.tm_hour = 15;
	instant.tm_min = 0;
	instant.tm_sec = 0;

	menu();
	
	// creation de la thread horloge
	pthread_create(&th_time, 0,&horloge, NULL);


	// creation de la thread parking
	pthread_create(tid+NbTh,0,(void *(*)())parking,(void*)NbTh);

	//creation des threads voiture

	th_voitures = malloc(sizeof(pthread_t));
	
	if (bool_infini == false) {
		
		while(tempsRestant > 0) {
		
			
			if(random_int(0, 100) < prob_voiture){
				pthread_create(&th_voitures[num], 0, (void*(*)())voiture, (void*)num);
				num++;
				size++;
			}
			tempsRestant--;
			sleep(1);
		}
	
	} else {
	
		while(1){
			if(random_int(0, 100) < prob_voiture){
				pthread_create(&th_voitures[num], 0, (void*(*)())voiture, (void*)num);
				num++; 
			}
			sleep(1);
		} 
	}
	

	if(bool_attendre == true){
	//attend la fin de toutes les threads voitures
		for(num=0;num<size;num ++){
			pthread_join(th_voitures[num],NULL);
		}   
	}
	
	afficher();

	/* liberation des ressources");*/
	
	 free(th_voitures);
	 pthread_mutex_destroy(&mutex);
	 pthread_cond_destroy(&entree);
	 pthread_cond_destroy(&sortie);
	 
	exit(0);
}
