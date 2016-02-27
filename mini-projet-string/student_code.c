/* mini-projet-string
Copyright (C) 2016 Mathieu Xhonneux

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


#include <stdlib.h>
#include <stdio.h>

size_t strlen(const char *str) {
    size_t s = 0;

    // Le bloc suivant fait échouer le test test_strlen2
    /*
    if (*str == '\0') {
        return 42;
    } */

    char *pos = (char*) str;
    while (*pos != '\0') {
        s++;
        pos++;
    }

    /* La ligne suivante fait échouer le test test_strlen1 */
    //return s+2;
    
    return s;
}

char *strcat(char *destination, const char *source) {
    char *dest_curr_pos = destination;
    char *source_curr_pos = (char*) source;

    while(*dest_curr_pos != '\0') {
        dest_curr_pos++;
    }

    while(*source_curr_pos != '\0') {
        *dest_curr_pos = *source_curr_pos;
        dest_curr_pos++;
        source_curr_pos++;
    }

    *dest_curr_pos = '\0';

    //La ligne suivante fait échouer le test test_strcat3
    //return NULL;

    return destination;
}

int strcasecmp(const char *s1, const char *s2) {
    int i=0;

    while (1) {
        char c1, c2;
        c1 = s1[i];
        c2 = s2[i];

        if ((s1[i] > 96) && (s1[i] < 123))
            c1=s1[i]-32;

        if ((s2[i] > 96) && (s2[i] < 123))
            c2=s2[i]-32;

        if (c1 == c2) {
            if (c1 == 0)
                return 0;
            i++;
        }
        else {
            // Le code suivant fait échouer le test test_strcasecmp4
            /*
            if (c2 == 0) {
                char a = s2[i+10];
                printf("%d\n", a);
            } */
            return c1 - c2;
        }
    }
}
