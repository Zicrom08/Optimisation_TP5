#ifndef TAS_H
#define TAS_H

#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"

typedef struct sommet {
	int sommet;
	int distance;
	int pere;
} sommet;

typedef struct tas {
	int taille;
	int taille2; // reste fixe
	sommet *t;
} tas;

tas *creeLP(graphe *, int);

void swapNode(sommet *, int, int);

void entasserMin(tas *, int);

void construireTasMin(tas *);

int parent(int);

int droit(int);

int gauche(int);

sommet extraire_min_tas(tas *);

void DiminuerCleTas(tas *, int, int);

void afficherAcpmPrim(tas *);

void detruireTas(tas **);

int distancePrim(tas *);

int rechercheSommet(tas *, int);

#endif
