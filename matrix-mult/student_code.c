#include <stdio.h>
#include <stdlib.h>
#include "student_code2.h"


/*
* precondition : A pointe vers le début d'une matrice carré d'entiers
* de dimension taille x taille
* postcondition : Renvoie l'élément A[ordonnee][abscisse]
*/
int access(int *A, int taille, int ordonnee, int abscisse) {
    int elem = *(A + abscisse - 1 + (taille * (ordonnee - 1)));
    return elem;
}

/*
* precondition : A, B, C sont des pointeurs vers le premier élément de matrices carrés d'entiers
* de dimension taille x taille
* postcondition : remplit C par le résultat obtenu parle produit matricielle A x B.
*/
void mult(int *A, int *B, int *C, int taille) {

  int sum = 0;

  for (size_t i = 0; i < taille; i++) {
      for (size_t j = 0; j < taille; j++) {
          sum = 0;
          for (size_t k = 0; k < taille; k++) {
              sum += *(A + (i * taille) + k) * *(B + (k * taille) + j);
          }
          *(C + taille * i + j) = sum;
      }
  }

}

/*
* préconditions : rang est le rang de la matrice carré génerée
* postcondition : retourne un pointeur vers une matrice de taille rang génerée aléatoirement
* (les valeurs sont compris entre 0 et 25)
*/
int * randomMatrice(size_t rang){

  int * A = (int *)malloc(rang*rang*sizeof(int));

  for (size_t i = 0; i < (rang*rang); i++) {
    *(A+i) = (rand()%26);
  }

  return A;
}
