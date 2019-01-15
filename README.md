# Traitement d'Images et Géométrie Discrète

## Organisation

auteurs :

* Romain Perrin <romain.perrin@etu.unistra.fr>
* Maxime Seyer <maxime.seyer@etu.unistra.fr>

| Répertoire | Fichier | Description |
|---|---|---|
| libtim | * | Bibliothêque libtim utilisée pour manipuler les images (I/O) |
| articles | Najman06.pdf | Article sur l'algorithme de Najman et Couprie utilisé |
| articles | Carlinet-Géraud_ISMM_MaxTree.pdf | Articles sur les comparaisons d'algorithmes de maxtree |
| images | * | Ensemble d'images utilisées pour les tests |
| include | Pixel.h | Classe Pixel utilisée pour représenter un pixel de l'image (i,j,valeur) |
| include | UFDSet.h | Classe UFDSet représentant des ensembles disjoints (algo union-find de Tarjan) |
| include | CNode.h | Classe CNode représentant un noeud de l'arbre des coupes |
| include | CTree.h | Classe CTree représentant l'arbre des coupes |
| src | Pixel.hxx | Code de la classe Pixel |
| src | UFDSet.hxx | Code de la classe UFDSet |
| src | CNode.hxx | Code de la classe CNode |
| src | CTree.hxx | Code de la classe CTree |
| graphs | * | Graphes (arbres des coupes) générés au format dot |

## Documentation utilisateur

Le projet a été développé en C++.

Un makefile est fourni pour le compiler.

`make` ou `make componentTree`

Le programme attends deux paramètres :
- une image binaire PGM à traiter
- un nom de fichier DOT pour sauvegarder le résultat

Quelques images sont founies dans le répertoire **images** et par défaut
les images sont recherchées dans ce répertoire.
Les résultats (l'arbre des coupes) sera sauvegardé au format DOT dans le répertoire
**graphs** avec le nom donné en paramètre.

Par exemple `./componentTree lena.pgm lena.dot` traitera l'image **images/lena.pgm**
et sauvegardera le résultat dans un fichier nommé **graphs/lena.dot**.

## Documentation scientifique

L'algorithme implémenté ici est l'algorithme de calcul de l'arbre des coupes d'une
image en niveaux de gris proposé par L.Najman et M.Couprie :
"Building the component tree in quasi-linear time", L.Najman & M.Couprie

L'algorithme consiste à traiter les pixels de l'image dans l'ordre décroissant
de leur intensité. On maintient une deux structures d'ensembles disjoints en
utilisant l'algorithme "union-find" proposé par Tarjan, une concernant les noeuds
et une autre concernant les arbres. Ces deux structures permettent de fusioner les
zone de l'image contenant des pixels de même intensité et étant liés par une relation
de voisinage (ces pixels font partie de la même composante connexe).
Un dernier passage est nécessaire afin d'attribuer à chaque pixel, le noeud de l'arbre
dans lequel il se trouve.

## Documentation technique

## Problèmes, limitations et résultats
