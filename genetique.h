#ifndef _GENETIQUE_H
#define _GENETIQUE_H

#define NBSWAP 10

typedef struct indiv_t {
	int *seq;
	int taille;
	int distance;
} indiv_t;

typedef struct popu_t {
	indiv_t *popu;
	int taille;
} popu_t;


indiv_t creerIndiv(int);

indiv_t creerIndivSeq(int *, int);

popu_t creerPopu(int, int);

void afficherPopu(popu_t);

void afficherIndiv(indiv_t);

int rand_a_b(int, int);

void swapSeqIndiv(indiv_t *, int);

void genererSeq(int *, int);


#endif