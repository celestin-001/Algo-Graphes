/*
Nom:Goumou
Prenoms:Celestin M'bemba
L2 Info ULCO
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

const int CELLSIZE=50;
const int MARGE=250;
// --------------------------------------------------------------------
// predefinition des fonctions liées à  l'écriture dans les fichiers SVG
// --------------------------------------------------------------------

// création du fichier et ouverture du flot d'écriture associé
// retourne false si le fichier n'a pas pu être ouvert.
bool ouvrirFichierSVG(const string &nomFichier,ofstream &out,int largeur,int hauteur);
/*
const string &nomFichier:nom du fichier à  créer;
ofstream &out:flot d'ecriture ouvert par la fonction;
int largeur:largeur de l'image en pixels;
int hauteur:hauteur de l'image en pixels;
*/

// fermeture du flot d'Ã©criture et du fichier associÃ©
void fermerFichierSVG(ofstream &out);
// flot d'Ã©criture Ã  fermer par la fonction;

// Ecriture d'une ligne dans le flot de sortie
void ligne(ofstream &out,int x1, int y1,int x2, int y2,const string& color,int width);
/*
&out flot d'ecriture dans lequel ajouter la ligne
int x1,int y1:coordonnées du point de départ de la ligne
int x2,int y2:coordonnées du point d'arrivée de la ligne
const string& color:couleur de tracé de la ligne
int width: epaisseur de trace de la ligne
*/

// Ecriture d'un rectangle dans le flot de sortie
void rect(ofstream &out,int x, int y,int width,int height,const string &color);
/*
ofstream &out:flot d'Ã©criture dans lequel ajouter le rectangle;
int x,y:flot d'ecriture dans lequel ajouter le rectangle;
int width:largeur du rectangle en pixels;
int height:hauteur du rectangle en pixels;
const string &color: couleur de trace du rectangle;
*/

// Ecriture d'un texte dans le flot de sortie
void text(ofstream &out,int x, int y,int size,const string &txt,const string &color);

void dessiner(ofstream &out, int largeur, int hauteur);
/*
Cette fonction doit permettre de dessiner une croix rouge dans une image de taille largeur ×
hauteur, qui sera sauvée dans un fichier dont le nom sera image01.svg
*/
void dessinerGrille(ofstream &out, int nbc, int nbl);
// --------------------------------------------------------------------
// programme principal
// --------------------------------------------------------------------

int main(int argc, char *argv[]){
  int nbl=5,nbc=1;
  ofstream out;
  char *nomFichier=argv[1];
  int largeur=stoi(argv[2]);
  int hauteur=stoi(argv[3]);
  if(argc<4){
    cout<<"Erreur il manque quelque(s) arguments"<<endl;
  }
  // flot d'Ã©criture pour le dessin
  ouvrirFichierSVG(nomFichier,out,largeur,hauteur);
  //dessiner(out,largeur,hauteur);
  rect(out, 0,0, largeur, hauteur,  "blue");
  //dessinerGrille(out, nbc,nbl);
  fermerFichierSVG(out);

  return 1;
}
  

// --------------------------------------------------------------------
// dÃ©finition des fonctions liÃ©es Ã  l'Ã©criture dans les fichiers SVG
// --------------------------------------------------------------------

bool ouvrirFichierSVG(const string &nomFichier, ofstream &out,
		      int largeur, int hauteur){
  out.open(nomFichier);
  
  if(!out.is_open()){
    cout << "erreur d'ouverture du fichier de dessin " << nomFichier << endl;
    return false;
  }

  // sortie de l'entÃªte
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
void dessiner(ofstream &out, int largeur, int hauteur){
  rect(out, 0,0, largeur, hauteur,  "white");
  ligne(out, 0, 0, largeur, hauteur, "red", 1); 
  ligne(out, 0, hauteur, largeur, 0, "red", 1); 

}
/*void dessinerGrille(ofstream &out, int nbc, int nbl,int largeur,int hauteur){
  for(int i=1;i<nbl;i++){
    ligne(out,(i*largeur)/nbl,0, (i*largeur)/nbl, hauteur, "red", 1);
  }
    for(int j=1;j<nbc;j++){
      ligne(out, 0, (j*largeur)/nbc, largeur, (j*largeur)/nbc, "red", 1);
  }
}*/
/*void dessinerGrille(ofstream &out, int nbc, int nbl){
  int largeur=nbc*(CELLSIZE);
  int hauteur=nbl*(CELLSIZE);
  rect(out,MARGE,MARGE,largeur-(2*MARGE),hauteur-(2*MARGE),"white");
  for(int i=1;i<nbl;i++){
    ligne(out,(i*CELLSIZE),0, (i*CELLSIZE), hauteur, "red", 1);
  }
    for(int j=1;j<nbc;j++){
      ligne(out, 0, (j*CELLSIZE), largeur, (j*CELLSIZE), "red", 1);
  }
}*/
/**/
void dessinerGrille(ofstream &out, int nbc, int nbl){
  int largeur=nbc*(CELLSIZE)+(2*MARGE);
  int hauteur=nbl*(CELLSIZE)+(2*MARGE);
  rect(out,0,0,largeur,hauteur,"white");
  int l=largeur;
  int h=hauteur+(2*MARGE);
  //rect(out,0,0,l,h,"blue");
  
  for(int i=0;i<=nbc;i++){
    ligne(out,MARGE+(i*CELLSIZE),MARGE, MARGE+(i*CELLSIZE), hauteur-MARGE, "red", 1);
  }
  for(int j=0;j<=nbl;j++){
      ligne(out, MARGE, MARGE+(j*CELLSIZE), largeur-MARGE, MARGE+(j*CELLSIZE), "red", 1);
  }
}
