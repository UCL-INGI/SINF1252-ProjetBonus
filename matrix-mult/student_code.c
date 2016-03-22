#include <stdio.h>
#include <stdlib.h>
#include "student_code.h"


/*
* precondition : A pointe vers le début d'une matrice carré d'entiers
* de dimension taille x taille
* postcondition : Renvoie l'élément A[ordonnee][abscisse]
*/
int access(int *A, int taille, int ordonnee, int abscisse) {
    int elem = *(A + (taille * (ordonnee - 1)) + abscisse - 1);
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
