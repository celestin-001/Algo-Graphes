# Projet de Dessin SVG

Ce projet consiste à créer des fichiers SVG à l'aide de C++ pour dessiner des formes simples, notamment des lignes, des rectangles et des grilles. Le programme utilise des fonctions pour générer du code SVG, ce qui permet de créer des images vectorielles.

## Auteur
- **Nom** : Celestin M'bemba Goumou
- **Niveau d'études** : L2 Informatique à l'ULCO

## Fonctionnalités

Le projet comprend les fonctionnalités suivantes :

1. **Ouverture et fermeture de fichiers SVG**
    - La fonction `ouvrirFichierSVG` permet d'ouvrir un fichier SVG pour l'écriture.
    - La fonction `fermerFichierSVG` permet de fermer le fichier SVG après avoir terminé de dessiner.

2. **Dessin de lignes**
    - La fonction `ligne` permet de dessiner des lignes dans le fichier SVG en spécifiant les coordonnées de début et de fin, la couleur et l'épaisseur.

3. **Dessin de rectangles**
    - La fonction `rect` permet de dessiner des rectangles dans le fichier SVG en spécifiant les coordonnées du coin supérieur gauche, la largeur, la hauteur et la couleur.

4. **Dessin de texte**
    - La fonction `text` permet d'ajouter du texte dans le fichier SVG en spécifiant les coordonnées, la taille, le texte et la couleur.

5. **Dessin d'une croix rouge**
    - La fonction `dessiner` génère une image SVG avec une croix rouge au centre de l'image. 

6. **Dessin d'une grille**
    - La fonction `dessinerGrille` génère une grille dans l'image SVG en fonction du nombre de colonnes et de lignes spécifiées.

## Utilisation

Le programme principal (`main`) permet de créer des fichiers SVG en utilisant les fonctions de dessin définies. Voici comment utiliser le programme :

1. Compiler le programme : `g++ nom_du_fichier.cpp -o nom_du_programme`

2. Exécuter le programme en spécifiant les arguments nécessaires :
   - `./nom_du_programme nom_du_fichier_svg largeur hauteur`

   Exemple : `./mon_programme image01.svg 800 600`

## Exemples

Le projet inclut des exemples de dessin de lignes, de rectangles, de texte, de croix rouge et de grilles dans le fichier `main`.

## Notes

- Le projet utilise C++ pour générer du code SVG, il est donc nécessaire d'avoir un compilateur C++ installé pour exécuter le programme.

- Le projet peut être étendu pour inclure d'autres formes ou fonctionnalités de dessin SVG en modifiant ou en ajoutant des fonctions.


