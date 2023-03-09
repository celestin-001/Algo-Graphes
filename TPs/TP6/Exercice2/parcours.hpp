

/* fonctions implantant l'algorithme de Dijkstra */
void afficherCheminVers(int sf, int *parent);
void rechercheCheminMinimum(MatriceAdjacence mat,
			    float *distances, int *parents, Couleur *couleurs,
			    int sommetDepart);
/* fonction d'affichage du contenu des tableaux */
/* et des chemins les plus courts */
void affichages(MatriceAdjacence mat, float *distances, int *parents, int sommetdepart);