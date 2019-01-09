#include "ListeAdj.h"

ListeAdj *creerListeAdj(int taille) {
	ListeAdj *th = (ListeAdj *) malloc(sizeof(ListeAdj));
	th->taille = taille;
	th->tabList = (liste **) malloc(sizeof(liste *) * taille);
	int i;
	for (i = 0; i < taille; ++i)
		th->tabList[i] = creerListe();
	return th;
}

void detruireListeAdj(ListeAdj **th) {
	int i;
	for (i = 0; i < (*th)->taille; ++i)
		detruireListe(&(*th)->tabList[i]);
	free((*th)->tabList);
	free(*th);
}

void afficherListeAdj(ListeAdj *th) {
	int i;
	for (i = 0; i < th->taille; ++i) {
		printf("Sommet : %d -> ", i);
		afficherListe(th->tabList[i]);
		printf("%s", "\n");
	}
}

void insererListeAdj(ListeAdj *la, int ind, int c, int p) {
	inserer(la->tabList[ind], creerCellule(c, p));
}

cellule *rechercherListeAdj(ListeAdj *la, int x, int ind) {
	return rechercher(la->tabList[ind], x);
}

void supprimerListeAdj(ListeAdj *la, int x, int ind) {
	supprimer(la->tabList[ind], rechercherListeAdj(la, x, ind));
}

int compteTabListe(ListeAdj *la) {
	int count = 0;
	int i;
	for (i = 0; i < la->taille; ++i) {
		count += compteListe(la->tabList[i]);
	}
	return count;
}
