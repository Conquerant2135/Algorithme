#include <stdio.h>
#include <stdlib.h>

/* Affichage de la matrice augmentée */
void afficher(int n, float **a) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%8.3f ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* Méthode de Gauss (sans permutation) */
void gauss(int n, float **a, float *x) {
    float pivot;

    /* Élimination */
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            pivot = a[j][i] / a[i][i];
            for (int k = i; k <= n; k++) {
                a[j][k] -= pivot * a[i][k];
            }
        }
    }

    /* Substitution arrière */
    for (int i = n - 1; i >= 0; i--) {
        x[i] = a[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= a[i][j] * x[j];
        }
        x[i] /= a[i][i];
    }
}

int main() {
    int n = 3;

    /* Allocation de la matrice n x (n+1) */
    float **a = malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        a[i] = malloc((n + 1) * sizeof(float));
    }

    /* Allocation du vecteur solution */
    float *x = malloc(n * sizeof(float));

    /* Exemple de système */
    a[0][0] =  2; a[0][1] =  1; a[0][2] = -1; a[0][3] =  8;
    a[1][0] = -3; a[1][1] = -1; a[1][2] =  2; a[1][3] = -11;
    a[2][0] = -2; a[2][1] =  1; a[2][2] =  2; a[2][3] = -3;

    gauss(n, a, x);

    printf("Solutions :\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %f\n", i + 1, x[i]);
    }

    /* Libération mémoire */
    for (int i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
    free(x);

    return 0;
}
