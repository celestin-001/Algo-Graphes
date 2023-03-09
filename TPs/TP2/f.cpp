#include <iostream>
using namespace std;
const int TAILLE = 9;

void initGrille(int s[TAILLE][TAILLE]) {
  for (int i = 0; i < TAILLE; i++) {

    for (int j = 0; j < TAILLE; j++) {
      s[i][j] = -1;
    }
  }
}
void remplirGrille(int s[TAILLE][TAILLE]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 3; j <= 5; j++) {
      s[i][j] = 1;
    }
  }
  for (int i = 3; i <= 5; i++) {
    for (int j = 0; j < 9; j++) {
      s[i][j] = 1;
    }
  }
  s[4][4] = 0;
}
void afficherGrille(int s[TAILLE][TAILLE]) {
  cout << "  ";
  for (int i = 0; i < 9; i++) {
    cout << i + 1 << " ";
  }
  cout << endl;
  for (int i = 0; i < 9; i++) {
    cout << i + 1 << " ";
    for (int j = 0; j < 9; j++) {
      
      if (s[i][j] == -1) {
        cout << "."
             << " ";

      } 
      if (s[i][j] == 0) {
        cout << "  ";
      }
      if (s[i][j] == 1) {
        cout << s[i][j] << " ";
      }
    }

    cout << endl;
  }
}
int NbPions( int s[TAILLE][TAILLE]) {
 int  np=0;
    for (int i = 0; i < 9; i++) {
    for (int j = 0; j <9; j++) {
      if(s[i][j]== 1) {
        np=np+1;
          
      }
  }
  

}
  return np;
}
 bool estPriseHD( int s[TAILLE][TAILLE],int x,int y) {
   if(s[x][y+2]==0){
     return true;
   }
   else{
     return false;
   }
}
bool  estPriseHG( int s[TAILLE][TAILLE],int x,int y){
   if(s[x][y-2]==0) {
     return true;
   }
   else{
     return false;
   }
 }
bool estPriseVH( int s[TAILLE][TAILLE],int x,int y) {
   if(s[x-2][y]==0){
     return true;
   }
   else{
     return false;
   }
 }
bool estPriseVB( int s[TAILLE][TAILLE],int x,int y) {
   if(s[x+2][y]==0){
     return true;
   }
   else{
     return false;
   }
 }
bool estPrise ( int s[TAILLE][TAILLE],int x,int y, string Dep, string S) {
  if(Dep=="H" && S=="D") {
    if( estPriseHD( s, x,y)==true) {
      return true;
    }
  }
   if(Dep=="H" && S=="G"){
  if(estPriseHG(s,x, y)==true){
    return true;
  }
      }
  if(Dep=="V" && S=="H")  {
if( estPriseVH( s, x,y)==true) {
    return true;
  }
   }
if(Dep=="V" && S=="B") {
if( estPriseVB(  s, x,y)==true) {
    return true;
  }
  else{
    return false;
  }
  }
return false;

}
/*void priseHD( int s[TAILLE][TAILLE],int x,int y) {

    
if(estPriseHD (s,x,y)){

 s[x][y]=0;
  s[x][y+1]=0;
  s[x][y+2]=1;
  
}
  
}*/
 
int nbCoups( int s[TAILLE][TAILLE],int x,int y) {
 int nbc=0;
  if( estPriseHD( s, x,y)) {
  nbc=nbc+1;
  
  }
   if( estPriseHG( s, x,y)) {
   nbc=nbc+1;
   
  }
    if( estPriseVH( s, x,y)) {
    nbc=nbc+1;
    
  }
   if( estPriseVB( s, x,y)) {
    nbc=nbc+1;
    
  }
  return nbc;
  }

int nbCoupsTotal(int s[TAILLE][TAILLE]) {
 int nct=0;
  for(int i=0;i<9;i++){
  for(int j=0;j<9;j++){
  
    
      nct+=nbCoups(s,i,j);
    
  
    
    
  }
    
    
  }
  return nct;
}
int main() {
  int t[TAILLE][TAILLE];
  initGrille(t);
  remplirGrille(t);
  afficherGrille(t);
  cout << endl;
  int n=nbCoupsTotal(t);
  cout<<n<<endl;
  int s=0;
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
        
       if(t[i][j]==0){
        s++;
       }
        
        
        
    }
    
  }cout<<s<<"ffff"<<endl;
  
  return 0;
}