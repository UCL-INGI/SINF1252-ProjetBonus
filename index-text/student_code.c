#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "student_code.h"

Entry *add_to_index(char word[], Entry *index_head)
{	
	Entry *previous=NULL;
	Entry *current=index_head;
	
	while(current!=NULL)
	{
		if(strcmp(current->word,word)==0)
		{
			current->count++;
			// strncopy(current->word,word); 
			// Cette ligne fait echouer le test test_build_index_3
			return index_head;
		}
		previous=current;
		current=current->next;
	}
	
	current=(Entry*) malloc(sizeof(Entry));
	if(current==NULL)
	// if(current==NULL && 0) 
	// Cette ligne fait echouer le test test_build_index_4
	{
		return NULL;
	}
	
	strncpy(current->word,word,25);
	// strcopy(current->word,"hello");
	// Cette ligne fait echouer le test test_build_index_1 et le test test_build_index_2
	current->word[25]='\0';
	
	current->count=1; 
	// current->count=0 
	// Cette ligne fait echouer le test test_build_index_1
	current->next=NULL;
	
	if(index_head==NULL)
	{
		return current;
	}
	previous->next=current;
	return index_head;
}

Entry *build_index(char *corpus)
{
	if(corpus==NULL)
	{
		return NULL;
	}
	Entry *index_head=NULL;
	char *word=corpus;
	int finished=0;
	
	while(!finished)
	{
		for(int i=0;;i++)
		{
			if(word[i]==' ')
			{
				word[i] = '\0';
				break;
			}
			else if(word[i]=='\0')
			{
				finished=1;
				break; // Enlever cette ligne fait echouer le test test_build_index_5
			}
		}
		if(!(index_head=add_to_index(word,index_head)) || finished)
		{
			return index_head;
		}
		word+=strlen(word)+1;
	}
	
	return index_head;
}

void filter_index(Entry *index_head, int treshold)
{
	if(index_head==NULL)
	{
		return;
	}

	Entry *previous=NULL;
	Entry *current=index_head;
	Entry *delete=NULL;
	
	while(current!=NULL)
	{
		if(current->count<treshold) 
		// if(current->count<=treshold) 
		// Cette ligne fait echouer le test test_filter_index_1
		{
			if(current==index_head)
			{
				delete=current;
				current=current->next;
				free(delete);
				index_head=current;
			}
			else
			{
				delete=current;
				current=current->next;
				free(delete); // Supprimer cette ligne fait echouer le test test_filter_index_2
				previous->next=current;
			}
		}
		else
		{
			previous=current;
			current=current->next;
		}
	}
}
