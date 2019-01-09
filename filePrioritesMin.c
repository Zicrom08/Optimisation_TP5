#include "filePrioritesMin.h"

//fonction créant un tas et initialisant les valeurs du tableau
tas *creeLP(graphe *g, int s) {
	tas *ts = (tas *) malloc(sizeof(tas));
	ts->taille = g->nbSommet;
	ts->taille2 = g->nbSommet;
	ts->t = (sommet *) malloc(sizeof(sommet) * (g->nbSommet));
	for (int i = 0; i < g->nbSommet; ++i) {
		ts->t[i].sommet = i;
		ts->t[i].pere = -1;
		ts->t[i].distance = 999;
	}
	ts->t[s].distance = 0;
	return ts;
}

void construireTasMin(tas *ts) {
	int i;
	for (i = (ts->taille / 2) - 1; i >= 0; --i)
		entasserMin(ts, i);
}

void swapNode(sommet *t, int a, int b) {
	sommet swap = t[a];
	t[a] = t[b];
	t[b] = swap;
}

void entasserMin(tas *ts, int i) {
	int max = i;
	int g = gauche(i), d = droit(i);
	if (g < ts->taille && ts->t[g].distance < ts->t[i].distance)
		max = g;
	if (d < ts->taille && ts->t[d].distance < ts->t[max].distance)
		max = d;
	if (max != i) {
		swapNode(ts->t, i, max);
		entasserMin(ts, max);
	}
}

int parent(int i) {
	if (i % 2 == 0)
		return i / 2 - 1;
	else
		return i / 2;
}

int droit(int i) { return 2 * i + 2; }

int gauche(int i) { return (2 * i + 1); }

sommet extraire_min_tas(tas *ts) {
	if (ts->taille < 0) {
		printf("Limite inférieure dépassée\n");
		exit(0);
	}
	sommet min = ts->t[0];
	ts->t[0] = ts->t[ts->taille - 1];
	ts->t[ts->taille - 1] = min;
	ts->taille = ts->taille - 1;
	entasserMin(ts, 0);
	return min;
}

void DiminuerCleTas(tas *ts, int i, int cle) {
	ts->t[i].distance = cle;
	while (i > 0 && ts->t[parent(i)].distance > ts->t[i].distance) {
		swapNode(ts->t, i, parent(i));
		i = parent(i);
	}
}

void afficherAcpmPrim(tas *ts) {
	int i;
	printf("Arbre couvrant de poids minimum : \n");
	for (i = ts->taille2 - 2; i > -1; i--) {
		printf("%2d\t %2d \n", ts->t[i].pere, ts->t[i].sommet);
	}
	printf(" ------------------------ \n");
	printf("\nLongueur de l'arbre : %d\n", distancePrim(ts));
}

void detruireTas(tas **t) {
	free((*t)->t);
	free(*t);
}

// fonction calculant le poids de l'arbre sur le tas
int distancePrim(tas *t) {
	int i = 0;
	int som = 0;
	for (i = 0; i < t->taille2; ++i) {
		som += t->t[i].distance;
	}
	return som;
}

// fonction recherchant l'indice d
int rechercheSommet(tas *t, int val) {
	int i = 0;
	while (i < t->taille && t->t[i].sommet != val)
		++i;
	return i;
}
