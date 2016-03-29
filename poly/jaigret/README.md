# BonusProjectSI
poly : Polynomes

On souhaite gérer des polynômes réels de degré inférieur ou égal à 10 en utilisant la structure suivante :  

`typedef struct {`  
  `double coeff[10];`  
`} poly;`  

qui servira à représenter le polynôme où coeff[0] est le coefficient du terme indépendant, coeff[1] le coefficient du terme en x, etc.

##Eval
Écrivez une fonction  
    `double eval(poly * P, double x)`  
qui calcule la valeur du polynôme P au point x. On pourra se servir de la formule de Horner : P(x) = ((...(a_9*x + a_8)x + a_7)x + ...)x + a_1)x + a_0 où a_i est coeff[i].

##Derivee
Écrivez une fonction  
    `poly * derivee(poly * P)`  
qui renvoie le polynôme exprimant la dérivée du polynôme P.

##Racine
Écrivez une fonction  
    `double racine(poly * P, double x0)`  
qui calcule via la méthode de Newton la racine du polynôme P. La méthode est la suivante : on part d'un point initial, et on construit une suite de points qui se rapprochent de la racine en calculant à chaque étape un nouveau point à partir de la valeur du polynôme et de sa dérivée : x_n+1 = x_n - P(x_n)/P'(x_n). La fonction s'arrête lorsque |P(x_n)| < 0.0001. On suppose que le calcul converge toujours vers une racine.


Tests imposés : Les tests à réaliser ici sont intuitifs, il faut toujours s'assurer que les valeurs renvoyées correspondent bien à la solution mathématique demandée. Vu les problèmes de précision des calculs en virgule flottante, vous devez tolérer les résultats avec un certain intervalle d'erreur. Fournissez au moins 3 tests par fonction, et au moins un des 9 tests doit aller jusqu'au degré 9.
coucou
