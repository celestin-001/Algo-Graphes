#include <iostream>
#include <fstream>
using namespace std;

// ligne suivante à décommenter pour l'exercice 2
//#define GRAPHIQUES

#include "types.hpp"

#ifdef GRAPHIQUES
#include "graphique.hpp"
#endif

/**
 * Licence Informatique 2eme année - ULCO
 * correction du TP5 du module d'algorithmique
 * consacré aux graphes. Année 2020-2021
 * Algorithme de Dijkstra
 * Auteur : C. Renaud
 */

/* pré-définition des fonctions utilisées dans ce module
 * Le code des fonctions est donnée après la fonction main
 */
void creerMatrice(MatriceAdjacence &m, int taille);
void effacerMatrice(MatriceAdjacence &mat);
void afficher(MatriceAdjacence mat);
bool charger(char *nom, MatriceAdjacence &mat);



/* fonctions implantant l'algorithme de Dijkstra */
void afficherCheminVers(int sf, int *parent);
void rechercheCheminMinimum(MatriceAdjacence mat,
			    float *distances, int *parents, Couleur *couleurs,
			    int sommetDepart);

/* fonction d'affichage du contenu des tableaux */
/* et des chemins les plus courts */
void affichages(MatriceAdjacence mat, float *distances, int *parents, int sommetdepart);
  
int main(int argc, char *argv[]){
  
  if(argc!=3){
    cout << "Syntaxe : " << argv[0] << " <file>  <indice_sommet_depart>" << endl;
    return -1;
  }

  MatriceAdjacence mat;

  if(!charger(argv[1], mat)) return -1;

  int sommetDepart = atoi(argv[2]);
  if(sommetDepart <0 || sommetDepart >= mat.ordre){
    cout << "indice de sommet " << sommetDepart << " incorrect ! ";
    cout << "valeurs autorisées dans [0," << mat.ordre-1 << "]" << endl;
    effacerMatrice(mat);
    return -1;
  }
  

  afficher(mat);

  // créer les tableaux à remplir par le parcours en largeur
  bool *traites = new bool[mat.ordre];
  float *distances = new float[mat.ordre];
  int *parents = new int[mat.ordre];
  Couleur *couleurs = new Couleur[mat.ordre];

  rechercheCheminMinimum(mat, distances, parents, couleurs, sommetDepart);
  
  affichages(mat, distances, parents, sommetDepart);

#ifdef GRAPHIQUES
  // ------ affichages graphiques -----

  // création de la fenêtre
  if(createWindow(mat)==EXIT_FAILURE){
    cout << "erreur de création de la fenêtre" << endl;
    return 0;
  }

  // affichage du graphe
  drawGraph(mat);

  // affichage des plus courts chemins
  drawPaths(mat, parents);

  // attendre l'appui sur une touche ou la fermeture de la fenêtre
  waitForEnd();

  // destruction de la fenêtre
  destroyWindow();
  
#endif

  // supprimer les tableaux
  delete traites;
  delete distances;
  delete parents;
  
  return 1;
}


void creerMatrice(MatriceAdjacence &m, int taille){
  // initialisation du nombre de lignes/colonnes de la matrice
  m.ordre = taille;
  // allocation mémoire du tableau de lignes
  m.lignes = new Maillon*[taille];
  // initialisation de chaque ligne à "vide"
  for(int i=0; i<taille; i++) m.lignes[i]=nullptr;
}

void effacerMatrice(MatriceAdjacence &mat){
  for(int l=0; l<mat.ordre; l++){// effacer chaque ligne
    while(mat.lignes[l]!=nullptr){// tq la ligne n'est pas vide
      // effacer le premier élément qui s'y trouve
      Maillon *cour = mat.lignes[l];// 1er élément de la liste
      mat.lignes[l] = cour->suiv;// élément suivant éventuel
      delete cour; // effacer le 1er élement courant
    }
  }
  // effacer le tableau de lignes
  delete mat.lignes;
  // raz de la taille
  mat.ordre = 0;
      
}

bool charger(char *nom, MatriceAdjacence &mat){
  ifstream in;
  
  in.open(nom, std::ifstream::in);
  if(!in.is_open()){
    printf("Erreur d'ouverture de %s\n", nom);
    return false;
  }

  int taille;
  in >> taille;

  // créer la matrice
  creerMatrice(mat, taille);
  

  for(int l=0; l<mat.ordre; l++){ // lire et créer une ligne complète
    Maillon *fin=nullptr;
    int col;// numéro de colonne lu
    int val; // valeur du coefficient lu
    in >> col;
    while(col!=-1){// lire les données de la colonne
      in >> val;
      // créer un maillon et l'insérer en fin de liste
      Maillon *nouveau = new Maillon;
      nouveau->col = col;
      nouveau->coef = val;
      nouveau->suiv = nullptr;
      if(fin!=nullptr){// il y a déjà des éléments dans la liste
	fin->suiv = nouveau;// insertion en fin
	fin = nouveau;// maj du pointeur vers le dernier élément de la liste
      }else{// c'est le premier coefficient de la liste
	mat.lignes[l] = nouveau;// ajout au début de la liste
	fin = nouveau;// maj du pointeur vers le dernier élément de la liste
      }
      // lire la colonne suivante
      in >> col;
    }
  }// for l

  in.close();
  return true;
}





void afficher(MatriceAdjacence mat){
  // affichage de chacune des lignes
  for(int l=0; l<mat.ordre; l++){// affichage de la ligne l
    int c=0;
    Maillon *mcur=mat.lignes[l];
    while(c<mat.ordre){
      if(mcur==nullptr){// le coefficients de la ligne >=c sont nuls
	cout << "0 ";
	c++;
      }else if(mcur->col != c){
	// on est sur un coefficient nul, qui se trouve avant c
	cout << "0 ";
	c++;
      }else{// afficher le coefficient
	cout << mcur->coef << " ";
	mcur = mcur->suiv;
	c++;
      }   
    }// while
    cout << endl;// fin de la ligne l
  }// for
}


void afficherCheminVers(int sf, int *parent){// version récursive
  if(parent[sf]!=INDEFINI){// on est sur un sommet intermédiaire
    afficherCheminVers(parent[sf], parent);
  }
  // afficher le sommet courant
  cout << sf << " ";

}


// recherche du chemin blanc de distance minimum
int sommetBlancMinimum(float *dist, Couleur *coul, int taille){
  float vmin=INFINI;
  int smin=-1;
  for(int i=0; i<taille; i++){
    if(coul[i]==BLANC && dist[i]<=vmin){
      vmin = dist[i];
      smin = i;
    }
  }

  return smin; 
}

// recherche du cehmin minimum entre un sommet de départ et
// l'ensemble des sommets d'un graphe orienté pondéré
// en suivant l'algorithme de Dijkstra
void rechercheCheminMinimum(MatriceAdjacence mat,
			    float *distances, int *parents, Couleur *couleurs,
			    int sommetDepart){

  // initialisation des tableaux
  for(int i=0; i<mat.ordre; i++){
    couleurs[i] = BLANC;
    distances[i] = INFINI;
    parents[i] = INDEFINI;
  }

  // initialisation du sommet de départ
  distances[sommetDepart] = 0;

  // tant que il existe des sommets blancs faire
  // on doit traiter tous les sommets
  int nbTraites = 0;
  while(nbTraites!=mat.ordre){
    int u = sommetBlancMinimum(distances, couleurs, mat.ordre);
    Maillon *cur = mat.lignes[u];
    while(cur){
      int v = cur->col;
      int poids = cur->coef;
      if(couleurs[v]==BLANC)
	if(distances[v]>distances[u]+poids){
	  distances[v]=distances[u]+poids;
	  parents[v] = u;
	}

      cur = cur->suiv;
    }

    couleurs[u] = NOIR;
    nbTraites++;
  }// while

}

void affichages(MatriceAdjacence mat, float *distances,
		int *parents, int sommetDepart){
 // affichage des distances
  cout << "distances : ";
  for(int i=0; i<mat.ordre; i++)
    if(distances[i]!=INFINI)
      cout << distances[i] << " ";
    else
      cout << "X ";
  cout << endl;
  
  // affichage des parents
  cout << "parents   : ";
  for(int i=0; i<mat.ordre; i++)
    if(parents[i]!=INDEFINI)
      cout << parents[i] << " ";
    else
      cout << "X ";
  cout << endl; 

  // affichage des chemins
  for(int i=0; i<mat.ordre; i++){
    if(i!=sommetDepart){
      if(distances[i]!=INFINI){// un chemin a été trouvé
	cout << "chemin vers " << i << " (lg = " << distances[i] << ") = ";
        afficherCheminVers(i, parents);
	cout << endl;
      }else{
	cout << "pas de chemin de " << sommetDepart << " vers " << i << endl;
      }
    }
  }

}
