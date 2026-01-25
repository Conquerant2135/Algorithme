#include <stdio.h>
#include <stdlib.h>

float determineB(float a , int n , float** points);
float determineA(int n , float** points);
void afficherResultat(float a , float b ,int n);

int main(){
// initalisation des variables 
    float a;
    float b;
// nombres de points
    int n = 9;
// liste des points 

    float **points = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) points[i] = (float*) malloc(2*sizeof(float));
    
    points[0][0] = 1;
    points[0][1] = 6.008;
    points[1][0] =1.1;
    points[1][1] = 5.257;
    points[2][0] = 1.8;
    points[2][1] = 9.549;
    points[3][0] = 2.2;
    points[3][1] = 11.098;
    points[4][0] = 2.5;
    points[4][1] = 15.722;
    points[5][0] = 3.5;
    points[5][1] =27.130;
    points[6][0] = 3.7;
    points[6][1] = 28.828;
    points[7][0] = 4;
    points[7][1] = 33.772;
    points[8][0] = 5;
    points[8][1] = 45.15;

// calculs

    a = determineA(n,points);
    b = determineB(b,n,points);

// affichage 

    afficherResultat(a,b,n);
}

float moyenne(int n , float** points , int col){
    float val = 0 ;
    for (int i = 0; i < n; i++)
        val += points[i][col];
    
    return val/n;
}

float determineB(float a , int n , float** points){

}

float determineA(int n , float** points){
    float sumXY = 0;
    float sumX = 0 , sumY = 0 , sumX2 = 0;

    for (int i = 0; i < n; i++){
        // n*sum(xi*yi)
        sumXY += points[i][0]*points[i][1];
        // sum(xi)
        sumX += points[i][0];
        // sum(yi)
        sumY += points[i][1];
        // sum(xi^2)
        sumX2 +=  points[i][0]* points[i][0];
    }

    return (n*sumXY - sumX*sumY) / (n*sumX2 - sumX*sumX);
}

void afficherResultat(float a, float b, int n)
{
    printf(" La droite obtenu de l'ajustement lineaire de %d points \n est : ", n);
    printf(" y = %f*x + %f  \n ", a, b);
}