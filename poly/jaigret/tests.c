/*
Systemes Informatique LSINF1252
Test unitaires pour les fonctions de poly
AIGRET Julien   8343-13-00

MARS 2016
*/

#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "student_code.h"




// Variables de test utilisées à travers le code
poly *test1, *test2, *test3, *test4;
double coeff1[]={10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
double coeff2[]={7.59, 13.87, 7.5631, 4.2, 3.55, 2.13, -32.12, 6.87, 2.0, 0.001};
double coeff3[]={1.0, 1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
double coeff4[]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

double x[]={1.0, 2.0, 0.0, -1.0};

double threshold = 0.001;

poly *newpoly(double a[10]) {
  poly *ret = (poly *) malloc(sizeof(poly));
  if (ret == NULL) exit(EXIT_FAILURE);
  for (int i = 0; i < 10; i++) {
    ret->coeff[i] = a[i];
  }
  return ret;
}




/* Tests pour savoir si eval reagis normalement a la premiere fonction*/
// @eval:test_eval_1 => [La fonction eval ne reagis pas correctement a un polynome de degre 9.]
void test_eval_1(void)
{
  double sol[] = {55.0, 2036.0, 10.0, 5.0};
  double test = 0;
  for (int i = 0; i < 4; i++) {
    test += sol[i] - eval(test1, x[i]);
  }
  int ass_less = fabs(test) < threshold;
  CU_ASSERT(ass_less);
}

/* Tests pour savoir si eval reagis normalement a la deuxieme fonction*/
// @eval:test_eval_2 => [La fonction eval ne reagis pas correctement a un polynome non-entier de degre 9.]
void test_eval_2(void)
{
  double sol[] = {15.6541, -439.6656, 7.5900, -38.4879};
  double test = 0;
  for (int i = 0; i < 4; i++) {
    test += sol[i] - eval(test2, x[i]);
  }
  int ass_less = fabs(test) < threshold;
  CU_ASSERT(ass_less);
}

/* Tests pour savoir si eval reagis normalement a la troisieme fonction*/
// @eval:test_eval_3 => [La fonction eval ne reagis pas correctement a un polynome a coefficients negatifs.]
void test_eval_3(void)
{
  double sol[] = {1.0, -1.0, 1.0, -1.0};
  double test = 0;
  for (int i = 0; i < 4; i++) {
    test += sol[i] - eval(test3, x[i]);
  }
  int ass_less = fabs(test) < threshold;
  CU_ASSERT(ass_less);
}

/* Tests pour savoir si eval reagis normalement a la quatrieme fonction*/
// @eval:test_eval_4 => [La fonction eval ne reagis pas correctement a un polynome nul.]
void test_eval_4(void)
{
  double sol[] = {0.0, 0.0, 0.0, 0.0};
  double test = 0;
  for (int i = 0; i < 4; i++) {
    test += sol[i] - eval(test4, x[i]);
  }
  int ass_less = fabs(test) < threshold;
  CU_ASSERT(ass_less);
}

/* Tests pour savoir si derivee reagis normalement a la premiere fonction*/
// @derivee:test_derivee_1 => [La fonction derivee ne reagis pas correctement a un polynome entier de degre 9.]
void test_derivee_1(void)
{
  double sol[] = {165,        7181,           9 ,          5};
  double test = 0;
  for (int i = 0; i < 4; i++) {
    test += sol[i] - eval(derivee(test1), x[i]);
  }
  int ass_less = fabs(test) < threshold;
  CU_ASSERT(ass_less);
}

/* Tests pour savoir si derivee reagis normalement a la deuxieme fonction*/
// @derivee:test_derivee_2 => [La fonction derivee ne reagis pas correctement a un polynome non-entier de degre 9.]
void test_derivee_2(void)
{
  double sol[] = { -62.1748, -660.4536,   13.8700,  232.6128};
  double test = 0;
  for (int i = 0; i < 4; i++) {
    test += sol[i] - eval(derivee(test2), x[i]);
  }
  int ass_less = fabs(test) < threshold;
  CU_ASSERT(ass_less);
}

/* Tests pour savoir si derivee reagis normalement a la troisieme fonction*/
// @derivee:test_derivee_3 => [La fonction derivee ne reagis pas correctement a un polynome entier negatif.]
void test_derivee_3(void)
{
  double sol[] = {-1,    -3,     1,     3};
  double test = 0;
  for (int i = 0; i < 4; i++) {
    test += sol[i] - eval(derivee(test3), x[i]);
  }
  int ass_less = fabs(test) < threshold;
  CU_ASSERT(ass_less);
}

/* Tests pour savoir si derivee reagis normalement a la quatrieme fonction*/
// @derivee:test_derivee_4 => [La fonction derivee ne reagis pas correctement a un polynome nul.]
void test_derivee_4(void)
{
  double sol[] = {0.0, 0.0, 0.0, 0.0};
  double test = 0;
  for (int i = 0; i < 4; i++) {
    test += sol[i] - eval(derivee(test4), x[i]);
  }
  int ass_less = fabs(test) < threshold;
  CU_ASSERT(ass_less);
}



/* Tests pour savoir si racine reagis normalement a la premiere fonction*/
// @racine:test_racine_1 => [La fonction racine ne reagis pas correctement a un polynome entier de degre 9.]
void test_racine_1(void)
{
  double test = racine(test1, -1);
  int ass_less = fabs(eval(test1,test)) < threshold;
  CU_ASSERT(ass_less);
}

/* Tests pour savoir si racine reagis normalement a la deuxieme fonction*/
// @racine:test_racine_2 => [La fonction racine ne reagis pas correctement a un polynome non-entier de degre 9.]
void test_racine_2(void)
{
  double test = racine(test2, 3);
  int ass_less = fabs(eval(test2,test)) < threshold;
  CU_ASSERT(ass_less);
}

/* Tests pour savoir si racine reagis normalement a la troisieme fonction*/
// @racine:test_racine_3 => [La fonction racine ne reagis pas correctement a un polynome entier negatif.]
void test_racine_3(void)
{
  double test = racine(test3, 2);
  int ass_less = fabs(eval(test3,test)) < threshold;
  CU_ASSERT(ass_less);
}

/* Tests pour savoir si racine reagis normalement a la quatrieme fonction*/
// @racine:test_racine4 => [La fonction racine ne reagis pas correctement a un polynome nul.]
void test_racine_4(void)
{
  double test = racine(test4, 3);
  int ass_less = fabs(eval(test4,test)) < threshold;
  CU_ASSERT(ass_less);
}



int setup(void)  {
  test1=newpoly(coeff1);
  test2=newpoly(coeff2);
  test3=newpoly(coeff3);
  test4=newpoly(coeff4);
  return 0;
}

int teardown(void) {
  free(test1);
  free(test2);
  free(test3);
  free(test4);
  return 0;
}

int main()
{
   CU_pSuite pSuite = NULL;
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   pSuite = CU_add_suite("Poly-Test-Suite", setup, teardown);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if ((NULL == CU_add_test(pSuite, "Eval Func 1",test_eval_1)) ||
       (NULL == CU_add_test(pSuite, "Eval Func 2",test_eval_2)) ||
       (NULL == CU_add_test(pSuite, "Eval Func 3",test_eval_3)) ||
       (NULL == CU_add_test(pSuite, "Eval Func 4",test_eval_4)) ||
       (NULL == CU_add_test(pSuite, "Derivee Func 1",test_derivee_1)) ||
       (NULL == CU_add_test(pSuite, "Derivee Func 2",test_derivee_2)) ||
       (NULL == CU_add_test(pSuite, "Derivee Func 3",test_derivee_3)) ||
       (NULL == CU_add_test(pSuite, "Derivee Func 4",test_derivee_4)) ||
       (NULL == CU_add_test(pSuite, "Racine Func 1",test_racine_1)) ||
       (NULL == CU_add_test(pSuite, "Racine Func 2",test_racine_2)) ||
       (NULL == CU_add_test(pSuite, "Racine Func 3",test_racine_3)) ||
       (NULL == CU_add_test(pSuite, "Racine Func 4",test_racine_4))
     )
   {
     CU_cleanup_registry();
     return CU_get_error();
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");

   CU_cleanup_registry();
   return CU_get_error();
}
