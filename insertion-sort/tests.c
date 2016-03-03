/* Tests unitaires pour l'exercice insertion-sort
Copyright (C) 2016 Damiano-Joseph Siciliano

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

#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "student_code.h"

char *globStr = NULL;

/* La fonction d'initialisation de la suite de tests.
* Retourne 0 en cas de succès, n'importe quelle autre valeur indique un échec.
*/
int init_suite1(void) {
    //On cherche à allouer un bloc mémoire qui sera utilisé dans nos tests
    globStr = malloc(sizeof(char)*20);
    if (globStr == NULL)
        return -1;

    return 0;
}

/* La fonction de "nettoyage" de la suite de tests.
* Retourne 0 en cas de succès, n'importe quelle autre valeur indique un échec.
*/
int clean_suite1(void) {
    free(globStr); //on libère la mémoire allouée lors de l'initialisation de la suite
    return 0;
}


// @tri:test_tri1 => [Lorsque tri est appelé avec {4,3,2,1} et 4 comme argument, il ne renvoie pas {1,2,3,4}]
void test_tri1(void) {
    int a []= {4,3,2,1}; 
    int b []= {1,2,3,4};
    tri(a,4);
    for(int i=0;i<4;i++){
    	CU_ASSERT_EQUAL(a[i], b[i]); 
    } 
}

// @tri:test_tri2 => [Lorsque tri est appelé avec {0,0,0,0} et 4 comme argument, il ne renvoie pas {0,0,0,0}]
void test_tri2(void) {
    int a []= {0,0,0,0}; 
    int b []= {0,0,0,0};
    tri(a,4);
    for(int i=0;i<4;i++){
    	CU_ASSERT_EQUAL(a[i], b[i]); 
    }
}

// @tri:test_tri3 => [Lorsque tri est appelé avec {0,6,0,6,0} et 5 comme argument, il ne renvoie pas {0,0,0,6,6}]
void test_tri3(void) {
    int a []= {0,6,0,6,0}; 
    int b []= {0,0,0,6,6};
    tri(a,5);
    for(int i=0;i<5;i++){
    	CU_ASSERT_EQUAL(a[i], b[i]); 
    }
}

// @tri:test_tri4 => [Lorsque tri est appelé avec {3,4,5,1,2} et 5 comme argument, il ne renvoie pas {1,2,3,4,5}]
void test_tri4(void) {
    int a []= {3,4,5,1,2}; 
    int b []= {1,2,3,4,5};
    tri(a,5);
    for(int i=0;i<5;i++){
    	CU_ASSERT_EQUAL(a[i], b[i]); 
    }
}

// @tri:test_tri5 => [Lorsque tri est appelé avec {2,1,3,4,5} et 5 comme argument, il ne renvoie pas {1,2,3,4,5}]
void test_tri5(void) {
    int a []= {2,1,3,4,5}; 
    int b []= {1,2,3,4,5};
    tri(a,5);
    for(int i=0;i<5;i++){
    	CU_ASSERT_EQUAL(a[i], b[i]); 
    }
}

// @tri:test_tri6 => [Lorsque tri est appelé avec {1,2,3,5,4} et 5 comme argument, il ne renvoie pas {1,2,3,4,5}]
void test_tri6(void) {
    int a []= {1,2,3,5,4}; 
    int b []= {1,2,3,4,5};
    tri(a,5);
    for(int i=0;i<5;i++){
    	CU_ASSERT_EQUAL(a[i], b[i]); 
    }
}

// @tri:test_tri7 => [Lorsque tri est appelé avec {42} et 1 comme argument, il ne renvoie pas {42}]
void test_tri7(void) {
    int a []= {42}; 
    tri(a,1);
    CU_ASSERT_EQUAL(a[0], 42); 
}



int main() {
    CU_pSuite pSuite = NULL;

    /* On initialise la suite de tests */
    if(CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* On ajoute la suite au registre */
    pSuite = CU_add_suite("Suite de tests pour l'exercice insertion-sort", init_suite1, clean_suite1);
    if(NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* On ajoute les tests à la suite. L'ordre est important !
     * test_strlen1 sera exécuté en premier, puis test_strlen2, etc ...*/
    if(NULL == CU_add_test(pSuite, "test_tri1", test_tri1) ||
       NULL == CU_add_test(pSuite, "test_tri2", test_tri2) ||
       NULL == CU_add_test(pSuite, "test_tri3", test_tri3) ||
       NULL == CU_add_test(pSuite, "test_tri4", test_tri4) ||
       NULL == CU_add_test(pSuite, "test_tri5", test_tri5) ||
       NULL == CU_add_test(pSuite, "test_tri6", test_tri6) ||
       NULL == CU_add_test(pSuite, "test_tri7", test_tri7) 
       ) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    /* On exécute les tests et on vide ensuite la mémoire utilisée par CUnit */
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
