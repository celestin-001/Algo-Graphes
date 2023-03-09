/*
Nom:Goumou
Prenoms:Celestin M'bemba
L2 Info ULCO
*/

#include <fstream>
#include <iostream>
using namespace std;
#include "types.hpp"

void creerMatrice(MatriceAdjacence &mat, int size);
bool charger(char *nomFichier, MatriceAdjacence &mat); 
void afficher(MatriceAdjacence mat);
void effacerMatrice(MatriceAdjacence &mat);
int getCoeff(MatriceAdjacence &mat, int l, int c) ;
bool estComplet(MatriceAdjacence mat);
void initialiser(Fifo &file);
bool estVide(Fifo file);
void ajouter(Fifo &file, int val);
int retirer(Fifo &file);
int getCoeff(MatriceAdjacence &mat, int l, int c);
void parcoursEnLargeur(MatriceAdjacence mat, int sommetDepart,Couleur *coul, int *dist, int *parent);
void afficherInfos(MatriceAdjacence mat, Couleur *coul,int *parent,int *dist);
void afficherCheminVers(int sf,int i, int *parent);




int main(int argc, char *argv[]) {
  MatriceAdjacence mat;
  int numeroDuSommetDeDepart;
  
  char *fic = argv[1];
  numeroDuSommetDeDepart=stoi(argv[2]);
  charger(fic, mat);
  // effacerMatrice(mat);
  if (argc != 3) {
    cout << endl << "Error";
  } else {
    afficher(mat);
  }
  
  Couleur *coul=new Couleur[mat.ordre];
  int *dist=new int[mat.ordre];
  int *parent=new int[mat.ordre];
  
 
  /*for(int i=0;i<mat.ordre;i++){
    coul[i]=BLANC;
    dist[i]=INFINI;
    parent[i]=INDEFINI;
  }*/
  parcoursEnLargeur(mat, numeroDuSommetDeDepart,coul,  dist,parent);
  afficher(mat);
    cout<<"--------------------------------------------------------------"<<endl;
  afficherInfos( mat,  coul,parent,dist);
  cout<<"--------------------------------------------------------------"<<endl;
  for(int i=0;i<mat.ordre;i++){
    if(i!=numeroDuSommetDeDepart){
      cout<<"Chemin vers "<<i<<" = ";
       afficherCheminVers(numeroDuSommetDeDepart,i, parent);
       cout<<endl;
    }
   
  }
  
  //cout<<getCoeff(mat,1,6)<<"  f"<<endl;
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
bool estComplet(MatriceAdjacence mat) {
  for(int i=0;i<mat.ordre;i++){
   int j=0;
   Maillon *cur=mat.lignes[i];
    while(cur!=nullptr && j!=cur->col){
      j++;
      cur=cur->suiv;
    }
    if(j==mat.ordre-1){
      return true;
    }
}
  return false;
}


void initialiser(Fifo &file){
    
    file.in=nullptr;
    file.out=nullptr;
}

bool estVide(Fifo file){
    if(file.in==nullptr){
        return true;
    }
    else{
        return false;
    }
}

void ajouter(Fifo &file, int val){
    MaillonEntier *maillon=new MaillonEntier;
    maillon->valeur=val;
    maillon->prec=nullptr;
    if(estVide(file)){
        file.in=maillon;
        file.out=maillon;
    }
    else{
        if(file.in->prec==nullptr){
            maillon->suiv=file.in;
            file.in->prec=maillon;
            file.in=maillon;
        }
        else{
            MaillonEntier *cur=file.in->prec;
            MaillonEntier *prec=nullptr;;
            while(cur!=nullptr){
                prec=cur;
                cur=cur->prec;
            }
            maillon->suiv=prec;
            prec->prec=maillon;
            file.in=maillon;

        }
    }
    
}
int retirer(Fifo &file){
    int val=0;
    if(file.out==file.in){
        val=file.out->valeur;
        file.out=nullptr;
        file.in=nullptr;
        return val;
    }
    MaillonEntier *maillon=file.out->prec;
    val=maillon->suiv->valeur;
    maillon->suiv=nullptr;
    file.out=maillon;
    return val;


}



void parcoursEnLargeur(MatriceAdjacence mat, int sommetDepart,Couleur *coul, int *dist, int *parent){

    
    for(int i=0;i<mat.ordre;i++){
        coul[i]=BLANC;
        dist[i]=INFINI;
        parent[i]=INDEFINI;

    }
    coul[sommetDepart]=BLANC;
    dist[sommetDepart]=0;
    parent[sommetDepart]=INDEFINI;
    Fifo file;
    initialiser(file);
    ajouter(file,sommetDepart);
    while(!estVide(file)){
        int cur=retirer(file);//retire sommetDepart(la première valeur entrée) et recupère sa valeur
        for(int i=0;i<mat.ordre;i++){
            if(i!=cur){
                int coeff=getCoeff(mat,i,cur);
                if(coeff==1){
                    if(coul[i]==BLANC){
                        coul[i]=GRIS;
                        dist[i]=dist[cur]+1;
                        parent[i]=cur;
                        ajouter(file,i);
                    }
                    
                    
                }
            }coul[cur]=NOIR;
        }
      
    }


   
}


void aff(Fifo f){
    if(f.in!=nullptr){
        MaillonEntier *cur=f.in;
        while(cur!=nullptr){
            cout<<cur->valeur<<" ";
            cur=cur->suiv;
        }
        cout<<endl;
    }
}


void afficherInfos(MatriceAdjacence mat, Couleur *coul,int *parent,int *dist){
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
    cout<<"Distances : ";
    while(j<mat.ordre){
        if(dist[j]==INFINI){
            cout<<"X ";
        }
        else{
            cout<<dist[j]<<" ";
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
        cout<<"Pas de chemin de "<<sf<<" vers "<<i<<endl;
        
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
