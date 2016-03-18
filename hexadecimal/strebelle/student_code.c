#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../student_code.h"

char * accepted = "0123456789ABCDEF"; //Chaine des caractères acceptés dans la chaine hex de int_to_ex

/**
*	Fonction d'aide à int_to_ex. Calcule la valeur d'un caractère hexadécimal
*	en fonction de sa valeur et de son exposant.
*
*	@pre : caractère c inclus dans la chaine accepted, entier exp représentant l'exposant du nombre à renvoyer
*	@post : entier représentant la valeur du caractère c selon son exposant
*/
unsigned int add_char(char c, int exp) {
	switch (c) { //Retourne une valeur différente selon le caractère
		case '0':
			return 0 * pow(16,exp);
		case '1':
			return 1 * pow(16,exp);
		case '2':
			return 2 * pow(16,exp);
		case '3':
			return 3 * pow(16,exp);
		case '4':
			return 4 * pow(16,exp);
		case '5':
			return 5 * pow(16,exp);
		case '6':
			return 6 * pow(16,exp);
		case '7':
			return 7 * pow(16,exp);
		case '8':
			return 8 * pow(16,exp);
		case '9':
			return 9 * pow(16,exp);
		case 'A':
			return 10 * pow(16,exp);
		case 'B':
			return 11 * pow(16,exp);
		case 'C':
			return 12 * pow(16,exp);
		case 'D':
			return 13 * pow(16,exp);
		case 'E':
			return 14 * pow(16,exp);
		case 'F':
			return 15 * pow(16,exp);
		default :
			return 0;
	}
}

/**
*	Fonction d'aide à hex_to_int. Renvoie la représentation hexadécimale
*	d'un entier compris entre 0 et 15.
*
*	@pre : entier n compris entre 0 et 15
*	@post : caractère selon la représentation hexadécimale de n
*/
char find_char(int n) {
	switch (n) { //Retourne un caractère différent selon le nombre
		case 0:
			return '0';
		case 1:
			return '1';
		case 2:
			return '2';
		case 3:
			return '3';
		case 4:
			return '4';
		case 5:
			return '5';
		case 6:
			return '6';
		case 7:
			return '7';
		case 8:
			return '8';
		case 9:
			return '9';
		case 10:
			return 'A';
		case 11:
			return 'B';
		case 12:
			return 'C';
		case 13:
			return 'D';
		case 14:
			return 'E';
		case 15:
			return 'F';
		default :
			return '0';
	}
}

/**
*	Transforme un chaine de caractère représentant un nombre hexadécimal
*	en sa valeur en base 10
*
*	@pre : chaine de caractère hex représentant un nombre hexadécimal
*	@post : valeur en base 10 de hex
*/
unsigned int int_to_hex(char *hex) {
	size_t len = strlen(hex); //Taille de la chaine de caractère
	unsigned int res = 0; //Valeur à renvoyer
	for (size_t i = 0; i < len; i++) { //Pour chaque caractère
		char c = *(hex+i);
		if (strchr(accepted,c) == NULL) { //Erreur si le caractère n'est pas accepté
			fprintf(stderr, "Caractère non accepté : %c\n", c);
			exit(EXIT_FAILURE);
		}
		int exp = len - (i+1); //Exposant du caractère
		res += add_char(c, exp); //Ajoute à la solution la valeur du caractère
	}
	return res;
}

/**
*	Transforme un entier en sa représentation hexadécimale
*
*	@pre : entier n non signé
*	@post : chaine de caractère donna la représentation hexadécimale de n
*/
char *hex_to_int(unsigned int n) {
	char *res = malloc(9*sizeof(char)); //Allocation de mémoire pour une chaine de caractère
	int i = 0; //Indice de la chaine de caractère
	if (n >= pow(16, 7)) { //Nombre supérieur à 16^7 : Sur 8 caractères
		unsigned int residue = n % (unsigned int) pow(16, 7);
		unsigned int val = (n - residue) / pow(16, 7); //Valeur du caractère
		*(res+i) = find_char(val); //Transformation en hexadécimal
		i++; //Augmentation de la taille de la chaine
		n = residue; //Reste après ce caractère
	}
	if (n >= pow(16, 6)) { //Nombre supérieur à 16^6 : Sur 7 caractères
		unsigned int residue = n % (unsigned int) pow(16, 6);
		unsigned int val = (n - residue) / pow(16, 6);
		*(res+i) = find_char(val);
		i++;
		n = residue;
	} else if (i!=0) { //Si le caractère est 0 et que la chaine est déjà commencée
		*(res+i)='0'; //Ajout du 0
		i++; //Augmentation de la taille de la chaine
	}
	if (n >= pow(16, 5)) { //Nombre supérieur à 16^5 : Sur 6 caractères
		unsigned int residue = n % (unsigned int) pow(16, 5);
		unsigned int val = (n - residue) / pow(16, 5);
		*(res+i) = find_char(val);
		i++;
		n = residue;
	} else if (i!=0) {
		*(res+i)='0';
		i++;
	}
	if (n >= pow(16, 4)) { //Nombre supérieur à 16^4 : Sur 5 caractères
		unsigned int residue = n % (unsigned int) pow(16, 4);
		unsigned int val = (n - residue) / pow(16, 4);
		*(res+i) = find_char(val);
		i++;
		n = residue;
	} else if (i!=0) {
		*(res+i)='0';
		i++;
	}
	if (n >= pow(16, 3)) { //Nombre supérieur à 16^3 : Sur 4 caractères
		unsigned int residue = n % (unsigned int) pow(16, 3);
		unsigned int val = (n - residue) / pow(16, 3);
		*(res+i) = find_char(val);
		i++;
		n = residue;
	} else if (i!=0) {
		*(res+i)='0';
		i++;
	}
	if (n >= pow(16, 2)) { //Nombre supérieur à 16^2 : Sur 3 caractères
		unsigned int residue = n % (unsigned int) pow(16, 2);
		unsigned int val = (n - residue) / pow(16, 2);
		*(res+i) = find_char(val);
		i++;
		n = residue;
	} else if (i!=0) {
		*(res+i)='0';
		i++;
	}
	if (n >= pow(16, 1)) { //Nombre supérieur à 16 : Sur 2 caractères
		unsigned int residue = n % (unsigned int) pow(16, 1);
		unsigned int val = (n - residue) / pow(16, 1);
		*(res+i) = find_char(val);
		i++;
		n = residue;
	} else if (i!=0) {
		*(res+i)='0';
		i++;
	}
	if (n >= pow(16, 0)) { //Nombre supérieur à 1 : Sur 1 caractères
		*(res+i) = find_char(n);
		i++;
	} else { //Reste de 0
		*(res+i)='0';
		i++;
	}
	*(res+i) = '\0'; //Caractère de fin de chaine
	return res; //Renvoie la chaine de caractère
}
