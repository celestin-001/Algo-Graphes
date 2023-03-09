/*
Nom:Goumou
Prenoms:Celestin M'bemba
L2 Info ULCO
*/

#include <iostream>
#include <fstream>
#include "types.hpp"
using namespace std;


void creerMatrice(MatriceAdjacence &mat, int size);
bool charger(char *nomFichier, MatriceAdjacence &mat); 
void afficher(MatriceAdjacence mat);
void effacerMatrice(MatriceAdjacence &mat);
void initialiser(Pile &p);
bool estVide(Pile &p);
void empiler(Pile &p,int v);
int depiler(Pile &p);
void parcoursEnProfondeur(MatriceAdjacence mat,Couleur *coul, int *parent);
void explorer(MatriceAdjacence mat,int sommetDepart,Couleur *coul, int *parent);
void ParcoursEnProfondeurRecursif(MatriceAdjacence mat,Couleur *coul,int *parent);
int getCoeff(MatriceAdjacence &mat, int l, int c);
void afficherInfos(MatriceAdjacence mat, Couleur *coul,int *parent);
void vider(Couleur *coul,int *parent);
void afficherCheminVers(int sf,int i, int *parent);

int main(int argc,char *argv[]){

    MatriceAdjacence mat;
  int numeroDuSommetDeDepart;
  
  char *fic = argv[1];
  numeroDuSommetDeDepart=stoi(argv[2]);
  charger(fic, mat);
  if (argc != 3) {
    cout << endl << "Error";
  } else {
    afficher(mat);
  }
  
  Couleur *coul=new Couleur[mat.ordre];
  int *parent=new int[mat.ordre];
  ParcoursEnProfondeurRecursif(mat,coul, parent);
  cout<<"Methode recursive"<<endl;
  cout<<"--------------------------------------------------------------"<<endl;
  afficherInfos( mat,  coul,parent);
  cout<<"--------------------------------------------------------------"<<endl;
  cout<<endl;
  cout<<"Methode non recursive"<<endl;
  parcoursEnProfondeur(mat,coul, parent);
  cout<<"--------------------------------------------------------------"<<endl;
  afficherInfos( mat,  coul,parent);
  cout<<"--------------------------------------------------------------"<<endl;
  cout<<endl;
   for(int i=0;i<mat.ordre;i++){
    
      cout<<"Chemin vers "<<i<<" = ";
      afficherCheminVers(numeroDuSommetDeDepart,i, parent);
      cout<<endl;
    
   
  }
  effacerMatrice(mat);
  
    
}


void creerMatrice(MatriceAdjacence &mat, int size) {
  mat.ordre = size;
  mat.lignes = new Maillon *[mat.ordre];
  for (int i = 0; i < mat.ordre; i++) {
    mat.lignes[i] = nullptr;
  }
}

bool charger(char *nomFichier, MatriceAdjacence &mat) {
  ifstream fichier;
  fichier.open(nomFichier, ios::in);
  if (fichier.is_open() == false) {
    cout << "erreur d’ouverture " << endl;
    return false;
  }
  int val;
  fichier >> val;
  creerMatrice(mat, val);

  int coeff;
  for (int i = 0; i < mat.ordre; i++) {

    for (int j = 0; j < mat.ordre; j++) {
      
      Maillon *maillon = new Maillon;
      maillon->suiv = nullptr;
      
      fichier >> coeff;
      if (coeff != 0) {
        maillon->coef = coeff;
        maillon->col = j;
        if (mat.lignes[i] == nullptr) {

          mat.lignes[i] = maillon;

          // mat.lignes[i]->suiv=nullptr;
        } else {
          Maillon *cur = mat.lignes[i]; // pointeur de parcours
          Maillon *prec = nullptr;
          while (cur != nullptr) {
            prec = cur;
            cur = cur->suiv;
          }
          prec->suiv = maillon;
        }
      }
    }
  }
  fichier.close();
  return true;
}

void afficher(MatriceAdjacence mat){
  
    for(int i=0;i<mat.ordre;i++){
        Maillon *cur=mat.lignes[i];
        for(int j=0;j<mat.ordre;j++){
            
            
            
            int s=0;
            if(cur!=nullptr){
                
                if(cur->col==j){
                    s=cur->coef;
                   cur=cur->suiv;
                   
                     
                }
                
                
            }
            
           cout<<s<<" ";
           
            
            
        }
        
        
        cout<<endl;
    }
}
void effacerMatrice(MatriceAdjacence &mat) {
  for (int i = 0; i < mat.ordre; i++) {
    Maillon *cur;
    while (mat.lignes[i] != nullptr) {
      cur = mat.lignes[i];
      mat.lignes[i] = mat.lignes[i]->suiv;
      delete cur;
    }
    mat.ordre = 0;
  }
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

  return 0;
}

void initialiser(Pile &p){

    p.sp=nullptr;

}

bool estVide(Pile &p){
    return (p.sp==nullptr);
}

void empiler(Pile &p, int v){
    MaillonPile *maillon=new MaillonPile;
    maillon->valeur=v;
    if(estVide(p)){
        maillon->dessous=nullptr;
        p.sp=maillon;
    }
    
    else{
        maillon->dessous=p.sp;
        p.sp=maillon;
    }
}
int depiler(Pile &p){

    int val=p.sp->valeur;
    MaillonPile *maillon=p.sp;
    p.sp=maillon->dessous;
    return val;

}


void parcoursEnProfondeur(MatriceAdjacence mat,Couleur *coul, int *parent){
    for(int i=0;i<mat.ordre;i++){
        coul[i]=BLANC;
        parent[i]=INDEFINI;
    }
    
    for(int j=0;j<mat.ordre;j++){
           coul[j]=GRIS;
    
    
    Pile pile;
    initialiser(pile);
    empiler(pile,j);
      while(!estVide(pile)){
         
        int cur=depiler(pile);//retire sommetDepart(la dernière valeur entrée) et recupère sa valeur
        for(int i=0;i<mat.ordre;i++){
            if(i!=cur){
             
                int coeff=getCoeff(mat,i,cur);
                if(coeff==1){
                  
                    if(coul[i]==BLANC){
                        coul[i]=GRIS;
                        
                        parent[i]=cur;
                        empiler(pile,cur);
                        empiler(pile,i);
                        break;
                        
                        //depiler(pile);
                    }
                    
                    
                }
            }
        }
        
        coul[cur]=NOIR;
      
    }
    }
 



}
void explorer(MatriceAdjacence mat,int sommetDepart,Couleur *coul, int *parent){

  coul[sommetDepart]=GRIS;

  for(int i=0;i<mat.ordre;i++){
    int coeff=getCoeff(mat,i,sommetDepart);
    if(sommetDepart!=i && coeff==1){
        if(coul[i]==BLANC){
          parent[i]=sommetDepart;
          explorer(mat,i,coul,parent);
        }
    }
  }coul[sommetDepart]=NOIR;


}
void ParcoursEnProfondeurRecursif(MatriceAdjacence mat,Couleur *coul,int *parent){

  for(int i=0;i<mat.ordre;i++){
    coul[i]=BLANC;
    parent[i]=INDEFINI;
  }
  for(int j=0;j<mat.ordre;j++){
    if(coul[j]==BLANC){
      explorer(mat,j,coul,parent);
    }
    
  }

}
void vider(Couleur *coul,int *parent){
  int i=0;
  while(i<sizeof(coul)){
    coul[i]=BLANC;
    parent[i]=INDEFINI;
  }
}

void afficherInfos(MatriceAdjacence mat, Couleur *coul,int *parent){
    int j=0;
    cout<<"Couleurs  : ";
    while(j<mat.ordre){
        if(coul[j]==BLANC){
            cout<<"B ";
        }
        else{
            cout<<"N ";
        }
        j++;
    }
    cout<<endl;
    j=0;
    cout<<"Parents   : ";
    while(j<mat.ordre){
        if(parent[j]==INDEFINI){
            cout<<"X ";
        }
        else{
            cout<<parent[j]<<" ";
        }
        j++;
    }
    cout<<endl;
    
}
void afficherCheminVers(int sf,int i, int *parent){
  
    
    if(parent[i]==INDEFINI){
      if(i!=sf){
        cout<<"Pas de chemin de "<<i<<" vers "<<sf<<endl;
        
      }
      else{
        cout<<sf<<" ";
      }
      
      
    }
    else{
      
      afficherCheminVers(sf,parent[i],parent);
      cout<<i<<" ";
    }
     
}










