/* Tests unitaires pour le mini-projet-string
Copyright (C) 2016 Mathieu Xhonneux

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

void *calloc2(size_t nmemb, size_t size) {
    void *ptr = malloc(nmemb*size);

    // if (ptr != NULL || 1) // Cette ligne fait échouer le test test_calloc2_3
    // if (ptr != NULL && 0) // Cette ligne fait échouer le test test_calloc2_2
    if (ptr != NULL) { //Si l'appel à malloc n'a pas échoué
        for(unsigned int i=0; i < nmemb*size; i++) {
            *(char *)(ptr+i) = 0; //On initialise à 0 toute la mémoire
        }
    }
    return ptr;
}

