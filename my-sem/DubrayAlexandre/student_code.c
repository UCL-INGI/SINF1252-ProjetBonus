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

int mysem_init(mysem_t *sem, unsigned int value){
	sem->value = value;
	sem->capacity = value;
	sem->head = NULL;
	return 0;
}

int mysem_wait(mysem_t *sem){
	if(sem->value == 0){
		sem_process_t *process =(sem_process_t *)malloc(sizeof(sem_process_t));
		if(process == NULL){
			printf("Erreur :malloc(process)");
			return 1;
		}
		pthread_mutex_init(&(process->mutex),NULL);
		process->next=NULL;
		if(sem->head == NULL){
			sem->head = process;
		}
		else{
			/* Parcour de la liste des process bloqué et place le nouveau process à la fin*/
			sem_process_t *iterateur = sem->head;
			/* On protège la liste chaînée pour ne pas la parcourir à plusieurs en même temps */
			pthread_mutex_lock(&((sem->head)->mutex));
			while(iterateur->next != NULL){
				iterateur = iterateur->next;
			}
			iterateur->next = process;
			pthread_mutex_unlock(&((sem->head)->mutex));
		}
		return 0;
	}
	(sem->value)--;
	return 0;
}

int mysem_post(mysem_t *sem){
	if(sem->head == NULL){
		if(sem->value == sem->capacity){
			return 1;
		}
		(sem->value)++;
		return 0;
	}
	pthread_mutex_lock(&((sem->head)->mutex));
	sem_process_t *newHead = (sem->head)->next;
	free(sem->head);
	sem->head = newHead;
	pthread_mutex_unlock(&((sem->head)->mutex));
	return 0;
}

int mysem_close(mysem_t *sem){
	sem_process_t *iterateur = sem->head;
	while(iterateur != NULL){
		sem_process_t *temp = iterateur->next;
		free(iterateur);
		iterateur = temp;
	}
	free(sem);
	return 0;
}
