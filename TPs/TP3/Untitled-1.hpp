#include <iostream>
#include <string>

using namespace std;


struct MaillonEntier {
int valeur; // valeur stockée dans le maillon
MaillonEntier *suiv;// élément suivant dans la file
MaillonEntier *prec;// élément précédent dans la file
} ;

struct Fifo {
MaillonEntier *in;// pointeur vers le début de la liste
MaillonEntier *out;// pointeur vers la fin de la liste
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

    coul=new Couleur[mat.ordre];
    dist=new int[mat.ordre];
    parent=new int[mat.ordre];
    for(int i=0;i<mat.ordre;i++){
        coul[i]=BLANC;
        dist[i]=INFINI;
        parent[i]=INDEFINI;

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









int main(void){

Fifo f;
initialiser(f);

//cout<<estVide(f);
ajouter(f,1);
ajouter(f,2);
ajouter(f,3);
cout<<retirer(f)<<" ";
cout<<retirer(f)<<" ";
cout<<retirer(f)<<" ";

//aff(f);


}