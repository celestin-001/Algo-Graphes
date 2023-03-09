#include <iostream>
#include <fstream>
using namespace std;
#include "types.hpp"




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