#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

#include "types.hpp"

#define CELLSIZE 50 // taille d'un côté d'une case du labyrinthe
#define MARGE  10   // marge du dessin
#define TEXTSIZE 10 // taille d'affichage du texte

#define LARGEUR 10  // largeur par défaut du labyrinthe
#define HAUTEUR 10  // hauteur par défaut du labyrinthe

// --------------------------------------------------------------------
// prédéfinition des fonctions liées à la gestion d'un labyrinthe
// --------------------------------------------------------------------
void initialiserLabyrinthe(labyrinthe &laby, int largeur, int hauteur);

void effacerLabyrinthe(labyrinthe &laby);

void genererLabyrinthe(labyrinthe &laby);

void dessinerLabyrinthe(labyrinthe &laby, const string &nomFichier);

void creerMatrice(MatriceAdjacence &m, int taille);

void effacerMatrice(MatriceAdjacence &mat);

void afficherMatrice(MatriceAdjacence &mat);
void remplirMatrice(MatriceAdjacence &mat,const labyrinthe &lab);
void ajoutMaillon(MatriceAdjacence &m,Maillon *ajout,int pos);
void dessinerMatrice(const MatriceAdjacence &mat, const labyrinthe &laby, const string &nom);
void saisirCoordonnees(coordonnee &deb, coordonnee &fin, int largeur, int hauteur);
void initialiser(Fifo &file);
bool estVide(Fifo file);
void ajouter(Fifo &file, int val);
int retirer(Fifo &file);
chemin calculerChemin(const MatriceAdjacence &mat, coordonnee deb, coordonnee fin, int largeur,Couleur *coul,int *parent,int *dist);
void dessinerSolution(const labyrinthe &laby,chemin ch,  const string &nomFichier);
void dessinMur(const labyrinthe &laby,const ofstream &out);
// --------------------------------------------------------------------
// prédéfinition des fonctions liées à l'écriture dans les fichiers SVG
// --------------------------------------------------------------------

// création du fichier et ouverture du flot d'écriture associé
// retourne false si le fichier n'a pas pu être ouvert.
bool ouvrirFichierSVG(const string &nomFichier,// nom du fichier à créer
		      ofstream &out,// flot d'écriture ouvert par la fonction
		      int largeur, // largeur de l'image en pixels
		      int hauteur);// hauteur de l'image en pixels

// fermeture du flot d'écriture et du fichier associé
void fermerFichierSVG(ofstream &out);// flot d'écriture à fermer par la fonction

// écriture d'une ligne dans le flot de sortie
void ligne(ofstream &out,// flot d'écriture dans lequel ajouter la ligne
	   int x1, int y1,// coordonnées du point de départ de la ligne
	   int x2, int y2,// coordonnées du point d'arrivée de la ligne
	   const string& color,// couleur de tracé de la ligne
	   int width);// épaisseur de tracé de la ligne

// écriture d'un rectangle dans le flot de sortie
void rect(ofstream &out,// flot d'écriture dans lequel ajouter le rectangle
	  int x, int y,// coordonnées du point supérieur gauche du rectangle
	  int width,// largeur du rectangle en pixels
	  int height,// hauteur du rectangle en pixels
	  const string &color);// couleur de tracé du rectangle

// écriture d'un texte dans le flot de sortie
void text(ofstream &out,// flot d'écriture dans lequel ajouter le texte
	  int x, int y,// coordonnées du point auquel placer le texte
	               // le texte est centré par rapport à ce point
	  int size,// hauteur des caractères du texte en pixels
	  const string &txt,// le texte à ajouter
	  const string &color);// la couleur de tracé du texte

// --------------------------------------------------------------------
// prédéfinition de la fonction de conversion d'une valeur entière
// en chaîne de caractères
// --------------------------------------------------------------------
string intToString(int v);


// --------------------------------------------------------------------
// programme principal
// --------------------------------------------------------------------

int main(int argc, char *argv[]){

  // analyse des paramètres pour déterminer la taille du labyrinthe
  int largeur, hauteur;
  if(argc==1){
    // dimensions par défaut
    largeur = LARGEUR;
    hauteur = HAUTEUR;
  } else if(argc==3){
    // lecture des dimensions dans les paramètres
    largeur = atoi(argv[1]);
    hauteur = atoi(argv[2]);
  } else {
    cerr << "syntaxe : " << argv[0] << " [largeur hauteur]" << endl;
    return 0;
  }
  
  // création du labyrinthe
  labyrinthe laby;MatriceAdjacence m;
  initialiserLabyrinthe(laby, largeur, hauteur);
  creerMatrice(m, largeur*hauteur);
  Maillon *k=new Maillon;
  k->c=7;
  k->l=90;
  k->suiv=nullptr;
  Maillon *y=new Maillon;
  y->c=44;
  y->l=99;
  y->suiv=nullptr;
 
  //m.lignes[1]=k;
  
    // ajoutMaillon(m,k,1);
    // ajoutMaillon(m,y,1);
    //ajoutMaillon(m,k,1);
  
  

  // génération du labyrinthe
  genererLabyrinthe(laby);

  // dessin du labyrinthe
  dessinerLabyrinthe(laby,"laby.svg");
  remplirMatrice(m,laby);
  dessinerMatrice(m,laby, "t.svg");
  afficherMatrice(m);

  coordonnee deb, fin;
  chemin test;
  Couleur *coul=new Couleur[m.ordre];
  int *dist=new int[m.ordre];
  int *parent=new int[m.ordre];
  
  
  saisirCoordonnees(deb,fin, laby.largeur, laby.hauteur);
  test=calculerChemin(m, deb, 
                fin, laby.largeur,coul,parent,dist);
                cout<<"---------"<<test.lg<<"-----"<<m.ordre<<endl;
  dessinerSolution(laby,test, "solut.svg");
  //suppression du labyrinthe et la matrice
  effacerMatrice(m);
  effacerLabyrinthe(laby);

  return 1;
}

// --------------------------------------------------------------------
// définition des fonctions liées à la gestion d'un labyrinthe
// --------------------------------------------------------------------

void initialiserLabyrinthe(labyrinthe &laby, int largeur, int hauteur){
  // initialisation des dimensions
  laby.largeur = largeur;
  laby.hauteur = hauteur;
  // allocation des zones mémoire
  laby.cell = new int[largeur*hauteur];
  laby.mursV = new bool[(largeur+1)*hauteur];
  laby.mursH = new bool[largeur*(hauteur+1)];
  // initialisation des zones mémoire
  // un identifiant différent par cellule
  for(int i=0; i<largeur*hauteur; i++) laby.cell[i] = i;
  // tous les murs verticaux sont présents
  for(int i=0; i<(largeur+1)*hauteur; i++) laby.mursV[i] = true;
  // tous les murs horizontaux sont présents
  for(int i=0; i<largeur*(hauteur+1); i++) laby.mursH[i] = true;
}

void effacerLabyrinthe(labyrinthe &laby){
  delete [] laby.cell;
  delete [] laby.mursV;
  delete [] laby.mursH;
}

void genererLabyrinthe(labyrinthe &laby){
  // calcul du nombre de murs à supprimer
  int nbm = laby.largeur*laby.hauteur-1;
  int nb=0;

  while(nb<nbm){
    // génération aléatoire d'une case de la grille
    // et d'une direction de suppression
    int c=rand()%laby.largeur;// dans [0,M-1]
    int l=rand()%laby.hauteur;// dans [0,N-1]
    int dir=rand()%4; // 0=droite, 1=haut, 2=gauche, 3=bas
    int oid, nid;// valeur de l'id (oid) à changer en nouvel id (nid)
    bool trouve;

    trouve=false;// on va vérifier que le mur peut être supprimé
    
    switch(dir){
    case 0:// suppression d'un mur droit
      if(c==laby.largeur-1) break;// colonne invalide
      if(!laby.mursV[(c+1)+l*laby.largeur]) break; // le mur n'existe pas
      if(laby.cell[c+l*laby.largeur]==laby.cell[(c+1)+l*laby.largeur]) break; // déjà connecté
      oid = laby.cell[(c+1)+l*laby.largeur];
      nid = laby.cell[c+l*laby.largeur];
      laby.mursV[(c+1)+l*laby.largeur]=false;
      trouve=true;
      break;
    case 2:// suppression d'un mur gauche
      if(c==0) break;// colonne invalide
      if(!laby.mursV[c+l*laby.largeur]) break; // le mur n'existe pas
      if(laby.cell[c+l*laby.largeur]==laby.cell[(c-1)+l*laby.largeur]) break; // déjà connecté
      oid = laby.cell[(c-1)+l*laby.largeur];
      nid = laby.cell[c+l*laby.largeur];
      laby.mursV[c+l*laby.largeur]=false;
      trouve=true;
      break;
    case 1:// suppression d'un mur haut
      if(l==0) break;// ligne invalide
      if(!laby.mursH[c+l*laby.largeur]) break; // le mur n'existe pas
      if(laby.cell[c+l*laby.largeur]==laby.cell[c+(l-1)*laby.largeur]) break; // déjà connecté
      oid = laby.cell[c+(l-1)*laby.largeur];
      nid = laby.cell[c+l*laby.largeur];
      laby.mursH[c+l*laby.largeur]=false;
      trouve=true;
      break;
    case 3:// suppression d'un mur bas
      if(l==laby.hauteur-1) break;// ligne invalide
      if(!laby.mursH[c+(l+1)*laby.largeur]) break; // le mur n'existe pas
      if(laby.cell[c+l*laby.largeur]==laby.cell[c+(l+1)*laby.largeur]) break; // déjà connecté
      oid = laby.cell[c+(l+1)*laby.largeur];
      nid = laby.cell[c+l*laby.largeur];
      laby.mursH[c+(l+1)*laby.largeur]=false;
      trouve=true;
      break;   
    }//switch
    
    if(!trouve) continue;

    // un mur a été supprimé - maj des id des cellules voisines
    // version basique de la màj par parcours de toutes les
    // cellules du labyrinthe
    nb++;
    for(int i=0; i<laby.largeur; i++)
      for(int j=0; j<laby.hauteur; j++)
	if(laby.cell[i+j*laby.largeur]==oid) laby.cell[i+j*laby.largeur]=nid;
  }
}


void dessinerLabyrinthe(labyrinthe &laby, const string &nomFichier){
  ofstream out;

  if(!ouvrirFichierSVG(nomFichier, out,
		       laby.largeur*CELLSIZE+2*MARGE,
		       laby.hauteur*CELLSIZE+2*MARGE))
    return;

  // dessin du fond
  rect(out, 0, 0,
       laby.largeur*CELLSIZE+2*MARGE,
       laby.hauteur*CELLSIZE+2*MARGE, "white");

   // dessin des murs verticaux
  for(int c=0; c<laby.largeur+1; c++)
    for(int l=0; l<laby.hauteur; l++)
      if(laby.mursV[c+l*laby.largeur]){// dessiner un mur vertical
	ligne(out,
	      c*CELLSIZE+MARGE, l*CELLSIZE+MARGE,
	      c*CELLSIZE+MARGE, (l+1)*CELLSIZE+MARGE,
	      "black", 3);
      }
  
  // dessin des murs horizontaux
  for(int c=0; c<laby.largeur; c++)
    for(int l=0; l<laby.hauteur+1; l++)
      if(laby.mursH[c+l*laby.largeur]){// dessiner un mur horizontal
	ligne(out,
	      c*CELLSIZE+MARGE, l*CELLSIZE+MARGE,
	      (c+1)*CELLSIZE+MARGE, l*CELLSIZE+MARGE,
	      "black", 3);
      }

  // affichage des identifiants de cellules
  for(int c=0; c<laby.largeur; c++)
    for(int l=0; l<laby.hauteur; l++){
      // conversion du numéro de cellule en chaîne de caractères
      string txt = intToString(laby.cell[c+l*laby.largeur]);
      text(out,
	   c*CELLSIZE + CELLSIZE/2 + MARGE, // centre de la colonne
	   l*CELLSIZE + CELLSIZE/2 + MARGE,// centre de la ligne
	   TEXTSIZE,
	   txt, "red");
    }

  fermerFichierSVG(out);
}

// --------------------------------------------------------------------
// définition des fonctions liées à l'écriture dans les fichiers SVG
// --------------------------------------------------------------------

bool ouvrirFichierSVG(const string &nomFichier, ofstream &out,
		      int largeur, int hauteur){
  out.open(nomFichier);
  
  if(!out.is_open()){
    cout << "erreur d'ouverture du fichier de dessin " << nomFichier << endl;
    return false;
  }

  // sortie de l'entête
  out << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << endl;
  out << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" ";
  out <<"width=\"" << largeur << "\" height=\"" << hauteur << "\">" << endl;
  
  return true;
}


void fermerFichierSVG(ofstream &out){
  // fermeture de la balise svg
  out << "</svg>" << endl;

  out.close();
}

void text(ofstream &out, int x, int y, int size, const string &txt, const string &color){

  out << "<text x=\"" << x << "\" y=\"" << y << "\"" ;
  out << " font-family=\"Verdana\" font-size=\"" << size << "\"";
  out << " text-anchor=\"middle\" " ;
  out << " dominant-baseline=\"middle\" ";
  out << "fill=\"" << color << "\" >" << endl;
  out << txt << endl; 
  out << "</text>" << endl;
}

void ligne(ofstream &out, int x1, int y1, int x2, int y2, const string& color, int width){
  out <<  "<line x1=\"" << x1<< "\" y1=\"" << y1 << "\"";
  out << " x2=\"" << x2<< "\" y2=\"" << y2;
  out << "\" stroke=\"" << color << "\"";
  out << " stroke-width=\"" << width << "\"" << " />" << endl;
}

void rect(ofstream &out, int x, int y, int width, int height,  const string &color){
  out << "<rect width=\"" << width << "\" height=\"" << height << "\"";
  out << " x=\"" << x << "\" y=\"" << y << "\" fill=\"" << color << "\"";
  out << " />" << endl;
}

// --------------------------------------------------------------------
// Fonction de conversion d'une valeur entière en chaîne de caractères
// --------------------------------------------------------------------

string intToString(int v){
  stringstream s;
  s << v;
  return s.str();
}
  
// --------------------------------------------------------------------
// définition des fonctions liées aux matrices d'adjacence
// --------------------------------------------------------------------

void creerMatrice(MatriceAdjacence &m, int taille){

  m.ordre=taille;
  m.lignes=new Maillon*[m.ordre];
  for(int i=0; i<m.ordre; i++){
    m.lignes[i]=nullptr;
  }

}

void effacerMatrice(MatriceAdjacence &mat){

  for(int i=0; i<mat.ordre; i++){
    Maillon *cur;
    while (mat.lignes[i]!=nullptr){
      cur=mat.lignes[i];
      mat.lignes[i]=mat.lignes[i]->suiv;
      delete cur;
    }
    
  }
  mat.ordre=0;
}

void afficherMatrice(MatriceAdjacence &mat){
  int j=0;
  for(int i=0; i<mat.ordre; i++){
    cout<<"noeud "<<i<<": ";
    Maillon *cur=mat.lignes[i];
    while(cur!=nullptr){
      cout<<"("<<cur->l<<" "<<cur->c<<")";
      cur=cur->suiv;
      j++;
      
    }cout<<endl;
    
  }

}
void ajoutMaillon(MatriceAdjacence &m,Maillon *ajout,int pos){
  if(m.lignes[pos]==nullptr){
    m.lignes[pos]=ajout;
  }
  else{
    
    Maillon *cur=m.lignes[pos];
    Maillon *prec=nullptr;
    while(cur!=nullptr){
      prec=cur;
      cur=cur->suiv;
    }
    prec->suiv=ajout;
  }

}
void remplirMatrice(MatriceAdjacence &mat,const labyrinthe &lab){
  for(int i=0; i<lab.hauteur; i++){
    
    for(int j=0; j<lab.largeur; j++){
      if(lab.mursV[(i*lab.largeur+j+1)]==false){
        Maillon *m=new Maillon;
        m->l=i;
        m->c=j+1;
        m->suiv=nullptr;
        ajoutMaillon(mat,m,(i*lab.largeur+j));
  
      }
      if(lab.mursV[(i*lab.largeur)+j]==false){
        Maillon *m=new Maillon;
        m->l=i;
        m->c=j-1;
        m->suiv=nullptr;
        ajoutMaillon(mat,m,(i*lab.largeur)+j);
        
      }
      if(lab.mursH[(i*lab.largeur)+j]==false){
        Maillon *m=new Maillon;
        m->l=i-1;
        m->c=j;
        m->suiv=nullptr;
        ajoutMaillon(mat,m,(i*lab.largeur)+j);
      }
      if(lab.mursH[(i*lab.largeur)+j+lab.largeur]==false){
        Maillon *m=new Maillon;
        m->l=i+1;
        m->c=j;
        m->suiv=nullptr;
        ajoutMaillon(mat,m,(i*lab.largeur)+j);
      }
    }
  }
}

void dessinMur(const labyrinthe &laby,ofstream &out){
  
  rect(out, 0, 0,
       laby.largeur*CELLSIZE+2*MARGE,
       laby.hauteur*CELLSIZE+2*MARGE, "white");
         for(int c=0; c<laby.largeur+1; c++){
    for(int l=0; l<laby.hauteur; l++){
      if(laby.mursV[c+l*laby.largeur]){// dessiner un mur vertical
        ligne(out,
              c*CELLSIZE+MARGE, l*CELLSIZE+MARGE,
              c*CELLSIZE+MARGE, (l+1)*CELLSIZE+MARGE,
              "black", 3);
      }  
    }
      
  }
  for(int c=0; c<laby.largeur; c++){
    for(int l=0; l<laby.hauteur+1; l++){
      if(laby.mursH[c+l*laby.largeur]){// dessiner un mur horizontal
	      ligne(out,
          c*CELLSIZE+MARGE, l*CELLSIZE+MARGE,
          (c+1)*CELLSIZE+MARGE, l*CELLSIZE+MARGE,
          "black", 3);
      }
    }
      
  }
}

void dessinerMatrice(const MatriceAdjacence &mat, const labyrinthe &laby, const string &nom){
  ofstream out;
  if(!ouvrirFichierSVG(nom, out,laby.largeur*CELLSIZE+2*MARGE,laby.hauteur*CELLSIZE+2*MARGE)){
    return;
  }
  rect(out, 0, 0,
       laby.largeur*CELLSIZE+2*MARGE,
       laby.hauteur*CELLSIZE+2*MARGE, "white");
  
  for(int c=0; c<laby.largeur+1; c++){
    for(int l=0; l<laby.hauteur; l++){
      if(laby.mursV[c+l*laby.largeur]){// dessiner un mur vertical
        ligne(out,
              c*CELLSIZE+MARGE, l*CELLSIZE+MARGE,
              c*CELLSIZE+MARGE, (l+1)*CELLSIZE+MARGE,
              "black", 3);
      }  
    }
      
  }
  for(int c=0; c<laby.largeur; c++){
    for(int l=0; l<laby.hauteur+1; l++){
      if(laby.mursH[c+l*laby.largeur]){// dessiner un mur horizontal
	      ligne(out,
          c*CELLSIZE+MARGE, l*CELLSIZE+MARGE,
          (c+1)*CELLSIZE+MARGE, l*CELLSIZE+MARGE,
          "black", 3);
      }
    }
      
  }
    
    
  for(int i=0; i<laby.hauteur; i++){
    for(int j=0; j<laby.largeur; j++){
      Maillon *cur=mat.lignes[i*laby.largeur+j];
      while (cur!=nullptr){
        ligne(out,
          ((i*laby.largeur+j)%laby.largeur+0.5)*CELLSIZE+MARGE, (i+0.5)*CELLSIZE+MARGE,
          (cur->c+0.5)*CELLSIZE+MARGE, (cur->l+0.5)*CELLSIZE+MARGE,
          "green", 3);
        cur=cur->suiv;
      }
      
    }
  }
  fermerFichierSVG(out);
}
void saisirCoordonnees(coordonnee &deb, coordonnee &fin, int largeur, int hauteur){

  cout<<"Saisir les coordonnées des sommets:"<<endl;
  cout<<"Abscisse debut: ";
  cin>>deb.x;
  while(deb.x>largeur-1){
    cout<<"Ressaisir à nouveau"<<endl;
    cin>>deb.x;
  }
  cout<<"Ordonnée debut: ";
  cin>>deb.y;
  while(deb.y>hauteur-1){
    cout<<"Ressaisir à nouveau"<<endl;
    cin>>deb.y;
  }
  cout<<"Abscisse fin: ";
  cin>>fin.x;
  while(fin.x>largeur-1){
    cout<<"Ressaisir à nouveau"<<endl;
    cin>>fin.x;
  }
  cout<<"Ordonnée fin: ";
  cin>>fin.y;
  while(fin.y>hauteur-1){
    cout<<"Ressaisir à nouveau"<<endl;
    cin>>fin.y;
  }

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

chemin calculerChemin(const MatriceAdjacence &mat, coordonnee deb, 
                      coordonnee fin, int largeur,Couleur *coul,int *parent,int *dist){

  chemin chem;                      
  for(int i=0; i<mat.ordre; i++){
    coul[i]=BLANC;
    dist[i]=INFINI;
    parent[i]=INDEFINI;
  }
  int sommetDep=deb.y*largeur+deb.x;
  int sommetArr=fin.y*largeur+fin.x;
  coul[sommetDep]=GRIS;
  dist[sommetDep]=0;
  parent[sommetDep]=INDEFINI;
  Fifo file;
  initialiser(file);
  ajouter(file,sommetDep);
  while(!estVide(file)){
    int cur=retirer(file);
    for(int i=0; i<mat.ordre; i++){
      Maillon *maillon=mat.lignes[i];
      while(maillon!=nullptr){
        if(maillon->l*largeur+maillon->c==cur){
          if(coul[i]==BLANC){
            coul[i]=GRIS;
            dist[i]=dist[cur]+1;
            parent[i]=cur;
            ajouter(file,i);
          }
        }
        maillon=maillon->suiv;
      }
      coul[cur]=NOIR;
    }
    
  }
  chem.lg=dist[fin.y*largeur+fin.x];
  chem.etape=new coordonnee[chem.lg+1];
  int hauteur=mat.ordre/largeur;
  int i=chem.lg;
  int cmpt=sommetArr;
  while(cmpt!=INDEFINI){
      chem.etape[i].x=cmpt%largeur;
      chem.etape[i].y=(cmpt-chem.etape[i].x)/largeur; 
      i--;
      cmpt=parent[cmpt];
  }
  return chem;

}

void dessinerSolution(const labyrinthe &laby,chemin ch, const string &nomFichier){

  ofstream out;
  if(!ouvrirFichierSVG(nomFichier, out,laby.largeur*CELLSIZE+2*MARGE,laby.hauteur*CELLSIZE+2*MARGE)){
    return;
  }
  dessinMur(laby,out);
  for(int i=0; i<ch.lg; i++){
    ligne(out,
          ((ch.etape[i].y*laby.largeur+ch.etape[i].x)%laby.largeur+0.5)*CELLSIZE+MARGE, (ch.etape[i+1].y+0.5)*CELLSIZE+MARGE,
          (ch.etape[i+1].x+0.5)*CELLSIZE+MARGE, (ch.etape[i].y+0.5)*CELLSIZE+MARGE,
          "red", 3);
  }
  fermerFichierSVG(out);

}
