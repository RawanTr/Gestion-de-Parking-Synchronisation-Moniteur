#ifndef H_GL_PARKING
#define H_GL_PARKING


void handler(int signum);

bool signalAbo();

int test_places();

bool test_fileSortir();

bool action_entrer(bool* placeabo, bool* abo);

void action_sortir(bool abo);

void voiture(int i);

void horloge();

void synchrone();

void parking(int i);


#endif
