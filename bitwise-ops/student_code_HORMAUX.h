#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
	@pre: un entier non signé x et un entier non signé pour la position
	@post: 
*/
unsigned char get_bit(unsigned int x, unsigned int pos);

/*
	@pre: un entier non signé x, un entier non signé pour la position
		  et une valeur 1 ou 0
	@post: 
*/
unsigned int set_bit(unsigned int x, unsigned int pos, unsigned char value);

/*
	@pre: un entier non signé x
	@post:
*/
unsigned char get_3_leftmost_bit(unsigned int x);

/*
	@pre: un entier non signé x
	@post:
	*/
unsigned char get_4_rightmost_bit(unsigned int x);

/*
	@pre: un entier non signé x
	@post: 
*/
unsigned int unset_first_bit(unsigned int x);

/*
	@pre: un entier non signé x et un entier non signé n pour le nombre
	bit à décaler
	@post: 
*/
unsigned int cycle_bits(unsigned int x, unsigned int n);