#ifndef H_LISTE
#define H_LISTE

#include <stdlib.h>
#include <string.h>

typedef struct cellule {
	struct cellule *pred;
	struct cellule *succ;
	int value;
	int poids;
} cellule;

cellule *creerCellule(int, int);

void detruireCellule(cellule **);


typedef struct liste {
	int nbElem;//juste une value pour comparer avec compterListe 5)
	cellule *tete;
} liste;

liste *creerListe();

void detruireListe(liste **);

void inserer(liste *, cellule *);

cellule *rechercher(liste *, int);

int contient(cellule *, int, int);

void supprimer(liste *, cellule *);

void afficherListe(liste *);

int compteListe(liste *);

cellule *minPoidsListe(liste *, cellule *, int);

#endif
