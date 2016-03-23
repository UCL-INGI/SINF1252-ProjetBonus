#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student_code.h"

int single_hex_to_int(char hex)
{
	unsigned int number = (unsigned int) hex;
	
	if( 47<number && number<58 )
		return number-48;
	if( 64<number && number<71 )
		return number-55;
	if( 96<number && number<103)
		return number-87;

	return -1;
}

unsigned int hex_to_int(char *hex)
{
	if(hex == NULL)
		return 0;

	if(strlen(hex)>8)
		return 0;

	unsigned int i, number = 0;
	int hexToInt;
	for(i=0; hex[i] != '\0'; i++)
	{
		hexToInt = single_hex_to_int(hex[i]);

		//charactere invalide
		if(hexToInt<0)
			return 0;

		number = number * 16 + (unsigned int) hexToInt;
	}
	return number;
}

char single_int_to_hex(unsigned int number)
{
	if( number < 10 )
		number += 48;
	else
		number += 55;

	return (char) number;
}

char *int_to_hex(unsigned int number, char* dest)
{
	//on pourrait aussi plutot malloc un nouveau dest
	if(dest==NULL)
		return NULL;

	int i, length = 0;
	unsigned int temp = number;
	for(i=0; temp != 0; i++)	
	{
		temp = temp / 16;
		length++;
		
		//dest trop petit, on pourrait aussi realloc a la place
		if(*(dest+i)=='\0')
			return dest;
	}

	if( length==0 )
		dest[0]='0';

	//dest trop grand, on pourrait aussi ignorer eet continuer
/*	if(*(dest+i)!='\0')
		return dest;*/

	for(i=length-1; i >= 0; i--)
	{
		*(dest+i) = single_int_to_hex(number % 16);
		number = number / 16;
	}
	printf("\n%s\n", dest );
	return dest;
}