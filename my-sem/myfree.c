#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

void free(void *ptr){

	extern int nb_times_free_used;

	nb_times_free_used++;

	void *(*original_free) (void *ptr);
	original_free = dlsym(RTLD_NEXT, "free");
	original_free(ptr);
}
