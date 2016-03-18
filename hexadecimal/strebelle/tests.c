#include <stdlib.h>
#include <stdio.h>
#include <CUnit/basic.h>
#include "../student_code.h"

// @hex_to_int:hex_0 => [la fonction ne gère pas l'entier nul]
void test_hex_0(void) {
	char *hex = hex_to_int(0);
	CU_ASSERT_STRING_EQUAL(hex, "0");
	free(hex);
}

// @int_to_hex:int_0 => [la fonction ne gère pas le nombre hexadécimal nul]
void test_int_0(void) {
	unsigned int n = int_to_hex("0");
	CU_ASSERT_EQUAL(n, 0);
}

// @hex_to_int:hex_normal => [la fonction ne renvoie pas les bonnes valeurs (42->2A, 19->13, 408->198)]
void test_hex_normal(void) {
	char *hex = hex_to_int(42);
	CU_ASSERT_STRING_EQUAL(hex, "2A");
	free(hex);
	hex = hex_to_int(19);
	CU_ASSERT_STRING_EQUAL(hex, "13");
	free(hex);
	hex = hex_to_int(408);
	CU_ASSERT_STRING_EQUAL(hex, "198");
	free(hex);
}

// @int_to_hex:int_normal => [la fonction ne renvoie pas les bonnes valeurs (2A->42, 13->19, 198->408)]
void test_int_normal(void) {
	unsigned int n = int_to_hex("2A");
	CU_ASSERT_EQUAL(n, 42);
	n = int_to_hex("13");
	CU_ASSERT_EQUAL(n, 19);
	n = int_to_hex("198");
	CU_ASSERT_EQUAL(n, 408);
}

// @hex_to_int:hex_big => [la fonction ne gère pas l'entier non signé le plus grand]
void test_hex_bigvalue(void) {
	unsigned int big = 0-1;
	char *hex = hex_to_int(big);
	CU_ASSERT_STRING_EQUAL(hex, "FFFFFFFF");
	free(hex);
}

// @int_to_hex:int_big => [la fonction ne gère pas le nombre hexadécimal le plus grand sur 8 bits]
void test_int_bigvalue(void) {
	unsigned int n = int_to_hex("FFFFFFFF");
	unsigned int big = 0-1;
	CU_ASSERT_EQUAL(n, big);

}

// @hex_to_int:hex_0_inside => [la fonction ne gère pas les nombres hexadécimaux contenant des 0]
void test_hex_0_inside(void) {
	char *hex = hex_to_int(1037);
	CU_ASSERT_STRING_EQUAL(hex, "40D");
}

// @int_to_hex:int_0_inside => [la fonction ne gère pas les nombres hexadécimaux contenant des 0]
void test_int_0_inside(void) {
	unsigned int n = int_to_hex("40D");
	CU_ASSERT_EQUAL(n, 1037);
}

// @hex_to_int:hex_crit => [la fonction ne gère pas les valeurs critiques (1->1, 16->10, 17->11)]
void test_hex_crit(void) {
	char *hex = hex_to_int(1);
	CU_ASSERT_STRING_EQUAL(hex, "1");
	free(hex);
	hex = hex_to_int(16);
	CU_ASSERT_STRING_EQUAL(hex, "10");
	free(hex);
	hex = hex_to_int(17);
	CU_ASSERT_STRING_EQUAL(hex, "11");
	free(hex);
}

// @int_to_hex:int_crit => [la fonction ne gère pas les valeurs critiques (1->1, 10->16, 11->17)]
void test_int_crit(void) {
	unsigned int n = int_to_hex("1");
	CU_ASSERT_EQUAL(n, 1);
	n = int_to_hex("10");
	CU_ASSERT_EQUAL(n, 16);
	n = int_to_hex("11");
	CU_ASSERT_EQUAL(n, 17);
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

	pSuite = CU_add_suite("hex_to_int", setup, teardown);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite, "Hexa 0", test_hex_0) ||
		NULL == CU_add_test(pSuite, "Hexa normal", test_hex_normal) ||
		NULL == CU_add_test(pSuite, "Hexa big value", test_hex_bigvalue) ||
		NULL == CU_add_test(pSuite, "Hexa 0 inside", test_hex_0_inside) ||
		NULL == CU_add_test(pSuite, "Hexa critic value", test_hex_crit)
	) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	pSuite2 = CU_add_suite("int_to_hex", setup, teardown);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite2, "Int 0", test_int_0) ||
		NULL == CU_add_test(pSuite2, "Int normal", test_int_normal) ||
		NULL == CU_add_test(pSuite2, "Int big value", test_int_bigvalue) ||
		NULL == CU_add_test(pSuite2, "Int 0 inside", test_int_0_inside) ||
		NULL == CU_add_test(pSuite2, "Int critic value", test_int_crit)
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
