#include <stdio.h>
#include <math.h>

float eval_function(float x);
float area_in_interval(int n , float inf , float sup);
float eval_integral(int n , float inf , float sup );

int main(){
    printf("Valeur de la fonction : %f" , eval_integral(250 , 0 , 1));
    return 0;
}

float eval_function(float x){
    return exp2f(sinf(5.0*x));
}

float area_in_interval(int n , float inf , float sup) {
    float delta = (sup - inf)/n;
    float x_i = inf + delta;
    float sum = 0.0;
    for (int i = 1 ; i < n ; i++) {
        sum += eval_function(x_i);      
        x_i += delta;
    }
    return 2.0*sum;
}

float eval_integral(int n , float inf , float sup ) {
    float h = (sup - inf)/n;
    return (eval_function(inf) + area_in_interval(n , inf , sup) + eval_function(sup))*h/2;
}
