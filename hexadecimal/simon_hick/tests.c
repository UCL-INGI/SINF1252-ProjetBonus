#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "student_code.h"


//@strcat:test_hex_to_int1 => [hex_to_int ne donne pas la bonne valeur]
void test_hex_to_int1(void)
{
	CU_ASSERT_EQUAL( hex_to_int("A1C345"), 10601285);
}

//@strcat:test_hex_to_int2 => [hex_to_int ne renvoie pas 0 quand hex est NULL]
void test_hex_to_int2(void)
{
	CU_ASSERT_EQUAL( NULL, 0);
}

//@strcat:test_hex_to_int3 => [hex_to_int ne renvoie pas 0 quand hex est vide]
void test_hex_to_int3(void)
{
	CU_ASSERT_EQUAL( hex_to_int(""), 0);
}

//@strcat:test_hex_to_int4 => [hex_to_int ne renvoie pas 0 quand hex="0"]
void test_hex_to_int4(void)
{
	CU_ASSERT_EQUAL( hex_to_int("0"), 0);
}

//@strcat:test_hex_to_int5 => [hex_to_int ne renvoie pas 4294967295 quand hex="FFFFFFFF"]
void test_hex_to_int5(void)
{
	CU_ASSERT_EQUAL( hex_to_int("FFFFFFFF"), 4294967295);
}

//@strcat:test_hex_to_int6 => [hex_to_int ne renvoie pas 0 quand hex est trop grand que pour pouvoir etre mit dans un int ( c'est a dire plus grand que "FFFFFFFF" ou "4294967295" en decimal)]
void test_hex_to_int6(void)
{
	CU_ASSERT_EQUAL( hex_to_int("FFFFFFFFFFF"), 0);
}

//@strcat:test_hex_to_int7 => [hex_to_int ne renvoie pas 0 quand un charactere invalide est donne en argument]
void test_hex_to_int7(void)
{
	CU_ASSERT_EQUAL( hex_to_int("hex"), 0);
}

//@strcat:test_int_to_hex1 => [int_to_hex ne donne pas la bonne valeur]
void test_int_to_hex1(void)
{
	unsigned int i = 10601285;
	char* hex = malloc(sizeof(char)*6);
	if (hex == NULL) {
        CU_FAIL("Erreur lors l'allocation de la mémoire.");
        return;
    }
	int_to_hex(i,hex);
	CU_ASSERT_STRING_EQUAL(hex,"A1C345");
	free(hex);
}

//@strcat:test_int_to_hex2 => [int_to_hex doit retourner la meme adresse que celle donnee a l'argument dest]
void test_int_to_hex2(void)
{
	unsigned int i = 10601285;
	char* hex1 = malloc(sizeof(char)*6);
	if (hex1 == NULL) {
        CU_FAIL("Erreur lors l'allocation de la mémoire.");
        return;
    }
	char* hex2 = NULL;
	hex2 = int_to_hex(i,hex1);
	CU_ASSERT_PTR_EQUAL(hex1,hex2);
	free(hex1);
}

//@strcat:test_int_to_hex3 => [int_to_hex ne peut pas changer l'adresse de l'argument dest]
void test_int_to_hex3(void)
{
	unsigned int i = 10601285;
	char* hex1 = malloc(sizeof(char)*6);
	if (hex1 == NULL) {
        CU_FAIL("Erreur lors l'allocation de la mémoire.");
        return;
    }
	char** hex2 = &hex1;
	int_to_hex(i,hex1);
	CU_ASSERT_PTR_EQUAL(hex1,*hex2);
	free(hex1);
}
 
 //@strcat:test_int_to_hex4 => [int_to_hex ne retourne pas NULL quand dest est NULL]
void test_int_to_hex4(void)
{
	unsigned int i = 10601285;
	char* hex = NULL;
	int_to_hex(i,hex);
	CU_ASSERT_PTR_EQUAL(hex,NULL);
}

//@strcat:test_int_to_hex5 => [int_to_hex ne retoure pas 0 quand number=0]
void test_int_to_hex5(void)
{
	unsigned int i = 0;
	char* hex = malloc(sizeof(char));
	if (hex == NULL) {
        CU_FAIL("Erreur lors l'allocation de la mémoire.");
        return;
    }
	int_to_hex(i,hex);
	CU_ASSERT_STRING_EQUAL(hex,"0");
	free(hex);
}

//ne fonctionne pas encore avec le code actuel
//@strcat:test_int_to_hex6 => [int_to_hex ne donne pas la bonne valeur pour 4294967295 ]
void test_int_to_hex6(void)
{
	unsigned int i = 4294967295;
	char* hex = malloc(sizeof(char)*8);
	if (hex == NULL) {
        CU_FAIL("Erreur lors l'allocation de la mémoire.");
        return;
    }
    printf("\n number = %u\n",i );
	int_to_hex(i,hex);
	printf("\n hex = %s\n",hex );
	CU_ASSERT_STRING_EQUAL(hex,"FFFFFFFF");
	free(hex);
}

//@strcat:test_int_to_hex7 => [int_to_hex ne verifie pas que dest ait la bonne taille pour contenir les characteres]
void test_int_to_hex7(void)
{
	unsigned int i = 17;
	char* hex = malloc(sizeof(char));
	if (hex == NULL) {
        CU_FAIL("Erreur lors l'allocation de la mémoire.");
        return;
    }
	int_to_hex(i,hex);
	//a faire, teste avance
	free(hex);
}

int main()
{
    CU_pSuite pSuite = NULL;

    /* On initialise la suite de tests */
    if(CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* On ajoute la suite au registre */
    pSuite = CU_add_suite("Suite de tests pour l'exercice hexadecimal", NULL, NULL);
    if(NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* On ajoute les tests à la suite */
    if(NULL == CU_add_test(pSuite, "test_hex_to_int1", test_hex_to_int1) ||
       NULL == CU_add_test(pSuite, "test_hex_to_int2", test_hex_to_int2) ||
       NULL == CU_add_test(pSuite, "test_hex_to_int3", test_hex_to_int3) ||
       NULL == CU_add_test(pSuite, "test_hex_to_int4", test_hex_to_int4) ||
       NULL == CU_add_test(pSuite, "test_hex_to_int5", test_hex_to_int5) ||
       NULL == CU_add_test(pSuite, "test_hex_to_int6", test_hex_to_int6) ||
       NULL == CU_add_test(pSuite, "test_hex_to_int7", test_hex_to_int7) ||
       NULL == CU_add_test(pSuite, "test_int_to_hex1", test_hex_to_int1) ||
       NULL == CU_add_test(pSuite, "test_int_to_hex2", test_int_to_hex2) ||
       NULL == CU_add_test(pSuite, "test_int_to_hex3", test_int_to_hex3) ||
       NULL == CU_add_test(pSuite, "test_int_to_hex4", test_int_to_hex4) ||
       NULL == CU_add_test(pSuite, "test_int_to_hex5", test_int_to_hex5) ||
       NULL == CU_add_test(pSuite, "test_int_to_hex6", test_int_to_hex6) ||
       NULL == CU_add_test(pSuite, "test_int_to_hex7", test_int_to_hex7)
       ) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    /* On exécute les tests et on vide ensuite la mémoire utilisée par CUnit */
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}