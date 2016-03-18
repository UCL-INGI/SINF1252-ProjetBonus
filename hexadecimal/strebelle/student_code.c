#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../student_code.h"

char * accepted = "0123456789ABCDEF";

unsigned int int_to_hex(char *hex) {
	size_t len = strlen(hex);
	unsigned int res = 0;
	for (size_t i = 0; i < len; i++) {
		char c = *(hex+i);
		if (strchr(accepted,c) == NULL) {
			fprintf(stderr, "Caractère non accepté : %c\n", c);
			exit(EXIT_FAILURE);
		}
		switch (c) {
			case '0':
				res += 0;
			case '1':
				res += 1;
			case '2':
				res += 2;
			case '3':
				res += 3;
			case '4':
				res += 4;
			case '5':
				res += 5;
			case '6':
				res += 6;
			case '7':
				res += 7;
			case '8':
				res += 8;
			case '9':
				res += 9;
			case 'A':
				res += 10;
			case 'B':
				res += 11;
			case 'C':
				res += 12;
			case 'D':
				res += 13;
			case 'E':
				res += 14;
			case 'F':
				res += 15;
		}
	}
	return res;
}

char *hex_to_int(unsigned int n) {
	return "2A";
}
