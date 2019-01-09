#ifndef H_LISTEADJ
#define H_LISTEADJ

#include "liste.h"
#include <stdio.h>

typedef struct ListeAdj {
	int taille;
	liste **tabList;
} ListeAdj;

ListeAdj *creerListeAdj(int taille);

void detruireListeAdj(ListeAdj **);

void afficherListeAdj(ListeAdj *);

void insererListeAdj(ListeAdj *, int, int, int);

cellule *rechercherListeAdj(ListeAdj *, int, int);

void supprimerListeAdj(ListeAdj *, int, int);

int compteTabListe(ListeAdj *);

#endif
