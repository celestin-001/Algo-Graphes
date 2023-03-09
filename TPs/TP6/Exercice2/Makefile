tp6: tp6.o matrice.o parcours.o graphique.o
	g++ tp6.o matrice.o parcours.o graphique.o -o tp6 -lSDL2

tp6.o:	tp6.cpp
	g++ -c tp6.cpp

matrice.o:	matrice.cpp
	g++ -c matrice.cpp

parcours.o:	parcours.cpp
	g++ -c parcours.cpp

graphique.o:	graphique.cpp
	g++ -c graphique.cpp $(sdl2-config--cflags)


