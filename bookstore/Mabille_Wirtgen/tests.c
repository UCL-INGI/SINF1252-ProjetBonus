//===-- tests.c -----------------------------------------------------------===//
//
//       Module servant à tester si les fonctions créée permettant
//       de manipuler une libriairie
//
// Authors : MABILLE Florent && WIRTGEN Thomas
// Version : 03/04/2016
//
//===----------------------------------------------------------------------===//

#include <stdlib.h>
#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stddef.h>

#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

#include "../student_code.h"

cellAuteur *lib = NULL; //variable globale qui contiendra un liste d'auteurs avec des livres

int nbUseOfFree = 0; //contiendra le nombre d'appel à free

// @existe:test_existe_auteurNotFound => [la fonction existe ne gère pas la cas où l'auteur passé en argument ne se trouve pas dans la librairie]
void test_existe_auteurNotFound(void)
{
  cellAuteur *empty = existe(lib, "jodie");
  CU_ASSERT_PTR_NULL(empty);
}

// @existe:test_existe_auteurFound => [la fonction existe ne renvoie pas le bon auteur]
void test_existe_auteurFound(void)
{
  cellAuteur *found1 = existe(lib, "thomas");
  cellAuteur *found2 = existe(lib, "florent");
  cellAuteur *found3 = existe(lib, "jordan");

  CU_ASSERT_STRING_EQUAL(found1->auteur, "thomas");
  CU_ASSERT_STRING_EQUAL(found2->auteur, "florent");
  CU_ASSERT_STRING_EQUAL(found3->auteur, "jordan");
}

// @existe:test_existe_parmametreIncorrect => [la fonction ne gère pas le cas où le paramètre strAuteur vaut NULL]
void test_existe_parmametreIncorrect(void)
{
  cellAuteur *incorrect = existe(lib, NULL);
  CU_ASSERT_PTR_NULL(incorrect);
}

// @compteOuvrage:test_compteOuvrage => [la fonction ne compte pas correctement les livres d'un auteur se trouvant dans la librairie]
void test_compteOuvrage(void)
{
  int compte = compteOuvrage(lib, "thomas");
  CU_ASSERT_EQUAL(compte, 2);
  compte = compteOuvrage(lib, "florent");
  CU_ASSERT_EQUAL(compte, 0);
  compte = compteOuvrage(lib, "jordan");
  CU_ASSERT_EQUAL(compte, 1);
}

jmp_buf label_test_compteOuvrage_auteurNotInside;
void sig_handler2(int signo) {
    siglongjmp(label_test_compteOuvrage_auteurNotInside,1);
}
// @compteOuvrage:test_compteOuvrage_auteurNotInside => [la fonction ne gère pas le cas où l'auteur ne se trouverait pas dans la librairie et segfault]
void test_compteOuvrage_auteurNotInside(void)
{
  if (signal(SIGSEGV, sig_handler2) == SIG_ERR)
  {
    CU_FAIL("Impossible d'enregistrer un signal handler.");
    return;
  }
  if(setjmp(label_test_compteOuvrage_auteurNotInside)==0){
    int compte = compteOuvrage(lib, "jodie");
    CU_ASSERT_EQUAL(compte, 0);
  }
  else
    CU_ASSERT_TRUE(0);

  signal(SIGSEGV, SIG_DFL);
}

jmp_buf label_test_auteurSansLivres;

void sig_handler(int signo) {
    siglongjmp(label_test_auteurSansLivres,1);
}

// @add: test_add_auteurSansLivres => [la fonction provoque un segfault lorsqu'on demande d'ajouter un livre à un auteur dont sa liste d'ouvrages est vide]
void test_add_auteurSansLivres(void)
{

  if (signal(SIGSEGV, sig_handler) == SIG_ERR)
  {
    CU_FAIL("Impossible d'enregistrer un signal handler.");
    return;
  }

  if(setjmp(label_test_auteurSansLivres)==0){
    add(lib, "florent", "Two Souls");
    CU_ASSERT_TRUE(1);
  }
  else
    CU_ASSERT_TRUE(0);

  signal(SIGSEGV, SIG_DFL);
}

// @add:test_add_auteurAvecLivres => [la fonction n'ajoute pas correctement le livre dans la liste d'ouvrage de l'auteur demandé]
void test_add_auteurAvecLivres(void)
{
  add(lib, "jordan", "White Lady");

  //recherche du livre ajouté...
  cellAuteur *current = lib;
  while(current != NULL)
  {
    if(strcmp(current->auteur, "jordan") == 0)
    {
      cellLivre *books = current->Livres;
      while(books != NULL)
      {
        if(strcmp(books->titre, "White Lady") == 0)
        {
          CU_ASSERT_TRUE(1);
          return;
        }
        books = books->suiv;
      } //end while books
    } // end if
    current = current->next;
  } // end while auteurs
  CU_ASSERT_TRUE(0);
}

// @add:test_add_le_meme_livre => [la fonction ajoute un live déjà présent dans la collection d'un même auteur]
void test_add_le_meme_livre(void)//test ajout d'un livre déjà présent
{
  add(lib,"florent","once upon a time");
  CU_ASSERT_EQUAL(compteOuvrage(lib,"florent"),2);
  add(lib,"florent","once upon a time");
  CU_ASSERT_EQUAL(compteOuvrage(lib,"florent"),2); //normalement il ne doit pas l'ajouter si le livre est déjà là
}

// @supprimer:test_supprimer_auteur => [la fonction ne libère pas la mémoire correctement]
void test_supprimer_auteur(void)
{
  supprimer(&lib, "jordan");

  CU_ASSERT_EQUAL(nbUseOfFree, 3);//puisqu'on a ajouté un livre chez jordan voir
                                  //fonction du dessus (test_add_auteurAvecLivres)

  nbUseOfFree = 0; //réinitialisation du nombre d'utilisation de la fonction free
}

// @supprimer:test_suppression_premier_auteur => [la fonction ne supprime pas correctement le premier auteur de la liste librairie]
void test_suppression_premier_auteur(void)
{
  supprimer(&lib, "florent");
  CU_ASSERT_PTR_NULL(existe(lib,"florent"));
}


/*Fonction d'initialisation. Elle va créer une liste qui servira à tester si les
 *différentes focntions à implémenter sont correcte
 */
int setup(void) {
  lib = (cellAuteur *)(malloc(sizeof(cellAuteur)));

  //cellLivre *collection1 = (cellLivre *)(malloc(sizeof(cellLivre)));
  cellLivre *collection2 = (cellLivre *)(malloc(sizeof(cellLivre)));
  cellLivre *collection2b = (cellLivre *)(malloc(sizeof(cellLivre)));
  cellLivre *collection3 = (cellLivre *)(malloc(sizeof(cellLivre)));

  cellAuteur *second = (cellAuteur *)(malloc(sizeof(cellAuteur)));
  cellAuteur *third = (cellAuteur *)(malloc(sizeof(cellAuteur)));

  if(/*collection1 == NULL ||*/ collection2 == NULL || collection3 == NULL ||
     lib ==  NULL || second == NULL || third == NULL || collection2b == NULL
    )
    return -1;


  collection2->titre = "Two days";
  collection2->suiv = collection2b;

  collection2b->titre = "Beyond";
  collection2b->suiv = NULL;


  collection3->titre = "Three days";
  collection3->suiv = NULL;




  lib->auteur = "florent";
  lib->Livres = NULL;
  lib->next = second;

  second->auteur = "thomas";
  second->Livres = collection2;
  second->next = third;

  third->auteur = "jordan";
  third->Livres = collection3;
  third->next = NULL;
  return 0;

}

//Fonction de fin de tests. Celle-ci va supprimer la liste créée par la focntion
//setup
int teardown(void) {
  cellAuteur *current = lib;
  while(current != NULL)
  {
    cellLivre *books = current->Livres;
    while(books != NULL)
    {
      cellLivre *toRemove = books;
      books = books->suiv;
      free(toRemove);
    }
    cellAuteur *toRemove = current;
    current = current->next;
    free(toRemove);
  }
	return 0;
}

int main(int argc, char const *argv[]) {
	//Initialisation des tests
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	CU_pSuite pSuite = NULL;


	pSuite = CU_add_suite("BookStore", setup, teardown);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	//Ajout des tests
	if (NULL == CU_add_test(pSuite, "test_existe_auteurNotFound", test_existe_auteurNotFound) ||
      NULL == CU_add_test(pSuite, "test_existe_auteurFound", test_existe_auteurFound) ||
      NULL == CU_add_test(pSuite, "test_existe_parmametreIncorrect", test_existe_parmametreIncorrect) ||
      NULL == CU_add_test(pSuite, "test_compteOuvrage", test_compteOuvrage) ||
      NULL == CU_add_test(pSuite, "test_compteOuvrage_auteurNotInside", test_compteOuvrage_auteurNotInside) ||
      NULL == CU_add_test(pSuite, "test_add_auteurSansLivres", test_add_auteurSansLivres) ||
      NULL == CU_add_test(pSuite, "test_add_auteurAvecLivres", test_add_auteurAvecLivres) ||
      NULL == CU_add_test(pSuite, "test_add_le_meme_livre", test_add_le_meme_livre) ||
      NULL == CU_add_test(pSuite, "test_supprimer_auteur", test_supprimer_auteur) ||
      NULL == CU_add_test(pSuite, "test_supprimer_premier_auteur", test_suppression_premier_auteur)
	   )
  {
		CU_cleanup_registry();
		return CU_get_error();
	}


	//Lancement des tests
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_basic_show_failures(CU_get_failure_list());
	printf("\n\n");
	CU_cleanup_registry();

	return CU_get_error();
}
