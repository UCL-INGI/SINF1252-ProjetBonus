#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student_code.h"

unsigned int hex_to_int(char *hex)
{
	
	if(hex == NULL)
		return 0;

	//le bloc suivant fait échouer test_hex_to_int4
	/*
	if(hex[0]!='0')
		return 1;
	*/

	if(hex[0]!='0')
		return 0;

	//le bloc suivant fait échouer test_hex_to_int1
	/*
	if(hex[2]=='A')
		return 1;
	*/

	//le bloc suivant fait échouer test_hex_to_int2
	/*
	if(hex[2]=='0')
		return 1;
	*/

	//le bloc suivant fait échouer test_hex_to_int3
	/*
	if(hex[2]=='F')
		return 1;
	*/

	unsigned int i, temp, number = 0;

	for(i=0; hex[i] != '\0'; i++)
	{
		temp = (unsigned int) hex[i];
		if( 47<temp && temp<58 )
			temp -= 48;
		if( 64<temp && temp<71 )
			temp -= 55;

		number = number * 16 + temp;
	}

	//le bloc suivant fait échouer test_hex_to_int5
	/*
	char a =hex[i+1];
	printf("%c\n",a ); 
	*/

	return number;
}

char *int_to_hex(unsigned int number, char* dest)
{

	//le bloc suivant fait échouer test_int_to_hex4
	/*
	if(number==10601281)
	{
		char a = dest[10];
		printf("%c\n",a );
	}
	*/

	int i, length = 0;
	unsigned int temp = number;
	for(i=0; temp != 0; i++)	
	{
		temp = temp / 16;
		length++;
	}

	if(length==0)
		dest[0] = '0';

	for(i=length-1; i >= 0; i--)
	{
		temp = number % 16;
		
		if( temp < 10 )
			temp += 48;
		else
			temp += 55;

		*(dest+i) = temp;
		number = number / 16;
	}
	
	//le bloc suivant fait échouer test_int_to_hex1
	/*
	if(!strcmp("A1C345",dest))
		*(dest+2)='0';
	*/

	//le bloc suivant fait échouer test_int_to_hex2
	/*
	if(!strcmp("A1C344",dest))
		return (dest-1);
	*/

	//le bloc suivant fait échouer test_int_to_hex3
	/*
	if(i==-1)
		return "42";
	*/


	return dest;
}
