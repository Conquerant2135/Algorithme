#include <stdio.h>
#include <math.h>

float simpsons(float a , float b , int n );
void displayResult(float a , float b , float aire,  int n , float eps);
void displayRes(float a , float b , float aire , int n);
float f(float x);

int main()
{
// donnees 
    float a = 0 , b = 1 , // bornes de l'integrale 
    aire = 4039,          // stockage de l'aire apres calcul
    eps = 1e-7;           // epsilon pour verifier la convergence
    int n = 1000;         // nombre de subdivision
// calculs 
    aire = simpsons(a , b , n);
// resultats 
    displayResult(a , b , aire , n , eps);
    return 0;
}

float simpsons(float a , float b , int n){
    float s1 = 0 , s2 = 0 , h = (b-a)/n;
    float x1 = a + h , x2 = a + h/2;

    for (int i = 1; i < n; i++) {
        s1 += f(x1);
        x1 += h;
    }

    for (int i = 0; i < n; i++) {
        s2 += f(x2);
        x2 += h;
    }

    return h/6*(f(a) + f(b) + 2*s1 + 4*s2);
}


void displayResult(float a , float b , float aire,  int n , float eps){
    printf("Approximation de l'integrale fonction f(x)=exp(sin(5*x)) sur l'intervale [%g;%g]\n" , a , b );
    printf("Avec %d subdivision et une precision de %f on a %f " , n , eps , aire );
}

void displayRes(float a , float b , float aire , int n ){
    printf("Approximation de l'integrale fonction f(x)=exp(sin(5*x)) sur l'intervale [%g;%g]\n" , a , b );
    printf("Avec %d subdivision on a %f " , n , aire );
}

float f(float x){
    return exp(sin(5.0*x));
}