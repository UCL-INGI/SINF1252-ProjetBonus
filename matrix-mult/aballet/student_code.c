/* Tests unitaires pour matrix-mult

Copyright (C) 2016 Adrien Ballet

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include "student_code.h"

/*
Fonction access : retourne l'incide (ordonnee, abscisse) de la matrice carrée A.
@pre : *A est un pointeur vers le premier indice de la matrice A, taille est la
taille de la matrice A (taille*taille) et ordonne et abscisse sont les coordonnées
de l'élément à retourner.
@post : renvoie l'indice demandé.
*/
int access(int *A, int taille, int ordonnee, int abscisse) {
    return *(A + taille*(ordonnee-1) + abscisse-1);
}

/*
Fonction mult : multiplie les matrices carrées A et B, et enregistre le résultat dans C.
@pre : *A, *B, *C sont des pointeurs vers le premier indice de chaque matrice,
taille est la taille des trois matrices (taille*taille).
@post : la fonction mult ne renvoie rien.
*/
void mult(int *A, int *B, int *C, int taille) {
    for (size_t i = 0; i < taille; i++) {
        for (size_t j = 0; j < taille; j++) {
            int sum = 0;
            for (size_t k = 0; k < taille; k++) {
                // Application de la formule de multiplication matricielle.
                sum = sum + access(A, taille, i+1, k+1)*access(B, taille, k+1, j+1);
            }
            *(C + taille*i + j) = sum; // Ecriture du résultat
        }
    }
}
