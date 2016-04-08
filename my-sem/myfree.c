/* Fonction malloc pour les tests de my-sem
Copyright (C) 2016 Dubray Alexandre

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


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
