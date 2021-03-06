#ifndef _GENETIQUE_H
#define _GENETIQUE_H

#include "graphe.h"

#define NBSWAP 10

typedef struct indiv_t {
	int *seq;
	int taille;
	int distance;
} indiv_t;

typedef struct popu_t {
	indiv_t *popu;
	graphe *g;
	int taille;
} popu_t;


indiv_t creerIndiv(int, graphe *);

void detruireIndiv(indiv_t* indiv, int taille);

indiv_t creerIndivSeq(int *, int, graphe *);

popu_t creerPopu(int, int, graphe *);

void detruirePopu(popu_t *);

void afficherPopu(popu_t);

void afficherIndiv(indiv_t);

int rand_a_b(int, int);

double rand_0_1();

int contienttab(int *, int, int);

int maxtab(popu_t *);

int mintab(popu_t*);

void swapSeqIndiv(indiv_t *, int);

void genererSeq(int *, int);

int distanceIndiv(indiv_t, graphe *);

int *selectionIndiv(popu_t *, int);

indiv_t *mutationIndiv(popu_t *, int *, int);

int *mutationSeq(int *, int *, int);

void mutationPopulation(popu_t *, indiv_t *, int);

void mutationRandom(popu_t *, int, int);


#endif