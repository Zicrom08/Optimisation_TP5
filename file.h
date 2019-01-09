#ifndef H_FILE
#define H_FILE

#include <stdio.h>
#include <stdlib.h>

#define BLANC 0
#define GRIS 1
#define NOIR 2
typedef struct parcours {
	int sommet;
	int couleur;
	int distance;
	int pere;
} parcours;

parcours *creerParcours(int);


typedef struct cel {
	struct cel *succ;
	parcours *value;
} cel;

cel *creercel(parcours *);

void detruirecel(cel **);


typedef struct file {
	int taille;
	cel *tete;
	cel *queue;
} file;


file *creerFile();

void detruireFile(file **);

int fileVide(file *);

void enfiler(file *, parcours *);

cel *defiler(file *);

void afficher(file *);

#endif
