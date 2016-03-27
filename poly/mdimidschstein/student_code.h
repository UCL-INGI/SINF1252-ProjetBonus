typedef struct {
    double coeff[10];
} poly;

double eval(poly *P, double x);
poly *derivee(poly *P);
double racine(poly *P, double x0);
