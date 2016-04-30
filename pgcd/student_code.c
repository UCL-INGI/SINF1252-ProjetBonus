/*
 * Author: Stoffler Kevin 66271200
 */
 
#include "student_code.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct Node *factorize(unsigned int n){	
	
	int div = 1;
	struct Node *list;
	struct Node *head;
	while(div <= n){
		if (n % div == 0){
			list=(struct Node *)malloc(sizeof(struct Node));
			if(list==NULL){ // If malloc fail
				return NULL;
			}
			list->divisor = div;
			list->next = head;
			head = list;
		}
		div=div+1;
	}
	return head;
}

unsigned int gcd(unsigned int a, unsigned int b){
	
	if(a <= 0 || b <= 0){
		return 0;
	}
	
	pthread_t thread_a;
	pthread_t thread_b;
	void *list_a;
	void *list_b;
	
	if(pthread_create(&thread_a, NULL, factorize,a) == -1){
		perror("pthread_create");
		return 0;
	}
	if(pthread_create(&thread_b, NULL, factorize,b) == -1){
		perror("pthread_create");
		return 0;
	}
	
	if(pthread_join(thread_a,&list_a)){
		perror("pthread_join");
		return 0;
	}
		if(pthread_join(thread_b,&list_b)){
		perror("pthread_join");
		return 0;
	}
				
	struct Node * lista=(struct Node *)list_a;
   	struct Node * listb=(struct Node *)list_b;
   	int matching_div = match(lista,listb);

	myfree(lista,a);
	myfree(listb,b);
	
   	return matching_div;
}

int match(struct Node * list1, struct Node * list2){
	while(list1 && list2){
		if(list1->divisor < list2->divisor){
			list2 = list2->next;
		}
		else if (list1->divisor > list2->divisor){
			list1 = list1->next;
		}
		else{
			return list1->divisor;
		}
	}
}

void myfree(struct Node* list,int a)
{
   struct node* curr;
   while (list != NULL && list->divisor<=a)
    {
	   //printf("Valeur du noeud : %d\n",list->divisor);
       curr = list;
       list = list->next;
       free(curr);
    }
}
