#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float gradB(float a, float b, int n, float **points);
float gradA(float a, float b, int n, float **points);
void descGrad(float *a, float *b, int n, float **points, float eps,float alpha);
void afficherResultat(float a, float b, int n);

int main()
{
    // l'epsilon
    float eps = 1e-7;
    // les points de depart
    float a = 1, b = 1;
    // nombre de points
    int n = 9;
    // alpha
    float alpha = 0.1;

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


    descGrad(&a, &b, n, points, eps,alpha);

    afficherResultat(a, b, n);
}

float ecart(float a, float b, int n, float **points)
{
    float rep = 0;

    for (int i = 0; i < n; i++)
    {
        rep += (points[i][1] - (points[i][0] * a + b))*(points[i][1] - (points[i][0] * a + b));
    }

    return rep / n;
}

float gradA(float a, float b, int n, float **points)
{
    float rep = 0;
    for (int i = 0; i < n; i++)
    {
        rep += points[i][0] * (points[i][1] - (a * points[i][0] + b));
    }
    return -(2.0f / n )* rep;
}

float gradB(float a, float b, int n, float **points)
{
    float rep = 0;
    for (int i = 0; i < n; i++)
    {
        rep += points[i][1] - (a * points[i][0] + b);
    }
    return -(2.0f / n )* rep;
}

void descGrad(float *a, float *b, int n, float **points, float eps,float alpha)
{
    float tempa = *a;
    float tempb = *b;

    while (1)
    {
        tempa = *a;
        tempb = *b;

        *a = *a - alpha*gradA(tempa, tempb, n, points);
        *b = *b - alpha*gradB(tempa, tempb, n, points);

        if (fabs(ecart(*a, *b, n, points) - ecart(tempa, tempb, n, points)) < eps)
            break;
    }
}

void afficherResultat(float a, float b, int n)
{
    printf(" La droite obtenu de l'ajustement lineaire de %d points \n est : ", n);
    printf(" y = %f*x + %f  \n ", a, b);
}