#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "genetique.h"

int main(int argc, char **argv) {
	int taillePopulation;
	int nombreReprod;
	int *tabSelection;
	indiv_t *tabMutation;

	if (argc != 6) {
		fprintf(stderr, "Usage : %s FICHIER_GRAPH TAILLE_POPULATION NOMBRE_PARENT_REPROD NOMBRE_ITERATION NOMBRE_MUTATION\n", argv[0]);
		fprintf(stderr, "Ou :\n");
		fprintf(stderr, "  FICHIER_GRAPH        : fichier .txt contenant un graphe valide\n");
		fprintf(stderr, "  TAILLE_POPULATION    : taille de la population désiré\n");
		fprintf(stderr, "  NOMBRE_PARENT_REPROD : Nombre de reproduction désiré\n");
		fprintf(stderr, "  NOMBRE_ITERATION     : Nombre d'iteration de mutation désiré\n");
		fprintf(stderr, "  NOMBRE_MUTATION     : Nombre de mutation aléatoire désiré.\n");

		exit(EXIT_FAILURE);
	}
	srand((unsigned int) time(NULL));
	taillePopulation = atoi(argv[2]);
	nombreReprod = atoi(argv[3]);
	graphe *g = creerGraphe(argv[1]);

	popu_t pop = creerPopu(taillePopulation, g->nbSommet, g);
	//afficherPopu(pop);
	for (int i = 0; i < atoi(argv[4]); ++i) {
		tabSelection = selectionIndiv(&pop, nombreReprod);
		tabMutation = mutationIndiv(&pop, tabSelection, nombreReprod);
		mutationPopulation(&pop, tabMutation, nombreReprod);
		//afficherPopu(pop);
		mutationRandom(&pop, atoi(argv[5]), 3);
		//afficherPopu(pop);
	}
	printf("\n\nLa distance minimale après génération est\n");
	afficherIndiv(pop.popu[mintab(&pop)]);

	detruirePopu(&pop);
	return 0;
}
