#include "graphe.h"

void creerListesAdjacences(char *nomfichier, graphe *g) {
	int indice, x;
	char buff[255];
	int val;
	int poids;

	FILE *fichier;
	fichier = fopen(nomfichier, "r");

	if (fichier == NULL) {
		perror("Erreur lors de l'ouverture du fichier %s\n");
		exit(EXIT_FAILURE);
	} else {
		fscanf(fichier, "%s", buff);
		fscanf(fichier, "%d ", &val);
		g->nbSommet = val;

		g->l = creerListeAdj(val);

		fscanf(fichier, "%s ", buff);
		fscanf(fichier, "%d ", &val);
		g->oriente = val;

		fscanf(fichier, "%s ", buff);
		fscanf(fichier, "%d ", &val);
		g->value = val;

		fscanf(fichier, "%s ", buff);
		fscanf(fichier, "%d ", &val);
		g->complet = val;

		fscanf(fichier, "%s ", buff);
		if (g->oriente == 1) {
			while (strcmp(buff, "finDefAretes") != 0) {
				fscanf(fichier, "%s", buff);
				if (strcmp(buff, "finDefAretes") != 0) {
					indice = atoi(buff);
					fscanf(fichier, "%s", buff);
					x = atoi(buff);
					fscanf(fichier, "%s", buff);
					poids = atoi(buff);
					insererListeAdj(g->l, indice, x, poids);
				}
			}
		} else {
			while (strcmp(buff, "finDefAretes") != 0) {
				fscanf(fichier, "%s", buff);
				if (strcmp(buff, "finDefAretes") != 0) {
					indice = atoi(buff);
					fscanf(fichier, "%s", buff);
					x = atoi(buff);
					fscanf(fichier, "%s", buff);
					poids = atoi(buff);
					insererListeAdj(g->l, indice, x, poids);
					insererListeAdj(g->l, x, indice, poids);
				}
			}
		}

	}
	fclose(fichier);
}

void afficherListesAdjacences(graphe *g) {
	afficherListeAdj(g->l);
}

void creerMatriceAdjacences(char *nomfichier, graphe *g) {
	int indice, x;
	char buff[255];
	int val;
	int poids;

	FILE *fichier;
	fichier = fopen(nomfichier, "r");

	if (fichier == NULL) {
		perror("Erreur lors de l'ouverture du fichier %s\n");
		exit(EXIT_FAILURE);
	} else {
		fscanf(fichier, "%s %d", buff, &val);
		g->nbSommet = val;

		g->matrice = (int **) malloc(sizeof(int *) * val);
		int i, j;
		for (i = 0; i < val; ++i)
			g->matrice[i] = (int *) malloc(sizeof(int) * val);
		for (i = 0; i < val; ++i) {
			for (j = 0; j < val; ++j)
				g->matrice[i][j] = 0;
		}


		fscanf(fichier, "%s %d", buff, &val);
		g->oriente = val;

		fscanf(fichier, "%s %d", buff, &val);
		g->value = val;

		fscanf(fichier, "%s %d", buff, &val);
		g->complet = val;

		fscanf(fichier, "%s ", buff);
		if (g->oriente == 1) {
			while (strcmp(buff, "finDefAretes") != 0) {
				fscanf(fichier, "%s", buff);
				if (strcmp(buff, "finDefAretes") != 0) {
					indice = atoi(buff);
					fscanf(fichier, "%s", buff);
					x = atoi(buff);
					fscanf(fichier, "%s", buff);
					poids = atoi(buff);
					g->matrice[indice][x] = poids;
				}
			}
		} else {
			while (strcmp(buff, "finDefAretes") != 0) {
				fscanf(fichier, "%s", buff);
				if (strcmp(buff, "finDefAretes") != 0) {
					indice = atoi(buff);
					fscanf(fichier, "%s", buff);
					x = atoi(buff);
					fscanf(fichier, "%s", buff);
					poids = atoi(buff);
					g->matrice[indice][x] = poids;
					g->matrice[x][indice] = poids;
				}
			}
		}
	}
	fclose(fichier);
}

void afficherMatriceAdjacences(graphe *g) {
	int i, j;
	for (i = 0; i < g->nbSommet; ++i) {
		for (j = 0; j < g->nbSommet; ++j)
			printf(" %2d\t", g->matrice[i][j]);
		printf("\n");
	}
}

graphe *creerGraphe(char *nomfichier) {
	graphe *g = (graphe *) malloc(sizeof(graphe));
	creerListesAdjacences(nomfichier, g);
	creerMatriceAdjacences(nomfichier, g);
	return g;
}

void detruireGraphe(graphe **g) {
	detruireListeAdj(&(*g)->l);
	int i;
	for (i = 0; i < (*g)->nbSommet; ++i) {
		free((*g)->matrice[i]);
	}
	free((*g)->matrice);
	free(*g);
	*g = NULL;
}