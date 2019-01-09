#include <stdlib.h>
#include <stdio.h>
#include "genetique.h"

indiv_t creerIndiv(int taille, graphe *g) {
	indiv_t result;
	result.taille = taille;
	result.seq = (int *) malloc(sizeof(int) * taille);
	genererSeq(result.seq, result.taille);
	result.distance = distanceIndiv(result, g);
	return result;
}

indiv_t creerIndivSeq(int *seq, int taille, graphe *g) {
	indiv_t result;
	result.taille = taille;
	result.seq = (int *) malloc(sizeof(int) * taille);
	printf("Seq dans individu : ");
	for (int i = 0; i < taille; ++i) {
		result.seq[i] = seq[i];
		printf("%d ", result.seq[i]);
	}
	printf("\n");
	result.distance = distanceIndiv(result, g);
	return result;
}

popu_t creerPopu(int taille, int tailleIndiv, graphe *g) {
	popu_t result;
	result.taille = taille;
	result.g = g;
	result.popu = (indiv_t *) malloc(sizeof(indiv_t) * taille);
	for (int i = 0; i < result.taille; ++i) {
		result.popu[i] = creerIndiv(tailleIndiv, result.g);
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

double rand_0_1() {
	return (double) rand() / (double) ((unsigned) RAND_MAX + 1);
}

int contienttab(int *tab, int taille, int x) {
	for (int i = 0; i < taille; ++i) {
		if (tab[i] == x)
			return 1;
	}
	return 0;
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
		printf("Individu %d : ", i);
		afficherIndiv(population.popu[i]);
		printf("\n");
	}
}

void afficherIndiv(indiv_t indiv) {
	printf(" Taille : %d Seq : ", indiv.taille);
	for (int i = 0; i < indiv.taille; ++i) {
		printf("%d ", indiv.seq[i]);
	}
	printf(" Distance : %d", indiv.distance);
}

int distanceIndiv(indiv_t indiv, graphe *g) {
	int res = 0;
	for (int i = 0; i < indiv.taille - 1; ++i) {
		res += g->matrice[indiv.seq[i]][indiv.seq[i + 1]];
	}
	/* Calcul du dernier cas : arete entre le sommet de fin et de début du cycle hamiltonien */
	res += g->matrice[indiv.seq[indiv.taille - 1]][indiv.seq[0]];
	return res;
}

int *selectionIndiv(popu_t *population, int nbReprod) {
	double *fitness = (double *) malloc(sizeof(double) * population->taille);
	int *tab = (int *) malloc(sizeof(int) * nbReprod);
	double s, nb;
	int k = 0;
	for (int j = 0; j < nbReprod; ++j) {
		s = 0.;
		nb = rand_0_1();
		k = 0;
		for (int i = 0; i < population->taille; ++i) {
			fitness[i] = population->popu[i].distance;
			fitness[i] = 1 / fitness[i];
		}
		for (int i = 0; i < population->taille; ++i) {
			s += fitness[i];
		}
		for (int i = 0; i < population->taille; ++i) {
			fitness[i] /= s;
		}
		for (int i = 1; i < population->taille; ++i) {
			fitness[i] += fitness[i - 1];
		}
		while (fitness[k] <= nb)
			k++;
		tab[j] = k;
		printf("Individu n° %d choisi : ", k);
		afficherIndiv(population->popu[k]);
		printf("\n");
	}
	return tab;
}

indiv_t *mutationIndiv(popu_t *population, int *tabSelection, int nbReprod) {
	indiv_t *tabMutation = (indiv_t *) malloc(sizeof(indiv_t) * nbReprod);
	int *seqMut;
	for (int i = 0; i < nbReprod; ++i) {
		if (i % 2 == 0) {
			seqMut = mutationSeq(population->popu[tabSelection[i]].seq, population->popu[tabSelection[i + 1]].seq,
								 population->g->nbSommet);
			tabMutation[i] = creerIndivSeq(seqMut, population->g->nbSommet, population->g);
		} else {
			seqMut = mutationSeq(population->popu[tabSelection[i]].seq, population->popu[tabSelection[i - 1]].seq,
								 population->g->nbSommet);
			tabMutation[i] = creerIndivSeq(seqMut, population->g->nbSommet, population->g);
		}
	}
}

int *mutationSeq(int *seq1, int *seq2, int taille) {
	int *res = (int *) malloc(sizeof(int) * taille);
	unsigned int i = 0, indice = 0;
	int tmp = 0;
	while (i != taille / 2) {
		res[i] = seq1[i];
		i++;
	}
	indice = i;

	while (indice != taille - 1) {
		if (i < taille && contienttab(res, taille, seq2[i]) == 0) {
			tmp = seq2[i];
			res[indice] = tmp;
			indice++;
			i++;
		} else {
			if (i == taille - 1) {
				i = 0;
			} else {
				i++;
			}
		}
	}


	printf("Seq 1 : ");
	for (int j = 0; j < taille; ++j) {
		printf("%d ", seq1[j]);
	}
	printf("\n Seq 2 : ");
	for (int j = 0; j < taille; ++j) {
		printf("%d ", seq2[j]);
	}
	printf("\n Seq 3 : ");
	for (int j = 0; j < taille; ++j) {
		printf("%d ", res[j]);
	}
	printf("\n");
	return res;
}
