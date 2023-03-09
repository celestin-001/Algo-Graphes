#include <iostream>
#include <fstream>
using namespace std;


#include "types.hpp"
#include "parcours.hpp"
#include "matrice.hpp"
#define GRAPHIQUES

#ifdef GRAPHIQUES
#include "graphique.hpp"
#endif


int main(int argc, char *argv[]){
  cout<<"=======CELESTIN MBEMBA GOUMOU======="<<endl;
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
  
  return -1;
}