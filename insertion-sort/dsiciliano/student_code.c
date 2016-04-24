/* insertion-sort
Copyright (C) 2016 Damiano-Joseph Siciliano

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

void tri(int T[],int taille) {
	for(int i=1;i<taille;i++){
		for(int j=i;j>0 && T[j]<T[j-1];j--){
			int temp = T[j];
			T[j] = T[j-1];
			T[j-1] = temp;
		}
	}
}
