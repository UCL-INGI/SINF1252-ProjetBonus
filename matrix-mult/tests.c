#include <stdlib.h>
#include <stdio.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "student_code.h"

int A[3][3] = {{1,1,1},{2,2,2},{3,4,5}};
int B[3][3] = {{2,3,4},{1,2,3},{3,3,3}};
int *C = NULL;

int init_suite(void) {
    C = (int *)malloc(16*sizeof(int));
    if (C == NULL) {
        return EXIT_FAILURE;
    }
    return 0;
}

// @access:access_general_case => [la fonction access renvoie un mauvais élément]
void access_general_case(void)
{
    CU_ASSERT_EQUAL(access(*A, 3, 1, 1), 1);
    CU_ASSERT_EQUAL(access(*A, 3, 2, 1), 2);
    CU_ASSERT_EQUAL(access(*A, 3, 3, 1), 3);
    CU_ASSERT_EQUAL(access(*A, 3, 3, 2), 4);
}

// @mult:mult_general_case => [la fonction mult n'effectue pas correctement la multiplication matricielle]
void mult_general_case(void)
{
    mult(*A, *B, C, 3);
    CU_ASSERT_EQUAL(access(C, 3, 1, 1), 6);
    CU_ASSERT_EQUAL(access(C, 3, 1, 2), 8);
    CU_ASSERT_EQUAL(access(C, 3, 3, 1), 25);
}

int clean_suite(void) {
    free(C);
    return 0;
}

int main(int argc, char const *argv[]) {

    CU_pSuite pSuite = NULL;

    if(CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    pSuite = CU_add_suite("Suite de tests pour matrix_mult", init_suite, clean_suite);
    if(NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if(NULL == CU_add_test(pSuite, "test_access", access_general_case) ||
       NULL == CU_add_test(pSuite, "test_mult", mult_general_case))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
