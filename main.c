#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "genetique.h"

int main(int argc, char **argv) {
	int taillePopulation;
	int nombreReprod;
	int *tabSelection;

	if (argc != 4) {
		fprintf(stderr, "Usage : %s FICHIER_GRAPH TAILLE_POPULATION NOMBRE_PARENT_REPROD\n", argv[0]);
		fprintf(stderr, "Ou :\n");
		fprintf(stderr, "  FICHIER_GRAPH        : fichier .txt contenant un graphe valide\n");
		fprintf(stderr, "  TAILLE_POPULATION    : taille de la population désiré\n");
		fprintf(stderr, "  NOMBRE_PARENT_REPROD : Nombre de reproduction désiré\n");

		exit(EXIT_FAILURE);
	}
	srand(time(NULL));
	taillePopulation = atoi(argv[2]);
	nombreReprod = atoi(argv[3]);
	graphe *g = creerGraphe(argv[1]);
	popu_t pop = creerPopu(taillePopulation, g->nbSommet, g);
	tabSelection = selectionIndiv(&pop, nombreReprod);
	mutationIndiv(&pop, tabSelection, nombreReprod);


	return 0;
}
