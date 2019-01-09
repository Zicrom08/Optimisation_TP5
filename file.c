#include "file.h"

parcours *creerParcours(int x) {
	parcours *p = (parcours *) malloc(sizeof(parcours));
	p->sommet = x;
	p->couleur = BLANC;
	p->distance = 99999;
	p->pere = 0;
	return p;
}


cel *creercel(parcours *p) {
	cel *c = (cel *) malloc(sizeof(cel));
	c->succ = NULL;
	c->value = p;
	return c;
}

void detruirecel(cel **c) {
	free((*c)->value);
	free(*c);
	*c = NULL;
}


file *creerFile() {
	file *f = (file *) malloc(sizeof(file));
	f->tete = NULL;
	f->taille = 0;
	f->queue = NULL;
	return f;
}

void detruireFile(file **f) {
	cel *tmp = (*f)->tete;
	while (tmp != NULL) {
		(*f)->tete = (*f)->tete->succ;
		detruirecel(&tmp);
		tmp = (*f)->tete;
	}
	free((*f));
	(*f) = NULL;
}

int fileVide(file *f) {
	return f->tete == NULL;
}//1  vide / 0 non vide

void enfiler(file *f, parcours *p) {
	if (fileVide(f)) {
		f->queue = creercel(p);
		f->tete = f->queue;
		f->taille++;
	} else {
		f->queue->succ = creercel(p);
		f->queue = f->queue->succ;
		f->taille++;
	}
}

cel *defiler(file *f) {
	cel *tmp = f->tete;
	if (!fileVide(f)) {
		f->tete = f->tete->succ;
		f->taille--;
	}
	return tmp;
}

void afficher(file *f) {
	printf("f.tete <-");
	cel *tmp = f->tete;
	while (tmp != NULL) {
		printf(" %d <-", tmp->value->sommet);
		tmp = tmp->succ;
	}
	printf(" f.queue \n");
}
