#include <iostream>
#include <fstream>
using namespace std;

#include "types.hpp"

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