/*
Nom:Goumou
Prenoms:Celestin M'bemba
L2 Info ULCO
*/


#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include "types.hpp"

#define CELLSIZE 50 // taille d'un côté d'une case du labyrinthe
#define MARGE 10    // marge du dessin
#define TEXTSIZE 10 // taille d'affichage du texte

// --------------------------------------------------------------------
// prédéfinition des fonctions liées à la gestion d'un labyrinthe
// --------------------------------------------------------------------
void initialiserLabyrinthe(labyrinthe &laby, int largeur, int hauteur);

void effacerLabyrinthe(labyrinthe &laby);

void genererLabyrinthe( labyrinthe &laby);
int nombreDemur(labyrinthe &laby);

void extremites(labyrinthe &laby,int pos,int a);

void dessinerLabyrinthe(labyrinthe &laby, const string &nomFichier);


// --------------------------------------------------------------------
// prédéfinition des fonctions liées à l'écriture dans les fichiers SVG
// --------------------------------------------------------------------

// création du fichier et ouverture du flot d'écriture associé
// retourne false si le fichier n'a pas pu être ouvert.
bool ouvrirFichierSVG(const string &nomFichier, // nom du fichier à créer
                      ofstream &out, // flot d'écriture ouvert par la fonction
                      int largeur,   // largeur de l'image en pixels
                      int hauteur);  // hauteur de l'image en pixels

// fermeture du flot d'écriture et du fichier associé
void fermerFichierSVG(
    ofstream &out); // flot d'écriture à fermer par la fonction

// écriture d'une ligne dans le flot de sortie
void ligne(ofstream &out,       // flot d'écriture dans lequel ajouter la ligne
           int x1, int y1,      // coordonnées du point de départ de la ligne
           int x2, int y2,      // coordonnées du point d'arrivée de la ligne
           const string &color, // couleur de tracé de la ligne
           int width);          // épaisseur de tracé de la ligne

// écriture d'un rectangle dans le flot de sortie
void rect(ofstream &out, // flot d'écriture dans lequel ajouter le rectangle
          int x, int y,  // coordonnées du point supérieur gauche du rectangle
          int width,     // largeur du rectangle en pixels
          int height,    // hauteur du rectangle en pixels
          const string &color); // couleur de tracé du rectangle

// écriture d'un texte dans le flot de sortie
void text(ofstream &out,        // flot d'écriture dans lequel ajouter le texte
          int x, int y,         // coordonnées du point auquel placer le texte
                                // le texte est centré par rapport à ce point
          int size,             // hauteur des caractères du texte en pixels
          const string &txt,    // le texte à ajouter
          const string &color); // la couleur de tracé du texte

// --------------------------------------------------------------------
// prédéfinition de la fonction de conversion d'une valeur entière
// en chaîne de caractères
// --------------------------------------------------------------------
string intToString(int v);

// --------------------------------------------------------------------
// programme principal
// --------------------------------------------------------------------

int main(int argc, char *argv[]) {
  labyrinthe laby;
  string nomFichier=argv[1];
  laby.hauteur=stoi(argv[2]);
  laby.largeur=stoi(argv[3]);
 
  if(argc<3){
    cout<<"Il manque "<<3-argc<<" argument(s) "<<endl;
  }
  else{
    initialiserLabyrinthe(laby, laby.largeur, laby.hauteur);
    //srand(time(0));
    genererLabyrinthe(laby);
    dessinerLabyrinthe(laby,nomFichier);
      
  effacerLabyrinthe(laby);
    //effacerLabyrinthe(laby);
  }

  return 1;
}

// --------------------------------------------------------------------
// définition des fonctions liées à la gestion d'un labyrinthe
// --------------------------------------------------------------------

// à compléter ...

// --------------------------------------------------------------------
// définition des fonctions liées à l'écriture dans les fichiers SVG
// --------------------------------------------------------------------

bool ouvrirFichierSVG(const string &nomFichier, ofstream &out, int largeur,
                      int hauteur) {
  out.open(nomFichier);

  if (!out.is_open()) {
    cout << "erreur d'ouverture du fichier de dessin " << nomFichier << endl;
    return false;
  }

  // sortie de l'entête
  out << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << endl;
  out << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" ";
  out << "width=\"" << largeur << "\" height=\"" << hauteur << "\">" << endl;

  return true;
}

void fermerFichierSVG(ofstream &out) {
  // fermeture de la balise svg
  out << "</svg>" << endl;

  out.close();
}

void text(ofstream &out, int x, int y, int size, const string &txt,
          const string &color) {

  out << "<text x=\"" << x << "\" y=\"" << y << "\"";
  out << " font-family=\"Verdana\" font-size=\"" << size << "\"";
  out << " text-anchor=\"middle\" ";
  out << " dominant-baseline=\"middle\" ";
  out << "fill=\"" << color << "\" >" << endl;
  out << txt << endl;
  out << "</text>" << endl;
}

void ligne(ofstream &out, int x1, int y1, int x2, int y2, const string &color,
           int width) {
  out << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\"";
  out << " x2=\"" << x2 << "\" y2=\"" << y2;
  out << "\" stroke=\"" << color << "\"";
  out << " stroke-width=\"" << width << "\""
      << " />" << endl;
}

void rect(ofstream &out, int x, int y, int width, int height,
          const string &color) {
  out << "<rect width=\"" << width << "\" height=\"" << height << "\"";
  out << " x=\"" << x << "\" y=\"" << y << "\" fill=\"" << color << "\"";
  out << " />" << endl;
}

// --------------------------------------------------------------------
// Fonction de conversion d'une valeur entière en chaîne de caractères
// --------------------------------------------------------------------

string intToString(int v) {
  stringstream s;
  s << v;
  return s.str();
}

void initialiserLabyrinthe(labyrinthe &laby, int largeur, int hauteur) {
  int sizeCell, sizemursH, sizemursV;
  sizeCell = hauteur * largeur;
  sizemursH = (hauteur + 1) * largeur;
  sizemursV = (largeur + 1) * hauteur;
  laby.cell = new int[sizeCell];
  laby.mursH = new bool[sizemursH];
  laby.mursV = new bool[sizemursV];
  
  for (int i = 0; i < sizeCell; i++) {
    laby.cell[i] = i;
  }
  for (int i = 0; i < sizemursH; i++) {
    laby.mursH[i] = true;
  }
  for (int i = 0; i < sizemursV; i++) {
    laby.mursV[i] = true;
  }
}

void effacerLabyrinthe(labyrinthe &laby) {

  delete[] laby.cell;
  delete[] laby.mursH;
  delete[] laby.mursV;
}

void dessinerLabyrinthe(labyrinthe &laby, const string &nomFichier){
  ofstream out; 
  int sizemursH = (laby.hauteur + 1) * laby.largeur;
  int nblH=laby.largeur;
  int nblV=laby.hauteur;
  
  ouvrirFichierSVG(nomFichier,out,laby.largeur*CELLSIZE, laby.hauteur*CELLSIZE);
  rect(out,0,0,laby.largeur*CELLSIZE,laby.hauteur*CELLSIZE,"white");
   
  for (int i = 0; i <= nblV; i++) {
    for (int j = 0; j < nblH; j++) {
      if (laby.mursH[(i * nblH) + j] == true) {
        ligne(out, j*CELLSIZE, i*CELLSIZE, (j+1)*CELLSIZE, i*CELLSIZE, "red", 2);
        
      }
    }
  }
  
  for (int i = 0; i < nblV; i++) {
    for (int j = 0; j < nblH+1; j++) {
      if (laby.mursV[(i * (nblH+1)) + j] == true) {
        ligne(out, j*CELLSIZE,i*CELLSIZE, j*CELLSIZE, (i+1)*CELLSIZE,  "red", 2);
        
      }
    }
  }
  for (int i = 0; i < nblV; i++) {
    for (int j = 0; j < nblH; j++) {
      text(out, CELLSIZE*(j+0.5), CELLSIZE*(i+0.5), TEXTSIZE, intToString(laby.cell[(i*laby.largeur)+j]),
          "blue");
    }
  }
  
  
  fermerFichierSVG(out);

}
int nombreDemur(labyrinthe &laby){
  int nbc=laby.largeur/CELLSIZE;
  int nbmur=0;
  int  sizemursV = (laby.largeur + 1) * laby.hauteur;
  int  sizemursH = (laby.hauteur + 1) * laby.largeur;
  for(int i=0;i<sizemursH;i++){
    
      if(laby.mursH[i]==true){
        nbmur+=1;
      }
    
  }
  for(int i=0;i<sizemursV;i++){
    
      if(laby.mursV[i]==true){
        nbmur+=1;
      }
    
  }
  return nbmur;
}

void genererLabyrinthe(labyrinthe &laby){
  
  int nbl = laby.hauteur;
  int nbc = laby.largeur;
  int Tab[4]={1,-1,nbc,-nbc};
  int nbmur=nombreDemur(laby);
  int cmpt=0;

  // Tableau pour stocker les identifiants de cellules
  int *cell_ids = new int[laby.hauteur * laby.largeur];
  for (int i = 0; i < laby.hauteur * laby.largeur; i++) {
    cell_ids[i] = i;
  }

  while(cmpt != (laby.largeur * laby.hauteur) - 1){
    int nbAlea = rand() % (laby.largeur * laby.hauteur);
    int cleMur = rand() % 4;
    while ((nbAlea + Tab[cleMur]) % (nbc) == 0 || (nbAlea + Tab[cleMur]) % (nbc) == nbc-1 ||
           nbAlea + Tab[cleMur] <= 0 || nbAlea + Tab[cleMur] >= nbl * nbc) {
      cleMur = rand() % 4;
    }
    int pos = (nbAlea + Tab[cleMur]);

    int id1 = cell_ids[laby.cell[nbAlea]];
    int id2 = cell_ids[laby.cell[pos]];

    if (id1 != id2) {
      for (int i = 0; i < laby.hauteur * laby.largeur; i++) {
        if (cell_ids[i] == id2) {
          cell_ids[i] = id1;
        }
      }
      if (Tab[cleMur] == 1 || Tab[cleMur] == -1) {
        if (Tab[cleMur] == 1 && laby.mursV[(nbAlea/nbc) + 1 + nbAlea] == true) {
          laby.mursV[(nbAlea/nbc) + 1 + nbAlea] = false;
          cmpt++;
        } else if (Tab[cleMur] == -1 && laby.mursV[(nbAlea/nbc) + nbAlea] == true) {
          laby.mursV[(nbAlea/nbc) + nbAlea] = false;
          cmpt++;
        }   
      } else if (Tab[cleMur] == nbc || Tab[cleMur] == -nbc) {
        if (Tab[cleMur] == nbc && laby.mursH[pos] == true) {
          laby.mursH[pos] = false;
          cmpt++;
        } else if (Tab[cleMur] == -nbc && laby.mursH[nbAlea] == true) {
          laby.mursH[nbAlea] = false;
          cmpt++;
        }  
      }
    }
  }
  cout << cmpt << endl;
  cout << nbmur << endl;
  for (int i = 0; i < laby.hauteur * laby.largeur; i++) {
          laby.cell[i]=cell_ids[i];
      }
  // Libération de la mémoire allouée pour le tableau 
  delete[] cell_ids;
}




