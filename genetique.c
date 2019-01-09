#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "genetique.h"

indiv_t creerIndiv(int taille) {
	indiv_t result;
	result.taille = taille;
	result.seq = (int *) malloc(sizeof(int) * taille);
	genererSeq(result.seq, result.taille);
	return result;
}

indiv_t creerIndivSeq(int *seq, int taille) {
	indiv_t result;
	result.taille = taille;
	result.seq = (int *) malloc(sizeof(int) * taille);
	memcpy(result.seq, seq, sizeof(int) * taille);
	return result;
}

popu_t creerPopu(int taille, int tailleIndiv) {
	popu_t result;
	result.taille = taille;
	result.popu = (indiv_t *) malloc(sizeof(indiv_t) * taille);
	for (int i = 0; i < result.taille; ++i) {
		result.popu[i] = creerIndiv(tailleIndiv);
	}
	return result;
}

void swapSeqIndiv(indiv_t *indiv, int nbswap) {
	int swap = 0;
	int indice_x = 0, indice_y = 0;

	for (int i = 0; i < nbswap; ++i) {
		indice_x = rand_a_b(0, indiv->taille);
		indice_y = rand_a_b(0, indiv->taille);
		swap = indiv->seq[indice_x];
		indiv->seq[indice_x] = indiv->seq[indice_y];
		indiv->seq[indice_y] = swap;
	}
}

int rand_a_b(int a, int b) {
	return rand() % (b - a) + a;
}

void genererSeq(int *seq, int taille) {
	int swap = 0;
	int indice_x = 0, indice_y = 0;

	for (int i = 0; i < taille; ++i) {
		seq[i] = i;
	}
	for (int i = 0; i < NBSWAP; ++i) {
		indice_x = rand_a_b(0, taille);
		indice_y = rand_a_b(0, taille);
		swap = seq[indice_x];
		seq[indice_x] = seq[indice_y];
		seq[indice_y] = swap;
	}
}

void afficherPopu(popu_t population) {
	printf("Population : \n");
	for (int i = 0; i < population.taille; ++i) {
		printf("Individu 1 : ");
		afficherIndiv(population.popu[i]);
		printf("\n");
	}
}

void afficherIndiv(indiv_t indiv) {
	printf(" Taille : %d Seq : ", indiv.taille);
	for (int i = 0; i < indiv.taille; ++i) {
		printf("%d ", indiv.seq[i]);
	}
}
