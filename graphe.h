#ifndef H_GRAPHE
#define H_GRAPHE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ListeAdj.h"
#include "file.h"

typedef struct graphe {
	int nbSommet;
	int oriente;
	int value;
	int complet;
	ListeAdj *l;
	int **matrice;
} graphe;

void creerListesAdjacences(char *, graphe *);

void afficherListesAdjacences(graphe *);

void creerMatriceAdjacences(char *, graphe *);

void afficherMatriceAdjacences(graphe *);

graphe *creerGraphe(char *);

void detruireGraphe(graphe **);

parcours **parcoursLargeur(graphe *, int);

#endif
