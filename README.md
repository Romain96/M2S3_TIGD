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

## Documentation scientifique

L'algorithme implémenté ici est l'algorithme de calcul de l'arbre des coupes d'une
image en niveaux de gris proposé par L.Najman et M.Couprie :
"Building the component tree in quasi-linear time", L.Najman & M.Couprie

## Documentation technique

## Problèmes, limitations et résultats
