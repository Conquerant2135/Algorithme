#include <stdio.h>

float determinant( int size , float matrice[3][3]);
void substitute(int l1 , int l2 , float matrice[3][3]);
void afficher_matrice(float matrice[3][3]);

int main(){

    float matrice[3][3] = {
    {1.5, -2.3, 0.7},
    {3.1,  0.0, 4.2},
    {-1.4, 2.8, 3.3}
    };

    printf("Voici le determinant de la matrice en utilisant la methode de Gauss : %f " , determinant(3 , matrice));

    return 0;
}

void afficher_matrice(float matrice[3][3]) {
    for (int i = 0 ; i < 3; i++) {
        for (int k = 0 ; k < 3 ; k++) {
            printf("%f " , matrice[i][k]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
}

void substitute(int l1 , int l2 , float matrice[3][3]){
    float* tmp = matrice[l2];
    for (int i = 0; i < 3; i++) {
        matrice[l2][i] = matrice[l1][i];
    }

    for (int i = 0; i < 3; i++) {
        matrice[l1][i] = tmp[i];
    }
}

float determinant(int size , float matrice[3][3]) { 
    float pivot = 0.0;
    for (int i = 0; i < size ; i++) {
        for ( int j = i + 1 ; j < size; j++) {
           if (matrice[i][i] == 0 ) continue;        
           pivot = matrice[j][i]  / matrice[i][i];
           for ( int k = i; k < size; k++) {
                matrice[j][k] = matrice[j][k] - matrice[i][k]*pivot;
           }
           afficher_matrice(matrice);
        }
    }
    return matrice[0][0] * matrice[1][1] * matrice[2][2];
}