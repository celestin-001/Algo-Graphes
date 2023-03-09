#include <fstream>
#include <iostream>
using namespace std;
struct Maillon {
  int col;       // num´ero de la colonne `a laquelle correspond le coefficient
  int coef;      // coefficient de la matrice
  Maillon *suiv; // ´el´ement suivant non nul sur la ligne
};
struct MatriceAdjacence {
  int ordre;        // nombre de sommets du graphe
  Maillon **lignes; // tableau `a allouer de taille "ordre", repr´esentant les
                    // lignes de la matrice
};
struct MaillonEntier {
int valeur; // valeur stockée dans le maillon
MaillonEntier *suiv;// élément suivant dans la file
MaillonEntier *prec;// élément précédent dans la file
} ;

struct Fifo {
MaillonEntier *in;// pointeur vers le début de la liste
MaillonEntier *out;// pointeur vers la fin de la liste
};
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
  
  if(estComplet(mat)==true){
    cout<<"La matrice est complete"<<endl;
  }
  else{
    cout<<"La matrice est complete n'est pas  complete"<<endl;
  }
 
  
  //cout<<getCoeff(mat,1,6)<<"  f"<<endl;
  effacerMatrice(mat);
  
}