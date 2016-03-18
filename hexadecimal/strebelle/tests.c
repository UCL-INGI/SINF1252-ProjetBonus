#include <stdlib.h>
#include <stdio.h>
#include <CUnit/basic.h>
#include "../student_code.h"

void test_int_0(void) {
	char *hex = hex_to_int(0);
	CU_ASSERT_STRING_EQUAL(hex, "0");
	free(hex);
}

void test_hex_0(void) {
	char *hex = "0";
	unsigned int n = int_to_hex(hex);
	CU_ASSERT_EQUAL(n, 0);
}

void test_hex_normal(void) {
	char *hex = hex_to_int(42);
	CU_ASSERT_STRING_EQUAL(hex, "2A");
	free(hex);
}

void test_int_normal(void) {
	unsigned int n = int_to_hex("2A");
	CU_ASSERT_EQUAL(n,42);
}

void test_hex_bigvalue(void) {
	unsigned int big = 0-1;
	char *hex = hex_to_int(big);
	CU_ASSERT_STRING_EQUAL(hex, "FFFFFFFF");
	free(hex);
}

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
	pSuite = CU_add_suite("Suite de tests : hexadecimal", setup, teardown);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite, "Int 0", test_int_0) ||
		NULL == CU_add_test(pSuite, "Hexa 0", test_hex_0) ||
		NULL == CU_add_test(pSuite, "Hexa normal", test_hex_normal) ||
		NULL == CU_add_test(pSuite, "Int normal", test_int_normal) ||
		NULL == CU_add_test(pSuite, "Hexa big value", test_hex_bigvalue) ||
		NULL == CU_add_test(pSuite, "Int big value", test_int_bigvalue)
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
