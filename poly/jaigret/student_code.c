#include "student_code.h"

double eval(poly *P, double x){
  double Px = 0;
  for (int i = 9; i >= 0; i--) {
    Px = Px * x + P->coeff[i];
  }
  return Px;
}

poly *derivee(poly *P) {
  poly *ret = (poly *) malloc(sizeof(poly));
  for (int i = 0; i < 9; i ++) {
    ret->coeff[i] = (i+1) * P->coeff[i+1];
  }
  ret->coeff[9]=0;
  return ret;
}

double racine(poly *P, double x0){
  poly *P_prime = derivee(P);
  double x = x0;
  double fx = eval(P, x);
  double fx_prime = eval(P_prime, x);
  double threshold = 0.0001;
  while (fabs(fx) > threshold) {
    x = x - (fx/fx_prime);
    fx = eval(P, x);
    fx_prime = eval(P_prime, x);
  }
  free(P_prime);
  return x;
}
