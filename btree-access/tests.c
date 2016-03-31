#include<stdio.h>
#include<stdlib.h>
#include<CUnit/CUnit.h>
#include<CUnit/Basic.h>
#include "student_code.h"
// @btreeaccess : keyOnFirst => [Votre fonction n'arrive pas trouver la clée sur le noeud entré directement en paramètre!]
void keyOnFirst(void)
{
	Node G={35,2,NULL,NULL};
	Node F={25,133,NULL,NULL};
	Node E={15,24,NULL,NULL};
	Node D={5,4,NULL,NULL};
	Node C={30,74,&F,&G};
	Node B={10,36,&D,&E};
	Node A={20,23,&B,&C};
	
	int* ptr1=has_key(A,20);
	CU_ASSERT_EQUAL(*(ptr1),23);
	
}
// @btreeaccess : keyNotHere => [Votre fonction ne renvoie pas NULL quand la clée n'est pas présente!]
void keyNotHere(void)
{
	Node G={35,2,NULL,NULL};
	Node F={25,133,NULL,NULL};
	Node E={15,24,NULL,NULL};
	Node D={5,4,NULL,NULL};
	Node C={30,74,&F,&G};
	Node B={10,36,&D,&E};
	Node A={20,23,&B,&C};
	
	int* ptr1=has_key(A,3);
	CU_ASSERT_PTR_NULL(ptr1);
}
// @btreeaccess : keyOnLeft => [Votre fonction ne renvoie pas une valeur correcte lorsque le clée se trouve dans un noeud à gauche de la racine !]
void keyOnLeft(void)
{
	Node G={35,2,NULL,NULL};
	Node F={25,133,NULL,NULL};
	Node E={15,42,NULL,NULL};
	Node D={5,4,NULL,NULL};
	Node C={30,74,&F,&G};
	Node B={10,36,&D,&E};
	Node A={20,23,&B,&C};
	
	int* ptr1=has_key(A,15);
	
	CU_ASSERT_EQUAL(*(ptr1),42);
}
// @btreeaccess : keyOnRight => [Votre fonction ne renvoie pas une valeur correcte lorsque le clée se trouve dans un noeud à droite de la racine !]
void keyOnRight(void)
{
	Node G={35,2,NULL,NULL};
	Node F={25,19,NULL,NULL};
	Node E={15,24,NULL,NULL};
	Node D={5,4,NULL,NULL};
	Node C={30,74,&F,&G};
	Node B={10,36,&D,&E};
	Node A={20,23,&B,&C};
	
	int* ptr1=has_key(A,25);
	
	CU_ASSERT_EQUAL(*(ptr1),19);
}
// @btreeaccess : treesEquals => [Votre fonction ne renvoie pas 1 alors que les deux arbres sont égaux!]
void treesEquals(void)
{
	Node G={35,2,NULL,NULL};
	Node F={25,133,NULL,NULL};
	Node E={15,24,NULL,NULL};
	Node D={5,4,NULL,NULL};
	Node C={30,74,&F,&G};
	Node B={10,36,&D,&E};
	Node A={20,23,&B,&C};
	
	Node N={35,2,NULL,NULL};
	Node M={25,133,NULL,NULL};
	Node L={15,24,NULL,NULL};
	Node K={5,4,NULL,NULL};
	Node J={30,74,&M,&N};
	Node I={10,36,&K,&L};
	Node H={20,23,&I,&J};
	
	int result=compare(A,H);
	CU_ASSERT_EQUAL(result,1);
}
// @btreeaccess : treesWithDifferentsValues => [Votre fonction ne renvoie pas 0 alors que les deux arbres possèdent des noeuds avec des valeurs différentes!]
void treesWithDifferentsValues(void)
{
	Node G={35,2,NULL,NULL};
	Node F={25,1,NULL,NULL};
	Node E={15,24,NULL,NULL};
	Node D={5,4,NULL,NULL};
	Node C={30,74,&F,&G};
	Node B={10,36,&D,&E};
	Node A={20,23,&B,&C};
	
	Node N={35,2,NULL,NULL};
	Node M={25,133,NULL,NULL};
	Node L={15,24,NULL,NULL};
	Node K={5,4,NULL,NULL};
	Node J={30,74,&M,&N};
	Node I={10,36,&K,&L};
	Node H={20,23,&I,&J};
	
	int result=compare(A,H);
	CU_ASSERT_EQUAL(result,0);
}
// @btreeaccess : treesWithDifferentsKeys => [Votre fonction ne renvoie pas 0 alors que les deux arbres possèdent des noeuds avec des clées différentes!]
void treesWithDifferentsKeys(void)
{
	Node G={35,2,NULL,NULL};
	Node F={25,133,NULL,NULL};
	Node E={15,24,NULL,NULL};
	Node D={5,4,NULL,NULL};
	Node C={30,74,&F,&G};
	Node B={7,36,&D,&E};
	Node A={20,23,&B,&C};
	
	Node N={35,2,NULL,NULL};
	Node M={25,133,NULL,NULL};
	Node L={15,24,NULL,NULL};
	Node K={5,4,NULL,NULL};
	Node J={30,74,&M,&N};
	Node I={10,36,&K,&L};
	Node H={20,23,&I,&J};
	
	int result=compare(A,H);
	CU_ASSERT_EQUAL(result,0);
}
// @btreeaccess : treesWithDifferentsLeftPart => [Votre fonction ne renvoie pas 0 alors que les deux arbres ont une structure différente à gauche!]
void treesWithDifferentLeftPart(void)
{
	Node G={35,2,NULL,NULL};
	Node F={25,133,NULL,NULL};
	Node E={15,24,NULL,NULL};
	Node D={5,4,NULL,NULL};
	Node C={30,74,&F,&G};
	Node B={10,36,&D,&E};
	Node A={20,23,&B,&C};
	
	Node N={35,2,NULL,NULL};
	Node M={25,133,NULL,NULL};
	Node K={5,4,NULL,NULL};
	Node J={30,74,&M,&N};
	Node I={10,36,&K,NULL};
	Node H={20,23,&I,&J};
	
	int result=compare(A,H);
	CU_ASSERT_EQUAL(result,0);
}
// @btreeaccess : treesWithDifferentsRightPart => [Votre fonction ne renvoie pas 0 alors que les deux arbres ont une structure différente à droite!]
void treesWithDifferentsRightPart(void)
{
	Node G={35,2,NULL,NULL};
	Node F={25,133,NULL,NULL};
	Node E={15,24,NULL,NULL};
	Node D={5,4,NULL,NULL};
	Node C={30,74,&F,&G};
	Node B={10,36,&D,&E};
	Node A={20,23,&B,&C};
	
	Node N={35,2,NULL,NULL};
	Node L={15,24,NULL,NULL};
	Node K={5,4,NULL,NULL};
	Node J={30,74,NULL,&N};
	Node I={10,36,&K,&L};
	Node H={20,23,&I,&J};
	
	int result=compare(A,H);
	CU_ASSERT_EQUAL(result,0);
}
int main (int argc, char** argv)
{
	
 if(CUE_SUCCESS != CU_initialize_registry())
   {return CU_get_error();}
  CU_pSuite pSuiteHasKey = CU_add_suite("Suite de Test pour la fonction int *has_key(Node root,int key)",NULL,NULL);
  CU_pSuite pSuiteCompare = CU_add_suite("Suite de Test pour la fonction int compare(Node root_a, Node root_b)",NULL,NULL);
 
  if(NULL== pSuiteHasKey||NULL==pSuiteCompare)
   	{
	 CU_cleanup_registry();
	return CU_get_error();
	}
  if(NULL==CU_add_test(pSuiteHasKey, "keyOnFirst", keyOnFirst)||
     NULL==CU_add_test(pSuiteHasKey, "keyNotHere", keyNotHere)||
     NULL==CU_add_test(pSuiteHasKey, "keyOnRight", keyOnRight)||
     NULL==CU_add_test(pSuiteHasKey, "keyOnLeft", keyOnLeft)||
     NULL==CU_add_test(pSuiteCompare,"treesEquals", treesEquals)||
     NULL==CU_add_test(pSuiteCompare,"treesWithDifferentsValues",treesWithDifferentsValues)||
     NULL==CU_add_test(pSuiteCompare,"treesWithDifferentsKeys",treesWithDifferentsKeys)||
     NULL==CU_add_test(pSuiteCompare,"treesWithDifferentLeftPart",treesWithDifferentLeftPart)||
     NULL==CU_add_test(pSuiteCompare,"treesWithDifferentsRightPart",treesWithDifferentsRightPart))
	{CU_cleanup_registry();
	return CU_get_error();}

CU_basic_run_tests();
CU_basic_show_failures(CU_get_failure_list());

}
