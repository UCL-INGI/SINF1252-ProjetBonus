#include <stdlib.h>
#include <stdio.h>
#include <CUnit/basic.h>
#include "../student_code.h"

void test_hex_normal(void) {
	CU_ASSERT_STRING_EQUAL(hex_to_int(42), "2A");
}

void test_int_normal(void) {
	CU_ASSERT_EQUAL(int_to_hex("2A"),42);
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

	if (NULL == CU_add_test(pSuite, "test hexa normal", test_hex_normal) ||
		NULL == CU_add_test(pSuite, "test int normal", test_int_normal)
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
