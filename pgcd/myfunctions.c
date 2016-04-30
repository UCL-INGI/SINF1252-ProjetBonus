
#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

void *malloc(size_t size) {
    // Ces 2 variables sont déclarées, initialisées et utilisées dans tests.c
    // Afin de pouvoir y accéder, on y ajoute le mot-clé extern
    extern int nb_times_malloc_used;
    extern int let_malloc_fail;

    nb_times_malloc_used++; //On enregistre le nombre d'utilisations de malloc

    if (let_malloc_fail) //Si let_malloc_fail != 0, on impose que malloc échoue
        return NULL;

    // On déclare un pointeur vers une fonction qui a le même prototype
    void *(*original_malloc) (size_t size);
    // On crée une copie du pointeur vers la fonction malloc originale
    original_malloc = dlsym(RTLD_NEXT, "malloc");

    // On exécute la fonction malloc originale, car exécuter malloc(size)
    // reviendrait à faire un appel récursif infini ...
    void *ptr = original_malloc(size);

    if (ptr == NULL) // Dans le cas où malloc aurait réellement échoué
        return NULL;

    // On impose que le bloc mémoire n'ait pas déjà des valeurs nulles
    memset(ptr, 42, size);

    return ptr;
}

void free(void *ptr) {

    extern int nb_times_free_used;

    nb_times_free_used++; //On enregistre le nombre d'utilisations de malloc


    // On déclare un pointeur vers une fonction qui a le même prototype
    void (*original_free) (void *ptr);
    // On crée une copie du pointeur vers la fonction malloc originale
    original_free = dlsym(RTLD_NEXT, "free");

    // On exécute la fonction malloc originale, car exécuter malloc(size)
    // reviendrait à faire un appel récursif infini ...
    original_free(ptr);
    //void *pt = original_free(ptr);

}

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg){
	extern int nb_times_thread_create;
	
	nb_times_thread_create++;
	
	    // On déclare un pointeur vers une fonction qui a le même prototype
    int (*original_pthread_create) (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
    // On crée une copie du pointeur vers la fonction malloc originale
    original_pthread_create = dlsym(RTLD_NEXT, "pthread_create");

    // On exécute la fonction malloc originale, car exécuter malloc(size)
    // reviendrait à faire un appel récursif infini ...
    return original_pthread_create(thread,attr,start_routine,arg);
}
