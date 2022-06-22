#ifndef H_GL_UTILS
#define H_GL_UTILS

struct tm instant;

#define NbTh 10

typedef int bool ;//on définie des variables boolean
#define false 0
#define true 1




int random_int(int min, int max);


void menu();

void header();

void afficher();

void console(char * msg, int j, bool abo);


#endif
