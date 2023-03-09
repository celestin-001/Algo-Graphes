#include <fstream>
#include <iostream>
using namespace std;

// représentation d'un matrice d'adjacence
struct MatriceAdjacence {
  int ordre; // nombre de sommets du graphe
  int *coef; // tableau contenant les (ordre x ordre) coefficients de la matrice
};

void creerMatrice(MatriceAdjacence &mat, int size) {
  mat.ordre=size;
  mat.coef = new int[mat.ordre * mat.ordre];
  for (int i = 0; i < mat.ordre; i++) {
    for (int j = 0; j < mat.ordre; j++) {
      mat.coef[i * mat.ordre + j] = 0;
    }
  }
}
void afficher(MatriceAdjacence mat) {
  for (int i = 0; i < mat.ordre; i++) {
    for (int j = 0; j < mat.ordre; j++) {
      cout << mat.coef[i * mat.ordre + j] << " ";
    }
    cout << endl;
  }
}
bool charger(string nomFichier, MatriceAdjacence &mat) {
  ifstream fic;
  fic.open(nomFichier, ios::in);

  if (fic.is_open() == false) {
    cout << "Erreur de chargement" << endl;
    return false;
  } else {
    int val;
    fic >> val;
    creerMatrice(mat, val);
    for (int i = 0; i < val; i++) {

      for (int j = 0; j < val; j++) {
        
        fic >> mat.coef[i * val + j];
        
        
      }
    }
    fic.close();
    return true;
    
  }
}
bool estComplet(MatriceAdjacence mat){
  bool result;
  for(int i=0; i<mat.ordre;i++){
    for (int i = 0; i < mat.ordre; i++) {
      for (int j = 0; j < mat.ordre; j++) {
        if(i!=j){
            if(mat.coef[i*mat.ordre+i]==0 || mat.coef[i*mat.ordre+i]==1){
              if(j!=i && mat.coef[i*mat.ordre+j]==1){
                  result=true;
              }
              else{
                result=false;
              }
            }
        }
      }
    }
  }
  
  return result;
}
bool estSymetrique(MatriceAdjacence mat){
  bool result; int val=mat.coef[0];
for(int i=0; i<mat.ordre;i++){
    for (int i = 0; i < mat.ordre; i++) {
      for (int j = 0; j < mat.ordre; j++) {
        if(i!=j){
            if(mat.coef[i*mat.ordre+i]==0){
              
              
              if(j!=i && mat.coef[i*mat.ordre+j]==mat.coef[j*mat.ordre+i]){
                  
                  result=true;
              }
              else{
                result=false;
              }
            }
        }
      }
    }
  }
  return result;
}
bool estIsole(MatriceAdjacence mat, int i){
  bool result;
  for (int j = 0; j < mat.ordre; j++) {
        
          
          if(mat.coef[j*mat.ordre+i]!=0){
            return false;
          }
          
        
  }
  return true;
}
void afficherDegresNonOriente(MatriceAdjacence mat){
  
  for(int i=0;i<mat.ordre;i++){
    int somme=0;
    
    for(int j=0;j<mat.ordre;j++){
      if(mat.coef[i*mat.ordre+j]==1){
        somme++;
        //cout<<somme<<" ";
      }
      
    }
    cout<<"Le sommet "<<i<<" Possède "<<somme<<" arètes"<<endl;
  }
}
void afficherDegresOriente(MatriceAdjacence mat){
  for(int i=0;i<mat.ordre;i++){
    int somme=0;
    
    for(int j=0;j<mat.ordre;j++){
      if(mat.coef[i*mat.ordre+j]==1){
        somme++;
        //cout<<somme<<" ";
      }
      
    }
    if(mat.coef[i*mat.ordre+i]==1){
      somme=somme+1;
    }
    
    cout<<"Le sommet "<<i<<" Possède "<<somme<<" arètes"<<endl;
  }
}

int main(int argc, char *argv[]) {

  int size;
  char *fic=argv[1];
  //string s = "Data/matrice04.txt";
  MatriceAdjacence mat;
  charger(fic, mat);
  
  
  if (argc != 2) {
    cout << endl << "Error";
  } else {
    afficher(mat);
  }
  cout<<"-------------------------------------------------"<<endl;
  //estComplet(mat);
  if(estComplet(mat)){
    cout<<"La matrice d'adjacence est complete"<<endl;
  }
  else{
    cout<<"La matrice d'adjacence n'est pas complete"<<endl;
  }
  int i=0;
  while(i<mat.ordre){
    if(estIsole( mat, i)){
      cout<<"Ce noeud est isolé"<<endl;
    }
    else{
      cout<<"Ce noeud n'est pas isolé"<<endl;
    }
    i++;
  }
    
  cout<<"-------------------------------------------------"<<endl;
  afficherDegresNonOriente( mat);
  cout<<"-------------------------------------------------"<<endl;
  afficherDegresOriente( mat);
  return 1;
}
