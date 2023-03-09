/*
Nom:Goumou
Prenoms:Celestin M'bemba
L2 Info ULCO
*/

#include <iostream>
#include <fstream>
using namespace std;

#include "types.hpp"



/* pré-définition des fonctions utilisées dans ce module
 * Le code des fonctions est donnée après la fonction main
 */
void creerMatrice(MatriceAdjacence &m, int taille);
void effacerMatrice(MatriceAdjacence &mat);
void afficher(MatriceAdjacence mat);
bool charger(char *nom, MatriceAdjacence &mat);
void rechercheCheminMinimum(MatriceAdjacence mat,int s,Couleur *coul,double *dist,int *parent);
int SommetBlancMinimum(MatriceAdjacence mat,Couleur *coul,double *dist);
int getCoeff(MatriceAdjacence &mat, int l, int c);
void afficherCheminVers(int sf,int *parent);
bool convertir(char *fichierIn, char *fichierOut);


  
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
  int *parent=new int[mat.ordre];
  double *dist=new double[mat.ordre];
  Couleur *coul=new Couleur[mat.ordre];
  rechercheCheminMinimum(mat,sommetDepart,coul,dist,parent);

  
  //afficher(mat);
  for(int i=0;i<mat.ordre;i++){
    if(i!=sommetDepart){
      if(parent[i]==INDEFINI){
        cout<<"Pas de chemin de ";afficherCheminVers(i,parent);cout<<" vers "<<i;
        cout<<endl;
      }
      else{
        cout<<"Chemin vers "<<i<<" ( lg = "<<dist[i]<<" ) = ";afficherCheminVers(i,parent);
        cout<<endl;
      }
      
      
    }
    
  }

  //convertir("Data/matrice01.txt", "test.txt");
  
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
int getCoeff(MatriceAdjacence &mat, int l, int c) {

  int i = 1;

  Maillon *maillon = mat.lignes[l];
  Maillon *prec = nullptr;

  while (maillon != nullptr) {
    if (maillon->col == c) {
      return maillon->coef;
    }
    prec = maillon;
    maillon = maillon->suiv;
    i++;
  }

  return -1;
}

void rechercheCheminMinimum(MatriceAdjacence mat,int s,Couleur *coul,double *dist,int *parent){

  for(int i=0;i<mat.ordre;i++){
    coul[i]=BLANC;
    dist[i]=INFINI;
    parent[i]=INDEFINI;
  }
  
  
  dist[s]=0;
  parent[s]=INDEFINI;
  for(int j=0;j<mat.ordre;j++){
    int u=SommetBlancMinimum(mat,coul,dist);
    while(coul[u]==BLANC){
      for(int i=0;i<mat.ordre;i++){
        if(u!=i){
          int coef=getCoeff(mat,i,u);
          if(coef!=-1){
            if(coul[i]==BLANC){
              if(dist[i]>dist[u]+getCoeff(mat,u,i)){
                dist[i]=dist[u]+getCoeff(mat,u,i);
                parent[i]=u;
              }
            }
          }
        }
        
      
        
      }
    
      coul[u]=NOIR;
    }
  }
  


}

int SommetBlancMinimum(MatriceAdjacence mat,Couleur *coul,double *dist){

  double vmin=INFINI; int smin;
   for(int i=0;i<mat.ordre;i++){
    if(coul[i]==BLANC){
      if(dist[i]<=vmin){
        vmin=dist[i];
        smin=i;
      }
    }
  }
  
  return smin;
}

void afficherCheminVers(int sf,int *parent){
  
    
    if(parent[sf]==INDEFINI){
      cout<<" "<<sf<<" ";
    }
    else{
      afficherCheminVers(parent[sf],parent);
      cout<<sf<<" ";
    }
      
      
    
}


