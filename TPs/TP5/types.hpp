/* ----------------------------------------------------------------- 
 * définition des structures  nécessaire pour représenter une matrice
 * d'adjacence sous forme de matrice creuse.
 * -----------------------------------------------------------------
 */

/*
 * structure d'un maillon de la liste chaînée associé 
 * à chaque ligne de la matrice
 */
struct Maillon {
  int col; // numéro de la colonne à laquelle correspond le coefficient
  int coef;// coefficient de la matrice
  Maillon *suiv;// élément suivant non nul sur la ligne
} ;

/*
 * structure représentant une matrice d'adjacence sous forme
 * de matrice creuse. La structure contient un tableau de lignes, chaque
 * ligne étant rerpésentée par une liste chaînée de "maillons".
 */
struct MatriceAdjacence {
  int ordre; // nombre de sommets du graphe
  Maillon* *lignes;// tableau à allouer de taille "ordre", représentant les lignes de la matrice
};



/*
 * type énuméré permettant de représenter les couleurs
 */
enum Couleur {BLANC, GRIS, NOIR};

// valeur indéfinie pour un indice de parent
#define INDEFINI  -1

// valeur infinie pour une distance enre sommets
#define INFINI  1e+100




