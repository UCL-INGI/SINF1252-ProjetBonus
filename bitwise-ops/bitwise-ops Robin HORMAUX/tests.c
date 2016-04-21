#include <stdlib.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "../student_code_HORMAUX.h"

int init_suite(void) 	{return 0;}
int clean_suite(void) 	{return 0;}

void get_bit_test(void){
	unsigned int a = 59;
	CU_ASSERT_EQUAL(get_bit(a, 0), '1');
	CU_ASSERT_EQUAL(get_bit(a, 7), '0');
}

void set_bit_test(void){
	unsigned int a = 0;

	a = set_bit(a, 3, 1);
	CU_ASSERT_EQUAL(a, 8);

	a = set_bit(a, 3, 0);
	CU_ASSERT_EQUAL(a, 0);

	a = set_bit(a, 0, 1);
	CU_ASSERT_EQUAL(a, 1);

	a = set_bit(a, 0, 0);
	CU_ASSERT_EQUAL(a, 0);
}

void get_3_leftmost_bit_test(void){
	unsigned int a = 139;
	unsigned char b = get_3_leftmost_bit(a);
	CU_ASSERT_EQUAL(b, 0);

	a = 4294967295;
	b = get_3_leftmost_bit(a);
	CU_ASSERT_EQUAL(b, 15);
}

void get_4_rightmost_bit_test(void){
	unsigned int a = 139;
	unsigned char b = get_4_rightmost_bit(a);
	CU_ASSERT_EQUAL(b, 11);

	a = 4294967295;
	b = get_4_rightmost_bit(a);
	CU_ASSERT_EQUAL(b, 15);
}

void unset_first_bit_test(void){
	unsigned int a = 39;

	a = unset_first_bit(a);
	CU_ASSERT_EQUAL(a, 7);

	a = unset_first_bit(a);
	CU_ASSERT_EQUAL(a, 3);

	a = unset_first_bit(a);
	CU_ASSERT_EQUAL(a, 1);
}

void cycle_bits_test(void){
	unsigned int a = 1;

	a = cycle_bits(a, 2);
	CU_ASSERT_EQUAL(a, 4);

	a = cycle_bits(a, 3);
	CU_ASSERT_EQUAL(a, 32);

}

int main(int argc, const char *argv[]){

	CU_pSuite pSuite = NULL;

	//initiation du registre de test de CUnit
	if(CUE_SUCCESS != CU_initialize_registry() )
		return CU_get_error();

	//ajoute une suite au registre
	pSuite = CU_add_suite("Test Unitaires Bitwise", init_suite, clean_suite);
	if(NULL == pSuite){
		CU_cleanup_registry();
		return CU_get_error();
	}

	//ajoute les tests à la suite
	if ((NULL == CU_add_test(pSuite, "get_bit", get_bit_test)) ||
		(NULL == CU_add_test(pSuite, "set_bit", set_bit_test)) ||
		(NULL == CU_add_test(pSuite, "get_3_leftmost", get_3_leftmost_bit_test)) ||
		(NULL == CU_add_test(pSuite, "get_4_rightmost_bit", get_4_rightmost_bit_test)) ||
		(NULL == CU_add_test(pSuite, "unset_first_bit", unset_first_bit_test)) ||
		(NULL == CU_add_test(pSuite, "cycle_bits", cycle_bits_test))
		){
		CU_cleanup_registry();
		return CU_get_error();
	}

	//CU_console_run_tests();

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	printf("\n");
	CU_basic_show_failures(CU_get_failure_list());
	printf("\n\n");

	//nettoie le registre et return
	CU_cleanup_registry();
	return CU_get_error();
}
