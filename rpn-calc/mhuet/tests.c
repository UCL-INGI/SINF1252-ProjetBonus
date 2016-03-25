#include<stdio.h>
#include<stdlib.h>
#include<CUnit/CUnit.h>
#include<CUnit/Basic.h>
void push(double value);
double pop();
double rpn(char *expr);
extern int stack_height;
extern double stack[10];
/* Check if the size of the stack is well incremented when push is called*/
// @push:pushTest1 => [Lorsque push est appelee, la taille du stack n est pas incrementee correctement]
void pushTest1()
{
	stack_height=0;
	push(3.5);
	CU_ASSERT_EQUAL(stack_height, 1);
}

/* Check if push puts the good value on top of the stack*/
// @push:pushTest2 => [Lorsque push est appelee, la valeur passee en parametre n est pas placee en haut du stack correctement]
void pushTest2()
{
	stack_height=0;
	push(3.5);
	CU_ASSERT_EQUAL(stack[0], 3.5);
}

/* Check if the size of the stack is well decremented when pop is called*/
//@pop:popTest1 => [Lorsque pop est appelee, la taille de la stack n est pas decrementee correctement]
void popTest1()
{
	stack_height=1;
	pop();
	CU_ASSERT_EQUAL(stack_height, 0);
}

/* Check if pop return the good value*/
// @pop:popTest2 => [La valeur retournee lorsque pop est appelee n est pas correcte]
void popTest2()
{
	stack_height=1;
	stack[0]=2.5;
	double res=pop();
	CU_ASSERT_EQUAL(res, 2.5);
}

/* Check a simple addition*/
// @rpn:simpleAdd => [rpn ne retourne pas le bon resultat pour l entree: \"2 3 +\"]
void simpleAdd()
{
	char str[6] = "2 3 +";
	CU_ASSERT_EQUAL(rpn(str), 5);
}

/* Check a simple soustraction*/
// @rpn:simpleDiff => [rpn ne retourne pas le bon resultat pour l entree: \"5 3 -\"]
void simpleDiff()
{
	char str[6] = "5 3 -";
	CU_ASSERT_EQUAL(rpn(str), 2);
}

/* Check a simple multiplication*/
// @rpn:simpleMult => [rpn ne retourne pas le bon resultat pour l entree: \"5 3 *\"]
void simpleMult()
{
	char str[6] = "5 3 *";
	CU_ASSERT_EQUAL(rpn(str), 15);
}

/* Check a simple division*/
// @rpn:simpleDiv => [rpn ne retourne pas le bon resultat pour l entree: \"5 3 /\"]
void simpleDiv()
{
	char str[7] = "15 3 /";
	CU_ASSERT_EQUAL(rpn(str), 5);
}

/* Check a simple division*/
// @rpn:addDiv => [rpn ne retourne pas le bon resultat pour l entree: \"2 3 + 2 /\"]
void addDiv()
{
	char str[10] = "2 3 + 2 /";
	CU_ASSERT_EQUAL(rpn(str), 2.5);
}

/* Check a simple division*/
// @rpn:divMinus => [rpn ne retourne pas le bon resultat pour l entree: \"6 3 / 1 -\"]
void divMinus()
{
	char str[10] = "6 3 / 1 -";
	CU_ASSERT_EQUAL(rpn(str), 1);
}

/* Check a simple division*/
// @rpn:minusTimes => [rpn ne retourne pas le bon resultat pour l entree: \"2 3 - 2 *\"]
void minusTimes()
{
	char str[10] = "2 3 - 2 *";
	CU_ASSERT_EQUAL(rpn(str), -2);
}

/* Check a simple division*/
// @rpn:timesAdd => [rpn ne retourne pas le bon resultat pour l entree: \"2 3 * 2 +\"]
void timesAdd()
{
	char str[10] = "2 3 * 2 +";
	CU_ASSERT_EQUAL(rpn(str), 8);
}

int main (int argc, char** argv)
{
 if(CUE_SUCCESS != CU_initialize_registry())
   {return CU_get_error();}
  CU_pSuite suitePushPop = CU_add_suite("Tests de Push et Pop",NULL,NULL);
  if(NULL== suitePushPop)
   	{
	 CU_cleanup_registry();
	return CU_get_error();
	}
  if(NULL==CU_add_test(suitePushPop, "Test si push incrémente bien stack_height", pushTest1)||NULL==CU_add_test(suitePushPop, "Test si push place bien le double passé en paramètre sur la pile", pushTest2)||NULL==CU_add_test(suitePushPop, "Test pop décrémente stack_height", popTest1)||NULL==CU_add_test(suitePushPop, "Test valeur pop", popTest2))
	{CU_cleanup_registry();
	return CU_get_error();}

  CU_pSuite suiteSimple = CU_add_suite("Simple Tests",NULL,NULL);

  if(NULL== suiteSimple)
   	{
	 CU_cleanup_registry();
	return CU_get_error();
	}
  if(NULL==CU_add_test(suiteSimple, "Test addition", simpleAdd)||NULL==CU_add_test(suiteSimple, "Test difference", simpleDiff)||NULL==CU_add_test(suiteSimple, "Test multiplication", simpleMult)||NULL==CU_add_test(suiteSimple, "Test division", simpleDiv))
	{CU_cleanup_registry();
	return CU_get_error();}

  CU_pSuite suiteDouble = CU_add_suite("Double Tests",NULL,NULL);

  if(NULL== suiteDouble)
   	{
	 CU_cleanup_registry();
	return CU_get_error();
	}
  if(NULL==CU_add_test(suiteDouble, "Test addition then division", addDiv)||NULL==CU_add_test(suiteDouble, "Test division then substraction", divMinus)||NULL==CU_add_test(suiteDouble, "Test substraction then multiplication", minusTimes)||NULL==CU_add_test(suiteDouble, "Test multiplication then addition", timesAdd))
	{CU_cleanup_registry();
	return CU_get_error();}
CU_basic_run_tests();
CU_basic_show_failures(CU_get_failure_list());
}
