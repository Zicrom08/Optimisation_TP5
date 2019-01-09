#include "liste.h"
#include <stdio.h>

cellule *creerCellule(int x, int p) {
	cellule *c = (cellule *) malloc(sizeof(cellule));
	c->value = x;
	c->poids = p;
	c->pred = NULL;
	c->succ = NULL;
	return c;
}

void detruireCellule(cellule **c) {
	free(*c);
	c = NULL;
}

liste *creerListe() {
	liste *l = (liste *) malloc(sizeof(liste));
	l->tete = NULL;
	l->nbElem = 0;//controle
	return l;
}


void detruireListe(liste **l) {
	cellule *del = (*l)->tete;
	while (del != NULL) {
		supprimer((*l), del);
		del = (*l)->tete;
	}
	free(*l);
	*l = NULL;
	detruireCellule(&del);
}

void inserer(liste *l, cellule *c) {
	if (l->tete != NULL) {
		c->succ = l->tete;
		l->tete->pred = c;
		l->tete = c;
		c->pred = NULL;
	} else {
		c->pred = NULL;
		c->succ = NULL;
		l->tete = c;
	}
	l->nbElem += 1;//controle
}


cellule *rechercher(liste *l, int x) {
	cellule *tmp = l->tete;
	while (tmp != NULL && tmp->value != x) {
		tmp = tmp->succ;
	}
	return tmp;
}

int contient(cellule *tab, int x, int tailletab) {
	int res = 0, i = 0;
	while (res == 0 && i != tailletab) {
		if (tab[i].value == x)
			res = 1;
		i++;
	}
	return res;
}

void supprimer(liste *l, cellule *c) {
	if (c->pred != NULL)
		c->pred->succ = c->succ;
	else
		l->tete = c->succ;
	if (c->succ != NULL)
		c->succ->pred = c->pred;
	l->nbElem -= 1;//controle
	detruireCellule(&c);
	c = NULL;
}


void afficherListe(liste *l) {
	cellule *tmp = l->tete;
	while (tmp != NULL) {
		printf(" %d (%d) ->", tmp->value, tmp->poids);
		tmp = tmp->succ;
	}
	printf(" NIL \n");
	detruireCellule(&tmp);
}

int compteListe(liste *l) {
	cellule *tmp = l->tete;
	int nbMot = 0;
	while (tmp != NULL) {
		++nbMot;
		tmp = tmp->succ;
	}
	return nbMot;
}

cellule *minPoidsListe(liste *l, cellule *tabCellule, int tailletab) {
	cellule *tmp = l->tete;
	cellule *min = creerCellule(-1, 100000);
	while (tmp != NULL) {
		if (contient(tabCellule, tmp->value, tailletab) == -1 && tmp->poids < min->poids) {
			min->value = tmp->value;
			min->poids = tmp->poids;
		}
		tmp = tmp->succ;
	}
	return min;
}
