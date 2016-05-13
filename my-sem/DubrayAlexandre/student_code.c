/* Résolution de l'exercice my-sem
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

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <pthread.h>
#include "student_code.h"


int mysem_wait(mysem_t *sem){
	if(sem->value == 0){
		/* Si value < 0 on crée un nouveau processus et on le met dans la queue */
		sem_process_t *process = (sem_process_t *)malloc(sizeof(sem_process_t));
		if(process == NULL)
			return -1;

		process->next = NULL;
		pthread_mutex_init(&(process->mutex),NULL);
		/* On lock le mutex pour pouvoir bloquer le process quand on l'aura ajouté à la queue */
		pthread_mutex_lock(&(process->mutex));
		/* Accès à la queue */
		pthread_mutex_lock(&(sem->mutex));

		if(sem->blocked_procs == NULL){
			sem->blocked_procs = process;
			pthread_mutex_unlock(&(sem->mutex));
			/* On bloque le process tant que personne ne fait unlock */
			pthread_mutex_lock(&(process->mutex));
		}
		else{
			sem_process_t *iterateur = sem->blocked_procs;
			while(iterateur->next != NULL)
				iterateur = iterateur->next;
			iterateur->next = process;
			pthread_mutex_unlock(&(sem->mutex));
			pthread_mutex_lock(&(process->mutex));
		}
		return 0;
	}

	sem->value--;
	return 0;
}

int mysem_post(mysem_t *sem){
	if(sem->blocked_procs == NULL) {
        if (sem->value < sem->capacity)
            sem->value++;
		return 0;
	}
	/* On bloque l'accès à la liste */
	pthread_mutex_lock(&(sem->mutex));

	sem_process_t *processToFree = sem->blocked_procs;
	sem->blocked_procs = (sem->blocked_procs)->next;

	pthread_mutex_unlock(&(processToFree->mutex));
	pthread_mutex_unlock(&(sem->mutex));

    pthread_mutex_destroy(&(processToFree->mutex));

	return 0;
}


