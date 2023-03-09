struct MaillonPile
{
    int valeur;
    MaillonPile *dessous;
};

struct Pile
{
    MaillonPile *sp;
};



struct Maillon {
  int col; // numéro de la colonne à laquelle correspond le coefficient
  int coef;// coefficient de la matrice
  Maillon *suiv;// élément suivant non nul sur la ligne
} ;

struct MatriceAdjacence {
  int ordre; // nombre de sommets du graphe
  Maillon* *lignes;// tableau à allouer de taille "ordre", représentant les lignes de la matrice
};

// valeur indéfinie pour un indice de parent
#define INDEFINI  -1
// valeur infinie pour une distance enre sommets
#define INFINI  -1
enum Couleur {BLANC, GRIS, NOIR};