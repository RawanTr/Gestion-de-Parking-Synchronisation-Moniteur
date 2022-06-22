#include<sys/wait.h>
#include <signal.h>
#include <pthread.h>

#include "utils.h"
#include "parking.h"

extern pthread_t tid[NbTh+1];
extern pthread_t *th_time;
extern pthread_mutex_t mutex;
extern pthread_cond_t entree;
extern pthread_cond_t sortie;

extern int NbfileSortir;

extern int BoolAbo;

extern int MINUTES;

extern int NbPlacesAbo;
extern int NbPlaces;

extern int NbAboOccupees;
extern int NbOccupees;
extern int prob_voiture;

int min_parking = 5;
int max_parking = 100;

/*--------------------TESTS-----------------------*/

/*sigusr1 - handler*/
void handler(int signum){
	
	if(signum == SIGUSR1){
		BoolAbo = true;
	}

}

/* Test si abonné ou non */
bool signalAbo(){
	
	if(random_int(0, 100)>=70){
		raise(10);
		
	}else{
		BoolAbo = false;
	}
	
	return BoolAbo;
}


/* Test si place dans parking */
int test_places(){

	if (signalAbo() == true){

		if(NbAboOccupees < NbPlacesAbo){

			return 1; // assez de place pour abonnés

		} else if (NbOccupees < NbPlaces) {
		
			return 2; // abonné occupe une place non abo
		}
		
	}
	
	if (NbOccupees < NbPlaces) {

		return 0; // assez de place dans parking (abonnés et non abonnés) 

	}

	return -1; // pas de places dans parking
}


/* Test si une voiture attend pour sortir */
bool test_fileSortir(){

	if(NbfileSortir > 0){

		return false; // voiture attends pour sortir

	}

	return true; // personne n'attend pour sortir

}

/*--------------------ACTIONS-----------------------*/



/* Action pour faire entrer la voiture dans le parking */
bool action_entrer(bool* placeabo, bool* abo){

	pthread_mutex_lock(&mutex);
	
	int result_test_places = test_places(); // creation ici de la variable result pour eviter de passer dans la fonction test_places plus d'une fois (on aurait pu creer un switch mais lourdeur dans le code)

	if(result_test_places == 0 || result_test_places == 1 || result_test_places == 2) { // 0 si non abo 1 si abo -1 autremment

		if(result_test_places == 1){

				NbAboOccupees++; // actualise le nombre de places abos
				*placeabo = true;
				*abo = true;
		}else if(result_test_places == 2){

				NbOccupees++; // actualise le nombre de places non abos
				*placeabo = false;
				*abo = true;
		}else{
				NbOccupees++;
				*placeabo = false;
				*abo = false; 
		}

		pthread_cond_wait(&entree, &mutex);   // Nombre de place actualisé avant de se mettre en file d'attente et avant l'affichage console disant que la voiture est entree


	}else{

		pthread_mutex_unlock(&mutex);

		return false; // voiture ne rentre pas dans le parking

	}

	pthread_mutex_unlock(&mutex);

	return true; // voiture est rentree dans le parking

}

/* Action pour faire entrer la voiture dans le parking */
void action_sortir(bool abo){
	pthread_mutex_lock(&mutex);


	NbfileSortir++;
	pthread_cond_wait(&sortie, &mutex);


	NbfileSortir--;

	if (abo == true){

		NbAboOccupees--;

	}else{

		NbOccupees--;

	}

	pthread_mutex_unlock(&mutex);
}

/*--------------------ROUTINES-----------------------*/

void voiture(int i) {
	
	bool* placeabo = NULL;
	bool* abo = false;
	
	if(action_entrer(&placeabo, &abo) == true) {
		console("entre dans le parking", i, abo);
		
		sleep(random_int(min_parking, max_parking)); // voiture reste dans le parking le temps indiqué (endort la thread)
		action_sortir(placeabo);
		console("sort du parking", i, abo);
	}else{
		console("pas de place donc s'en va", i, abo);
	}
	
	pthread_exit(tid[i]);
}

void horloge(){
	
	int places_abo = NbPlacesAbo;
	int places_non_abo = NbPlaces;
	
	 while(1){

	 	sleep(1);

    	instant.tm_min = instant.tm_min + MINUTES;
    	if(instant.tm_min >= 60){
      		instant.tm_min = 0;
      		if((instant.tm_hour++) >= 23){
        		instant.tm_hour = 0;
      		}
    	}
		
		if(instant.tm_hour == 0 && instant.tm_min == 0){
    		prob_voiture = 20;
    		min_parking = 90;
    		max_parking = 120;
    	}
    	
    	if(instant.tm_hour == 2 && instant.tm_min == 0){
    		prob_voiture = 5;
    		min_parking = 70;
    		max_parking = 100;
    	}
    	
    	if(instant.tm_hour == 6 && instant.tm_min == 0){
    		prob_voiture = 20;
    		min_parking = 30;
    		max_parking = 80;
    	}
    	
    	if(instant.tm_hour == 8 && instant.tm_min == 0){
    		prob_voiture = 50;
    		min_parking = 10;
    		max_parking = 50;
    	}
	
    	if(instant.tm_hour == 16 && instant.tm_min == 0){
       
    		NbPlacesAbo = places_abo*0.7 ; 
           
    		NbPlaces = places_non_abo*0.7;
    		
    		prob_voiture = 75;
    		min_parking = 10;
    		max_parking = 120;
    	}
    	   
   		if(instant.tm_hour == 18 && instant.tm_min == 0){
       
    		NbPlacesAbo = places_abo*0.8;
           
    		NbPlaces = places_non_abo*0.8 ;
    		prob_voiture = 90;
    		min_parking = 10;
    		max_parking = 120;
    	}
       
    	if(instant.tm_hour == 20 && instant.tm_min == 0){
       
    		NbPlacesAbo =  places_abo*0.9;
           
   			NbPlaces =  places_non_abo*0.9;
   			prob_voiture = 75;
   			min_parking = 10;
    		max_parking = 120;
    	}
    	
    	if(instant.tm_hour == 22 && instant.tm_min == 0){
    		NbPlacesAbo = places_abo;
    		NbPlaces = places_non_abo;
    		prob_voiture = 50;
    		min_parking = 10;
    		max_parking = 120;
    	}
    	
    	
	
	}

	return;
}

void synchrone(){

	pthread_mutex_lock(&mutex);

	if(test_fileSortir() == true){

		pthread_cond_signal(&entree);

	}else{

		pthread_cond_signal(&sortie);

	}

	pthread_mutex_unlock(&mutex);
}

void parking(int i) {
	
	

	while(1){
	
		afficher();
		
		synchrone();

		sleep(1);

	}


}

