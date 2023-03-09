/*
Nom:Goumou
Prenoms:Celestin M'bemba
L2 Info ULCO
*/


#include <iostream>
#include <fstream>
using namespace std;


bool convertir(char *fichierIn, char *fichierOut);

int main(int argc,char *argv[]){

    if(argc!=3){
        cout<< "Erreur D'ouverture"<<endl;
        return -1;
    }
    char *fichierIn=argv[1];
    char *fichierOut=argv[2];
    convertir(fichierIn,fichierOut);

    return 1;
}
bool convertir(char *fichierIn, char *fichierOut){
  ifstream in;
  ofstream out;
  in.open(fichierIn, std::ifstream::in);
  out.open(fichierOut,std::ofstream::out);
  if(!in.is_open()){
    printf("Erreur d'ouverture de %s\n", fichierIn);
    return false;
  }
  int taille;
  in>>taille;
  out<<taille<<endl;
  
   int val;
  for(int i=0;i<taille;i++){
   
    for(int j=0;j<taille;j++){
      in>>val;
      if(val!=0){
        out<<j<<" ";
        out<<val<<" ";
      }
    }
    out<<-1;
    out<<endl;
  }
  
  in.close();
  out.close();
  return true;


}