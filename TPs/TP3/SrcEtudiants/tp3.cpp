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
void initialiser(Fifo &file);
bool estVide(Fifo file);
void ajouter(Fifo &file, int val);
int retirer(Fifo &file);
int getCoeff(MatriceAdjacence &mat, int l, int c);
void parcoursEnLargeur(MatriceAdjacence mat, int sommetDepart,Couleur *coul, int *dist, int *parent);
void afficherInfos(MatriceAdjacence mat, Couleur *coul,int *parent,int *dist);
void afficherCheminVers(int sf,int i, int *parent);

int main(int argc, char *argv[]){
  
  if(argc!=2){
    cout << "Erreur - il manque le nom du fichier à lire\n";
    return -1;
  }

  MatriceAdjacence mat;

  //if(!charger(argv[1], mat)) return -1;

  afficher(mat);


  effacerMatrice(mat);
  
  return 1;
}


void creerMatrice(MatriceAdjacence &m, int taille){
  // raz éventuelle de la matrice
  if(m.lignes!=nullptr) delete m.lignes;
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
  mat.lignes = nullptr;
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
  
  int v; // coefficient lu

  for(int l=0; l<mat.ordre; l++){ // lire et créer une ligne complète
    Maillon *fin=nullptr;// pointeur vers la fin d'une liste chaînée
    for(int c=0; c<mat.ordre; c++){ // lire et créer chaque colonne de la ligne courante
      in >> v;// lecture du coefficient (0 ou 1)
      if(v!=0){// créer un maillon et l'insérer en fin de liste
	// créer un nouveau maillon
	Maillon *nouveau = new Maillon;
	nouveau->col = c;
	nouveau->coef = v;
	nouveau->suiv = nullptr;
	// insérer le maillon en fin de liste
	if(fin!=nullptr){// il y a déjà des éléments dans la liste
	  fin->suiv = nouveau;// insertion en fin
	  fin = nouveau;// maj du pointeur vers le dernier élément de la liste
	}else{// c'est le premier coefficient de la liste
	  mat.lignes[l] = nouveau;// ajout au début de la liste
	  fin = nouveau;// maj du pointeur vers le dernier élément de la liste
	}
      }// if - rien à faire si v vaut 0
    }// for c
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
        dist[i]=-1;
        parent[i]=-1;

    }
    coul[sommetDepart]=BLANC;
    dist[sommetDepart]=0;
    parent[sommetDepart]=INDEFINI;
    Fifo file;
    initialiser(file);
    ajouter(file,sommetDepart);
    while(!estVide(file)){
        int cur=retirer(file);//define sommetDepart(la première valeur entrée) et recupère sa valeur
        for(int i=0;i<mat.ordre;i++){
            if(i!=cur){
                int coeff=getCoeff(mat,i,cur);
                if(coeff==1){
                    if(coul[i]==BLANC){
                        coul[i]=GRIS;
                        dist[i]=dist[cur]+1;
                        parent[i]=cur;
                        ajouter(file,i);
                    }coul[cur]=NOIR;
                    
                }
            }
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
    cout<<"Couleurs : ";
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
    cout<<"Parents : ";
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


