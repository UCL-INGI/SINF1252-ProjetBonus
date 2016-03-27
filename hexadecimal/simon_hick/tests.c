/* Tests unitaires pour les exercice hexadecimal
Copyright (C) 2016 Simon Hick
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "student_code.h"


//@strcat:test_hex_to_int1 => [hex_to_int ne donne pas la bonne valeur]
void test_hex_to_int1(void)
{
	CU_ASSERT_EQUAL( hex_to_int("00A1C345"), 10601285);
}

//@strcat:test_hex_to_int2 => [hex_to_int ne renvoie pas 0 quand hex="0"]
void test_hex_to_int2(void)
{
	CU_ASSERT_EQUAL( hex_to_int("000000000"), 0);
}

//@strcat:test_hex_to_int3 => [hex_to_int ne renvoie pas 4294967295 quand hex="FFFFFFFF"]
void test_hex_to_int3(void)
{
	CU_ASSERT_EQUAL( hex_to_int("0FFFFFFFF"), 4294967295);
}

//@strcat:test_hex_to_int4 => [hex_to_int ne renvoie pas 0 quand hex est trop grand que pour pouvoir etre mit dans un int ( c'est a dire plus grand que "FFFFFFFF" ou "4294967295" en decimal)]
void test_hex_to_int4(void)
{
	CU_ASSERT_EQUAL( hex_to_int("FFFFFFFFFFF"), 0);
}

jmp_buf label_test_hex_to_int5;

void sig_handler1(int signo) {
    //Le signal handler a été exécuté, on a donc reçu un SIGSEGV
    //On provoque alors un jump vers le label avec le paramètre 1
    siglongjmp(label_test_hex_to_int5,1);
}

// Dans ce test, on va s'assurer que l'utilisateur n'accède pas à la mémoire située après la fin de la chaine de caractères
// @strcasecmp:test_hex_to_int5 => [hex_to_int accède à une adresse mémoire à droite de la zone mémoire de la chaine de caractères passée en argument.]
void test_hex_to_int5(void) {
  char* hex1 = NULL;

  //On cherche à allouer 2 pages de la mémoire, la première avec le droit d'écriture et de lecture
  void *ptr = mmap(NULL, getpagesize()*2, PROT_READ | PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
  if (ptr == MAP_FAILED) {
    CU_FAIL("La mémoire n'a pas pu être allouée pour le test test_hex_to_int5.");
    return;
  }

  // On protège ensuite la deuxième page mémoire en enlevant les droits de lecture et écriture
  mprotect(ptr+getpagesize(), getpagesize(), PROT_NONE);

  // On écrit à la fin de la première page mémoire la chaine "00A1C345"
  hex1 = (char*) ptr+getpagesize()-9;
  strcpy(hex1, "0011C345");

  /* Si le code de l'utilisateur accède à de la mémoire située après le caractère de fin \0,
   * autrement dit la mémoire protégée de la seconde page, un segfault sera envoyé.
   * La mécanique utilisée ici permet d'"attraper" un segfault sans que tout le programme ne plante */

  //On enregistre un signal handler. Cette fonction sera exécutée par le programme lorsque
  //le code produira une segmentation fault (ce qui lance le signal SIGSEGV).
  if (signal(SIGSEGV, sig_handler1) == SIG_ERR) {
      CU_FAIL("Impossible d'enregistrer un signal handler.");
      return;
  }

  //On définit ici un jump avec le label label_test_hex_to_int5 qui attend le paramètre 0 (par défaut)
  if(setjmp(label_test_hex_to_int5)==0) {
      CU_ASSERT_TRUE( hex_to_int(hex1) == 1164101);
  }
  else { //On a reçu un autre paramètre que 0, autrement dit le code a exécuté sig_handler
      //On a donc intercepté une segmentation fault, donc le code de l'utilisateur est fautif.
      CU_ASSERT_TRUE(0);
  }
        
  //On enlève le signal handler précédemment assigné à SIGSEGV
  signal(SIGSEGV, SIG_DFL);

  //On libère la mémoire précédemment allouée
  munmap(ptr, getpagesize()*2);
}

//@strcat:test_int_to_hex1 => [int_to_hex ne donne pas la bonne valeur]
void test_int_to_hex1(void)
{
	unsigned int i = 10601285;
	char* hex = malloc(sizeof(char)*6);
	if (hex == NULL) {
        CU_FAIL("Erreur lors l'allocation de la mémoire pendant le test test_int_to_hex1.");
        return;
    }
	int_to_hex(i,hex);
	CU_ASSERT_STRING_EQUAL(hex,"A1C345");
	free(hex);
}

//@strcat:test_int_to_hex2 => [int_to_hex doit retourner la meme adresse que celle donnee a l'argument dest]
void test_int_to_hex2(void)
{
	unsigned int i = 10601284;
	char* hex1 = malloc(sizeof(char)*6);
	if (hex1 == NULL) {
        CU_FAIL("Erreur lors l'allocation de la mémoire pendant le test test_int_to_hex2.");
        return;
    }
	char* hex2 = NULL;
	hex2 = int_to_hex(i,hex1);
	CU_ASSERT_PTR_EQUAL(hex1,hex2);
	free(hex1);
}

//@strcat:test_int_to_hex4 => [int_to_hex ne retourne pas "0" quand number=0]
void test_int_to_hex3(void)
{
	unsigned int i = 0;
	char* hex = malloc(sizeof(char));
	if (hex == NULL) {
        CU_FAIL("Erreur lors l'allocation de la mémoire pendant le test test_int_to_hex3.");
        return;
  }
	int_to_hex(i,hex);
	CU_ASSERT_STRING_EQUAL(hex,"0");
	free(hex);
}

jmp_buf label_test_int_to_hex4;

void sig_handler2(int signo) {
    //Le signal handler a été exécuté, on a donc reçu un SIGSEGV
    //On provoque alors un jump vers le label avec le paramètre 1
    siglongjmp(label_test_int_to_hex4,1);
}

// Dans ce test, on va s'assurer que l'utilisateur n'accède pas à la mémoire située après la fin de la chaine de caractères
// @strcasecmp:test_int_to_hex4 => [int_to_hex accède à une adresse mémoire à droite de la zone mémoire de la chaine de caractères passée en argument.]
void test_int_to_hex4(void) {
  unsigned int i = 10601281;
  char* hex1;

  //On cherche à allouer 2 pages de la mémoire, la première avec le droit d'écriture et de lecture
  void *ptr = mmap(NULL, getpagesize()*2, PROT_READ | PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
  if (ptr == MAP_FAILED) {
    CU_FAIL("La mémoire n'a pas pu être allouée pour le test test_int_to_hex6.");
    return;
  }

  // On protège ensuite la deuxième page mémoire en enlevant les droits de lecture et écriture
  mprotect(ptr+getpagesize(), getpagesize(), PROT_NONE);

  // On écrit à la fin de la première page mémoire une chaine de taille 9
  hex1 = (char*) ptr+getpagesize()-9;
  strcpy(hex1, "00000000");

  /* Si le code de l'utilisateur accède à de la mémoire située après le caractère de fin \0,
   * autrement dit la mémoire protégée de la seconde page, un segfault sera envoyé.
   * La mécanique utilisée ici permet d'"attraper" un segfault sans que tout le programme ne plante */

  //On enregistre un signal handler. Cette fonction sera exécutée par le programme lorsque
  //le code produira une segmentation fault (ce qui lance le signal SIGSEGV).
  if (signal(SIGSEGV, sig_handler2) == SIG_ERR) {
      CU_FAIL("Impossible d'enregistrer un signal handler.");
      return;
  }

  //On définit ici un jump avec le label label_test_int_to_hex6 qui attend le paramètre 0 (par défaut)
  if(setjmp(label_test_int_to_hex4)==0) {
      CU_ASSERT_PTR_NOT_NULL(int_to_hex(i,hex1));
  }
  else { //On a reçu un autre paramètre que 0, autrement dit le code a exécuté sig_handler
      //On a donc intercepté une segmentation fault, donc le code de l'utilisateur est fautif.
      CU_ASSERT_TRUE(0);
  }
        
  //On enlève le signal handler précédemment assigné à SIGSEGV
  signal(SIGSEGV, SIG_DFL);

  //On libère la mémoire précédemment allouée
  munmap(ptr, getpagesize()*2);
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
       NULL == CU_add_test(pSuite, "test_int_to_hex1", test_int_to_hex1) ||
       NULL == CU_add_test(pSuite, "test_int_to_hex2", test_int_to_hex2) ||
       NULL == CU_add_test(pSuite, "test_int_to_hex3", test_int_to_hex3) ||
       NULL == CU_add_test(pSuite, "test_int_to_hex4", test_int_to_hex4) ) 
    {
        CU_cleanup_registry();
        return CU_get_error();
    }


    /* On exécute les tests et on vide ensuite la mémoire utilisée par CUnit */
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}