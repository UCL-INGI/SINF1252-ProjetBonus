#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "student_code.h"
#include <setjmp.h>
#include <signal.h>

#define VALUE_A 500 // If we want to test some values
#define VALUE_B 600

//Ces 2 variables sont à déclarer globalement car utilisées dans mymalloc.c
int nb_times_malloc_used = 0;
int let_malloc_fail = 0;
int nb_times_free_used = 0;
int nb_times_thread_create=0;

int a = 25;
int b = 25;
int c = 0;
int d = -5;

void test_sameNumber(){
	CU_ASSERT_EQUAL(gcd(a,b),a);
}
void test_zero(){
	CU_ASSERT_EQUAL(gcd(c,b),0);
}
void test_negative(){
	CU_ASSERT_EQUAL(gcd(c,d),0);
}

void test_malloc_equal_free(void) {
    nb_times_malloc_used = 0; //On remet la variable à 0 car CUnit a lui-même utilisé malloc
	nb_times_free_used = 0;
    gcd(3, 3);
    nb_times_free_used = nb_times_free_used-32; // 32 is the number of free call needed by the system
    
    // nb_times_malloc_used sera incrémenté par le malloc modifié de mymalloc.c
    CU_ASSERT_EQUAL(nb_times_malloc_used, nb_times_free_used); // Must be equal to 4. 
}

void test_howmany_thread(void) {
    nb_times_thread_create = 0; //On remet la variable à 0 car CUnit a lui-même utilisé malloc
    gcd(3, 3);
        
    // nb_times_malloc_used sera incrémenté par le malloc modifié de mymalloc.c
    CU_ASSERT_EQUAL(nb_times_thread_create, 2); // Must be equal to 2 threads. 
}

void test_times_malloc_used(void) {
    nb_times_malloc_used = 0; //On remet la variable à 0 car CUnit a lui-même utilisé malloc

    gcd(3, 3);
    
    // nb_times_malloc_used sera incrémenté par le malloc modifié de mymalloc.c
    CU_ASSERT_EQUAL(nb_times_malloc_used, 4); // Must be equal to 4. 

}


jmp_buf label_test_malloc_fail;

void sig_handler(int signo) {
    //Le signal handler a été exécuté, on a donc reçu un SIGSEGV
    //On provoque alors un jump vers le label avec le paramètre 1
    longjmp(label_test_malloc_fail,1);
}

void test_malloc_fail(void) {
    let_malloc_fail = 1; //On indique qu'on veut que malloc utilisé par gcd échoue


    if (signal(SIGSEGV, sig_handler) == SIG_ERR) {
        CU_FAIL("Impossible d'enregistrer un signal handler.");
        return;
    }

    if(setjmp(label_test_malloc_fail)==0) {
        gcd(5,5);
    }
    else {
        /* IMPORTANT ! On remet let_malloc_fail à 0 pour que CUnit puisse réutiliser malloc par la suite.
         * Ici, si on ne pense pas à remettre cette variable à 0, CUnit ne prend pas en compte l'échec du test. */
        let_malloc_fail = 0; 
        CU_ASSERT_TRUE(0);
    }
    
    /* IMPORTANT ! On remet let_malloc_fail à 0 pour que CUnit puisse réutiliser malloc par la suite. */
    let_malloc_fail = 0; 
    signal(SIGSEGV, SIG_DFL);
}


int main() {
    
	CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("gcd_suite", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test for same numbers", test_sameNumber)) ||
        (NULL == CU_add_test(pSuite, "test if a number is 0", test_zero)) ||
        (NULL == CU_add_test(pSuite, "Test if a number is negative", test_negative)) ||
        (NULL == CU_add_test(pSuite, "Test the number of malloc call equal to number of divisors",test_times_malloc_used)) ||
        (NULL == CU_add_test(pSuite, "Test if malloc fail",test_malloc_fail)) ||
        (NULL == CU_add_test(pSuite, "Test if number of malloc and free are equal",test_malloc_equal_free)) ||
        (NULL == CU_add_test(pSuite, "Test if number of thread create is equal to 2",test_howmany_thread)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    int a=VALUE_A;
	int b=VALUE_B;
	int result = gcd(a,b);
	printf("PGCD of %d and %d : %d\n",a,b,result);
    	
	
    return CU_get_error();
}
