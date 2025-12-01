#include <stdio.h>
#include <math.h>

float dico(float a , float b , float eps);
void afficherResultat(float a , float b , float x , float eps);
float f(float x);

int main(){
// data 
    float a = 0.1 , b = 1 , // les bornes pour la separation
    eps = 1e-6 ,  // epsilon pour le test 
    x = 23.9f; // valeur bidon 

// calcul
    x = dico(a,b,eps);

// resultat 
    afficherResultat(a,b,x,eps);

    return 0;
}

float dico(float a , float b , float eps){
    float x = 99.9f ; // valeur bidon again

    while( fabs(a - b) > eps ){
        x = (a+b)/2;

        if (f(a)*f(x) <= 0 ) {
            b = x;
        } else a = x;
    }

    return x;
}

void afficherResultat(float a , float b , float x , float eps){
    printf("La recherche de la valeur de l'equation f(x)=x-2-ln(x) sur l'intervalle [%g;%g] \n" , a , b);
    printf("Avec une precision de %f donne  : %f \n " , eps , x );

}

float f(float x){ return x-2-log(x); }