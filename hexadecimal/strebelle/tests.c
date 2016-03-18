#include <stdlib.h>
#include <stdio.h>
#include <CUnit/basic.h>
#include "../student_code.h"

// @hex_to_int:hex_0 => L'entier 0 ne donne pas 0 en hexadécimal
void test_hex_0(void) {
	char *hex = hex_to_int(0);
	CU_ASSERT_STRING_EQUAL(hex, "0");
	free(hex);
}

// @int_to_hex:int_0 => Le nombre hexadécimal 0 ne donne pas l'entier 0
void test_int_0(void) {
	char *hex = "0";
	unsigned int n = int_to_hex(hex);
	CU_ASSERT_EQUAL(n, 0);
}

// @hex_to_int:hex_normal => L'entier 42 ne donne pas 2A en hexadécimal
void test_hex_normal(void) {
	char *hex = hex_to_int(42);
	CU_ASSERT_STRING_EQUAL(hex, "2A");
	free(hex);
}

// @int_to_hex:int_normal => Le nombre hexadécimal 2A ne donne pas l'entier 42
void test_int_normal(void) {
	unsigned int n = int_to_hex("2A");
	CU_ASSERT_EQUAL(n,42);
}

// @hex_to_int:hex_big => Le plus grand entier non signé ne donne pas FFFFFFFF en hexadécimal
void test_hex_bigvalue(void) {
	unsigned int big = 0-1;
	char *hex = hex_to_int(big);
	CU_ASSERT_STRING_EQUAL(hex, "FFFFFFFF");
	free(hex);
}

// @int_to_hex:int_big => Le nombre hexadécimal FFFFFFFF ne donne pas le plus grand entier non signé
void test_int_bigvalue(void) {
	char *hex = "FFFFFFFF";
	unsigned int n = int_to_hex(hex);
	unsigned int big = 0-1;
	CU_ASSERT_EQUAL(n, big);
}

int setup(void) {
	return 0;
}

int teardown(void) {
	return 0;
}

int main(int argc, char const *argv[]) {
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	CU_pSuite pSuite = NULL;
	CU_pSuite pSuite2 = NULL;

	pSuite = CU_add_suite("Suite de tests : hex_to_int", setup, teardown);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite, "Hexa 0", test_hex_0) ||
		NULL == CU_add_test(pSuite, "Hexa normal", test_hex_normal) ||
		NULL == CU_add_test(pSuite, "Hexa big value", test_hex_bigvalue)
	) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	pSuite2 = CU_add_suite("Suite de tests : int_to_hex", setup, teardown);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite2, "Int 0", test_int_0) ||
		NULL == CU_add_test(pSuite2, "Int normal", test_int_normal) ||
		NULL == CU_add_test(pSuite2, "Int big value", test_int_bigvalue)
	) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_basic_show_failures(CU_get_failure_list());
	printf("\n\n");
	CU_cleanup_registry();

	return CU_get_error();
}
