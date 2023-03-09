
#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
using namespace std;

#include "types.hpp"

#define MIN 0
#define MAX 10000

#define TAILLE_RECT  20  // côté d'un rectanngle en pixels

// définition de 3 variables représentant les couleurs rouge, vert et bleu
SDL_Color rouge={255, 0, 0, 255};
SDL_Color bleu={0,0,255,255};
SDL_Color vert={0, 255, 0, 255};


static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;
static void computeWindowSize(MatriceAdjacence &m, int &w, int &h);
static void drawRect(coordonnees centre, int cote, SDL_Color col);
static void drawLine(coordonnees deb, coordonnees fin, SDL_Color c);
static void drawPath(MatriceAdjacence mat, int sf, int *parents);
		     


// ----- fonctions à compléter 

void drawGraph(MatriceAdjacence &m){
  // 1. dessin des arcs

  for(int i=0; i<m.ordre; i++){
    for(int j=0; j<m.ordre; j++){
      
      
      Maillon *cur=m.lignes[j];
      while(cur && cur->col!=j){
        if(cur->col==i){
          drawLine(m.positions[i], m.positions[j], bleu);
        }
        cur=cur->suiv;
    
      }
   
    }
  }
  
  // 2. dessin des sommets sous forme de rectangles
  // de coté TAILLE_RECT

  for(int i=0; i<m.ordre; i++){
    drawRect(m.positions[i], 6, rouge);
  }

  // forcer l'affichage des primitives graphiques
  //SDL_RenderPresent(renderer);
}


// tracé du chemin entre le sommet d'indice sf et le sommet de départ
// la fonction doit opérer de manière récursive, comme la fonction
// d'affichage des chemins.
void drawPath(MatriceAdjacence mat, int sf, int *parents){
 
  //cout << "chemin vers " << sf << endl;
  if(parents[sf]==INDEFINI){
    drawLine(mat.positions[sf], mat.positions[sf], vert);
  }
  else{
    drawPath(mat, parents[sf],parents);
    drawLine(mat.positions[sf], mat.positions[parents[sf]], rouge);
  }
  
}

// tracé de tous les chemins les plus courts calculés par
// l'algorihme de Dijkstra
void drawPaths(MatriceAdjacence mat, int *parents){
  // tracer chacun des chemins les plus courts trouvés 
  // par l'algorithme de dijkstra
  for(int i=0; i<mat.ordre;i++){
    drawPath(mat,i,parents);
  }

  // forcer l''affichage
  SDL_RenderPresent(renderer);
	
}

// -- fin des fonctions à compléter





int createWindow(MatriceAdjacence &m){
  
  if(SDL_Init(SDL_INIT_VIDEO)!=0){
    cerr << "Erreur SDL_Init : " << SDL_GetError();
    SDL_Quit();
    return EXIT_FAILURE;
  }

  int width, height;
  computeWindowSize(m, width, height);

  cout << width << "-" << height << endl;
  window = SDL_CreateWindow("Plus court chemin",
			    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			    width, height, SDL_WINDOW_SHOWN);
  if(window==nullptr){
    cerr << "Erreur SDL_CreateWindow : " << SDL_GetError();
    SDL_Quit();
    return EXIT_FAILURE;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(renderer==nullptr){
    cerr << "Erreur SDL_CreateRenderer : " << SDL_GetError();
    SDL_Quit();
    return EXIT_FAILURE;       
  }

   // effacer la fenêtre
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  return EXIT_SUCCESS;
}


void destroyWindow(){
  SDL_DestroyWindow(window);
  SDL_Quit();
}



void computeWindowSize(MatriceAdjacence &m, int &w, int &h){
  // calcul des valeur min et max des positions
  int cmin=MAX, cmax=MIN, lmin=MAX, lmax=MIN;
  for(int l=0; l<m.ordre; l++){
    int vx = m.positions[l].x;
    int vy = m.positions[l].y;
    if(vx<cmin) cmin=vx;
    if(vx>cmax) cmax=vx;
    if(vy<lmin) lmin=vy;
    if(vy>lmax) lmax=vy;
  }
  // calcul de la taille de la fenêtre
  // en assurant un centrage du graphe
  w = cmax+cmin;
  h = lmax+lmin;
}
  


void drawRect(coordonnees centre, int cote, SDL_Color col){
  SDL_Rect rect={centre.x-cote/2, centre.y-cote/2, cote, cote};
  SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
  SDL_RenderFillRect(renderer, &rect);
}

void drawLine(coordonnees deb, coordonnees fin, SDL_Color col){
  SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
  SDL_RenderDrawLine(renderer, deb.x, deb.y, fin.x, fin.y);
}

void waitForEnd(){
  SDL_Event event;
  while(SDL_WaitEvent(&event)){
    if(event.type==SDL_KEYDOWN) break;
    if(event.type==SDL_QUIT) break;
  }
}
