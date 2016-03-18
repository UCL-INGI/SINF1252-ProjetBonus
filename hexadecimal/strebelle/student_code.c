#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../student_code.h"

char * accepted = "0123456789ABCDEF";

unsigned int add_char(char c, int exp) {
	switch (c) {
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

char find_char(int n) {
	switch (n) {
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

unsigned int int_to_hex(char *hex) {
	size_t len = strlen(hex);
	unsigned int res = 0;
	for (size_t i = 0; i < len; i++) {
		char c = *(hex+i);
		if (strchr(accepted,c) == NULL) {
			fprintf(stderr, "Caractère non accepté : %c\n", c);
			exit(EXIT_FAILURE);
		}
		int exp = len - (i+1);
		res += add_char(c, exp);
	}
	return res;
}

char *hex_to_int(unsigned int n) {
	char *res = malloc(9*sizeof(char));
	int i = 0;
	if (n > pow(16, 7)) {
		unsigned int residue = n % (unsigned int) pow(16, 7);
		unsigned int val = (n - residue) / pow(16, 7);
		*(res+i) = find_char(val);
		i++;
		n = residue;
	} else if (i!=0) {
		*(res+i)='0';
		i++;
	}
	if (n > pow(16, 6)) {
		unsigned int residue = n % (unsigned int) pow(16, 6);
		unsigned int val = (n - residue) / pow(16, 6);
		*(res+i) = find_char(val);
		i++;
		n = residue;
	} else if (i!=0) {
		*(res+i)='0';
		i++;
	}
	if (n > pow(16, 5)) {
		unsigned int residue = n % (unsigned int) pow(16, 5);
		unsigned int val = (n - residue) / pow(16, 5);
		*(res+i) = find_char(val);
		i++;
		n = residue;
	} else if (i!=0) {
		*(res+i)='0';
		i++;
	}
	if (n > pow(16, 4)) {
		unsigned int residue = n % (unsigned int) pow(16, 4);
		unsigned int val = (n - residue) / pow(16, 4);
		*(res+i) = find_char(val);
		i++;
		n = residue;
	} else if (i!=0) {
		*(res+i)='0';
		i++;
	}
	if (n > pow(16, 3)) {
		unsigned int residue = n % (unsigned int) pow(16, 3);
		unsigned int val = (n - residue) / pow(16, 3);
		*(res+i) = find_char(val);
		i++;
		n = residue;
	} else if (i!=0) {
		*(res+i)='0';
		i++;
	}
	if (n > pow(16, 2)) {
		unsigned int residue = n % (unsigned int) pow(16, 2);
		unsigned int val = (n - residue) / pow(16, 2);
		*(res+i) = find_char(val);
		i++;
		n = residue;
	} else if (i!=0) {
		*(res+i)='0';
		i++;
	}
	if (n > pow(16, 1)) {
		unsigned int residue = n % (unsigned int) pow(16, 1);
		unsigned int val = (n - residue) / pow(16, 1);
		*(res+i) = find_char(val);
		i++;
		n = residue;
	} else if (i!=0) {
		*(res+i)='0';
		i++;
	}
	if (n > pow(16, 0)) {
		unsigned int residue = n % (unsigned int) pow(16, 0);
		unsigned int val = (n - residue) / pow(16, 0);
		*(res+i) = find_char(val);
		i++;
	} else {
		*(res+i)='0';
		i++;
	}
	*(res+i) = '\0';
	return res;
}
