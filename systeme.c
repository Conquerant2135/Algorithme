
#include <stdio.h>
#include <stdlib.h>

void gauss(int n, float **a, float *x);
float *secondMembre(int n);
void afficherSolutions(float *solutions, int n);
float **matrice(int n);
void afficherMatrice(int n, float **a);

int main()
{
    int n = 3;
    float **matr = matrice(n);
    float *secMembre = secondMembre(n);

    gauss(n, matr, secMembre);

    afficherSolutions(secMembre , n);
    return 0;
}

void gauss(int n, float **a, float *x)
{
    float pivot;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            pivot = a[j][i] / a[i][i];
            for (int k = i; k <= n; k++)
            {
                a[j][k] -= pivot * a[i][k];
            }
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        x[i] = a[i][n];
        for (int j = i + 1; j < n; j++)
        {
            x[i] -= a[i][j] * x[j];
        }
        x[i] /= a[i][i];
    }
}

void afficherSolutions(float *solutions, int n)
{
    printf("Solutions :\n");
    for (int i = 0; i < n; i++)
    {
        printf("x%d = %f\n", i + 1, solutions[i]);
    }
}

float* secondMembre(int n){

    float *x = malloc(n * sizeof(float));
    return x;
}

float **matrice(int n)
{
    float **a = malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++)
    {
        a[i] = malloc((n + 1) * sizeof(float));
    }

    a[0][0] = 2;  a[0][1] = 1; a[0][2] = -1; a[0][3] = 8;
    a[1][0] = -3; a[1][1] = -1; a[1][2] = 2; a[1][3] = -11;
    a[2][0] = -2; a[2][1] = 1;
    a[2][2] = 2;
    a[2][3] = -3;

    return a;
}

void afficherMatrice(int n, float **a)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            printf("%8.3f ", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
