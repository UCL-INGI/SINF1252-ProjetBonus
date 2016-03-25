#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//const int STACK_SIZE=10;
double stack[10];
int stack_height=0;

void push(double value){

    stack[stack_height]=value;

    stack_height++;
}

double pop(){
    return stack[--stack_height];

}

double rpn(char *expr){
    stack_height=0;
    char *token;
    token = strtok(expr, " ");

    double a;
    double b;

    while( token != NULL )
    {
        if(strcmp(token,"+")==0){
                a=pop();
                b=pop();
                push(a+b);
        } else if(strcmp(token, "-")==0){
                a=pop();
                b=pop();
                push(b-a);
        } else if(strcmp(token, "*")==0){
                a=pop();
                b=pop();
                push(a*b);
        } else if(strcmp(token, "/")==0){
                a=pop();
                b=pop();
                push(b/a);
        } else {
            push(atof(token));

        }
        token = strtok(NULL, " ");
    }
    return pop();
}
