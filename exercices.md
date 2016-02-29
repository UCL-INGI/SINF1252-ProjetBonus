# Liste des exercices proposés

### insertion-sort : Tri par insertion

On désire implémenter un algorithme de tri par insertion sur un tableau de N entiers, le tableau et sa taille étant passés en argument.

L'algorithme de tri est le suivant :
Pour chaque élément d'indice `i` (`i` variant de 1 à N-1)
* cet élément devient la clé
* on la compare avec l'élément d'indice `i-1`
* si la clé est plus petite, on les échange et on recommence la comparaison avec l'élément précédent (d'indice `i-2`) et ainsi de suite, tant que la clé est plus petite que l'élément qui lui précède (ou qu'on est revenu au début du tableau)
* quand la clé est à sa place (c'est-à-dire qu'elle est plus grande que ou égale à l'élément qui lui précède), la boucle intérieure est finie et on passe à l'élément d'indice `i+1`.

Écrivez le corps de la fonction `void tri(int T[], int taille);`.

_Tests imposés :_ Aucun.

### matrix-mult : Multiplication de matrices

Écrivez une fonction `int access(int *A, int taille, int ordonnee, int abscisse);` qui renvoie l'élément d'abscisse et d'ordonnée indiquées dans une matrice carrée `taille x taille` d'entiers (il s'agit donc de l'élément A\[ordonnee][abscisse]).

Écrivez une fonction qui effectue la multiplication de deux matrices carrées `taille x taille` d'entiers. Le prototype de la fonction est la suivante : `void mult(int *A, int *B, int *C, int taille)` et elle calcule `C = A x B`. Les trois matrices sont stockées sous forme de tableau ligne par ligne et la place de la matrice C est déjà allouée. 

_Tests imposés :_ Aucun.

### poly : Polynomes

On souhaite gérer des polynômes réels de degré inférieur ou égal à 10 en utilisant la structure suivante :

```typedef struct {
    double coeff[10];
} poly;```

qui servira à représenter le polynôme où coeff[0] est le coefficient du terme indépendant, coeff[1] le coefficient du terme en x, etc.

Écrivez une fonction `double eval(poly *P, double x)` qui calcule la valeur du polynôme P au point x. On pourra se servir de la formule de Horner : `P(x) = ((...(a_9*x + a_8)*x + a_7)*x + ...)x + a_1)*x + a_0` où `a_i` est `coeff[i]`.

Écrivez une fonction `poly *derivee(poly *P)` qui renvoie le polynôme exprimant la dérivée du polynôme P.

Écrivez une fonction `double racine(poly *P, double x0)` qui calcule via la méthode de Newton la racine du polynôme P.
La méthode est la suivante : on part d'un point initial, et on construit une suite de points qui se rapprochent de la racine en calculant à chaque étape un nouveau point à partir de la valeur du polynôme et de sa dérivée : `x_n+1 = x_n  - P(x_n)/P'(x_n)`. La fonction s'arrête lorsque `|P(x_n)| < 0.0001`. On suppose que le calcul converge toujours vers une racine.

_Tests imposés_ : Les tests à réaliser ici sont intuitifs, il faut toujours s'assurer que les valeurs renvoyées correspondent bien à la solution mathématique demandée. Vu les problèmes de précision des calculs en virgule flottante, vous devez tolérer les résultats avec un certain intervalle d'erreur. Fournissez au moins 3 tests par fonction, et au moins un des 9 tests doit aller jusqu'au degré 9.

### bookstore : Gestion d'une librairie

On souhaite gérer le catalogue d'une librairie dans lequel chaque livre est identifié par son auteur et son titre. La structure de données choisie est la suivante : il y a une liste chaînée d'auteurs dont chaque élément pointe vers une liste chaînée d'ouvrages.

```
typedef struct cellAuteur {
    char *auteur;
    struct cellLivre *Livres;
    struct cellAuteur *next;
} cellAuteur;

typedef struct cellLivre {
    char *titre;
    struct cellLivre *suiv;
} cellLivre;
```

Écrivez une fonction `cellAuteur *existe(cellAuteur *librairie, char *strAuteur)` qui teste si un auteur existe dans la liste `librairie` et dans ce cas renvoie un pointeur sur sa cellule de la liste (et `NULL` sinon).

Écrivez une fonction `int compteOuvrage(cellAuteur *librairie, char *strAuteur)` qui compte le nombre de livres d'un auteur dans la liste `librairie`.

Écrivez une fonction `void add(cellAuteur *librairie, char *strAuteur, char *strTitre)` qui ajoute dans le catalogue un livre de l'auteur indiqué. L'auteur existe dans le catalogue.

Écrivez une fonction `void supprimer(cellAuteur *librairie, char *strAuteur)` qui supprime du catalogue un auteur et tous ses livres. L'auteur existe dans le catalogue.

_Tests imposés_ : Outre les tests classiques, assurez-vous que la fonction `add` ne segfault pas lorsque vous lui indiquez un auteur dont la liste de livres est vide. Utilisez les fonctions `signal`, `sigsetjmp`et `siglongjmp` pour attraper un éventuel segfault dans `add` et pouvoir indiquer à l'utilisateur l'origine précise de ce segfault (il ne prend pas en compte le fait que la liste d'articles d'un auteur puisse être vide).
