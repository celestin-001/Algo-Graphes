


struct labyrinthe {
  int largeur, hauteur;// nombre de colonnes et de lignes du labyrinthe
  int *cell; // cellules du labyrinthes
  bool *mursV;// état des murs verticaux des cellules
  bool *mursH;// état des murs horizontaux des cellules
};
