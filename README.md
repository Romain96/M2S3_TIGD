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

Nous avons commencé par définir une classe Pixel permettant de représenter les pixels
de l'image traitée (assez similaire à la classe Point dans libtim).

L'algorithme choisi utilisant la structure d'ensembles disjoints et l'algorithme
"union-find" de Tarjan, nous avons mis en place une classe UFDSet (UnionFinDSet).
Les pixels de l'image pouvant être linérisés et traités par un indice unique
(i,j) -> j * largeur_image + i, cette structure n'a de fait pas besoin de contenir
les pixels eux-mêmes.

Les ensembles disjoints peuvent se contenter de travailler sur les entiers (indices)
uniquement et donc les champs **parents** et **ranks** sont des tableaux. Il n'y a donc
pas besoin de stocker explicitement des arbres disjoints mais seulement des entiers.

Avec ces structures, l'algorithme décrit dans l'article peut être implémenté
quasiment au mot près. Les pixels sont triés dans l'ordre décroissant de leur intensité
au moyen d'une file de priorité sur les pixels.

Il y a cependant un ajout qui a été nécessaire. Lorsqu'il faut traiter tous les voisins
q de p ayant déjà été traités et ayant une intensité supérieure ou égale à p, il est nécessaire
de connaitre lesdits voisins de p !
Ceci a été réalisé au moyen d'un tableau indexé sur les indices de pixels et contenant des booléens.
Au départ tous les pixels sont initialisés à faux et lorsqu'un pixel est traité (sorti hors de la file de priorité)
il est passé à vrai et pourra donc servir de voisin au pixel suivant (s'il est un voisin).

## Problèmes, limitations et résultats

Auparavant le programme s'arrêtait à cause de segfault.
Après investigation, il s'est avéré que la fonction **find** dans les **UFDSet**
provoquait des appels récursifs intriqués : parent de a valait b donc on cherchait
parent de b qui valait a et ainsi de suite jusqu'à submerger le pile d'appels et
provoquer un *stack overflow*.

Une solution temporaire a été de supprimer l'échange de a et b quand les rangs sont égaux.
Les arbres (ensembles) disjoints ne sont de fait plus équilibrés.
Note: la compression de chemin et l'union par rang sont toujours effectuées.
Cette solution est malheureusement toujours d'actualité.

Le deuxième problème relevé est que le résultat (l'arbre des coupes) obtenu comporte
tout un tas de noeuds avec une area de 1 (correspondant dont à des pixels isolés).
Sauf que les images utilisées n'avaient pas de pixels isolés...il s'agit donc de noeuds
qui ne devrait pas figurer dans l'arbre des coupes final. Les noeuds devant y figurer (area > 1)
eux s'y trouvent. C'est d'autant plus troublant que sur l'image **example.pgm** le résultat
n'implique pas les noeuds de pixels isolés mais sur l'image **test2_100_100.pgm** c'est tout
le contraire alors que ces deux images ont été fabriquées (avec Gimp) et ne contiennent que
des zones plates...
