# Projet de Génération et Dessin de Labyrinthe en C++

Ce projet vise à générer un labyrinthe aléatoire en utilisant un algorithme de génération de labyrinthe et à dessiner ce labyrinthe en format SVG à l'aide de C++. Le programme comporte plusieurs fonctionnalités clés pour accomplir cela.

## Auteur
- **Nom** : Celestin M'bemba Goumou
- **Niveau d'études** : L2 Informatique à l'ULCO

## Fonctionnalités

### Génération de Labyrinthe
- La fonction `initialiserLabyrinthe` initialise la structure du labyrinthe.
- La fonction `genererLabyrinthe` génère un labyrinthe aléatoire en utilisant l'algorithme de Kruskal.
- La fonction `effacerLabyrinthe` libère la mémoire allouée pour le labyrinthe.

### Écriture de Fichier SVG
- La fonction `ouvrirFichierSVG` ouvre un fichier SVG pour écrire.
- La fonction `fermerFichierSVG` ferme le fichier SVG après l'écriture.
- La fonction `ligne` écrit une ligne dans le fichier SVG.
- La fonction `rect` écrit un rectangle dans le fichier SVG.
- La fonction `text` écrit du texte dans le fichier SVG.

### Autres Fonctions
- `nombreDemur` compte le nombre de murs dans le labyrinthe.

## Utilisation

Le programme principal prend en compte trois arguments en ligne de commande :
- `nomFichier`: Nom du fichier SVG de sortie.
- `largeur`: Largeur du labyrinthe en cellules.
- `hauteur`: Hauteur du labyrinthe en cellules.

Exemple d'utilisation :
/mon_programme mon_labyrinthe.svg 10 10

Le programme générera un labyrinthe de 10x10 cellules et l'enregistrera dans un fichier SVG nommé `mon_labyrinthe.svg`.

## Implémentation Manquante

Le code fourni comprend des déclarations de fonctions liées à la gestion du labyrinthe, mais l'implémentation de ces fonctions est actuellement manquante. Vous devrez implémenter ces fonctions pour que le projet fonctionne correctement.

## Notes

- Le programme utilise C++ pour générer des fichiers SVG, assurez-vous d'avoir un compilateur C++ installé pour exécuter le programme.

- Le projet utilise un algorithme de génération de labyrinthe basé sur l'algorithme de Kruskal. L'implémentation de cet algorithme est importante pour générer des labyrinthes.

- Lors de l'exécution du programme, assurez-vous que la bibliothèque `<fstream>` est correctement incluse et que vous avez les droits d'écriture dans le répertoire où vous souhaitez enregistrer le fichier SVG.

N'hésitez pas à personnaliser ce README en fonction des besoins de votre projet et à ajouter des détails sur l'implémentation manquante. Bonne continuation !

