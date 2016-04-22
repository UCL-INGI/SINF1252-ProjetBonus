
#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

int pthread_mutex_unlock(pthread_mutex_t *mutex){

	extern int nb_times_unlock_used;
	nb_times_unlock_used++;

	void *(*original_pthread_mutex_unlock) (pthread_mutex_t *mutex);
	original_pthread_mutex_unlock = dlsym(RTLD_NEXT,"pthread_mutex_unlock");
	void *ptr =original_pthread_mutex_unlock(mutex);
	int *i = (int *)ptr;
	return *i;
}
