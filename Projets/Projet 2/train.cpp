#include <iostream>
using namespace std;


int soustraction(int a,int b){
  
    return (a-b);
}

int age(int anA,int anN){
    return soustraction(anA,anN);
}


int main(){

    int x,y;
    x=10; y=7;
    int tab[3][2]={{1,2},{4,5},{7,8}};
    int p[2];
    int tmp=1;
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            tmp=tmp*tab[j][i];
            p[i]=tmp;
        }
        
    }
    int nm=p[0];
    int i=1;
    while(i<2){
        if(nm!=p[i]){
            return false;
        }
        else{
            i++;
        }
        
    }
    return true;
    //cout<<b;
    return 0;
}