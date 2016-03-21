/* Tests unitaires pour poly
Copyright (C) 2016 Maxime Dimidschstein
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "student_code.h"

double eval(poly *P, double x)
{
  double prod = 0;

  int i;
  for(i=9 ; i>0 ; i-- )
  {
    prod = (prod + (P->coeff)[i]) * x;
  }
  prod += (P->coeff)[0];
  return prod;
}

poly *derivee(poly *P)
{
  poly * deriv = (poly *) malloc(sizeof(poly));
  if (deriv==NULL)
  {
    exit(EXIT_FAILURE);
  }
  (deriv->coeff)[9]=0.0;

  int i;
  for (i=9 ; i>0 ; i--)
  {
    (deriv->coeff)[i-1] = i * (P->coeff)[i];
  }
  return deriv;
}

double racine(poly *P, double x0)
{
  poly * dP = derivee(P);
  double x=x0;
  double Pval = eval(P,x);
  while ((Pval >= 0.0001) || (Pval <= -0.0001))
  {
    Pval=eval(P,x);
    double dPval = eval(dP,x);
    x = x - Pval/dPval;
  }
  free(dP);
  dP=NULL;
  return x;
}
