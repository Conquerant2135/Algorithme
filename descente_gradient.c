#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void afficherGraphe(float** points , int n ,float a , float b);
float gradB(float a, float b, int n, float **points);
float gradA(float a, float b, int n, float **points);
void getDataf(const char *fileName, int *dim, float ***tA);
void descGrad(float *a, float *b, int n, float **points, float eps,float alpha);
void afficherResultat(float a, float b, int n);

int main()
{
    // l'epsilon
    float eps = 1e-7;
    // les points de depart
    float a = 1, b = 1;
    // nombre de points
    // alpha
    float alpha = 0.01;

    int n = 0;
    float **points = NULL;

    getDataf("data/data_mmc.txt" , &n , &points);
    
    descGrad(&a, &b, n, points, eps,alpha);

    afficherGraphe(points , n , a , b);
    afficherResultat(a, b, n);
}

void afficherGraphe(float** points , int n , float a , float b)
{
    FILE* gp = popen("gnuplot -persist" , "w");
    if (!gp)
    {
        perror("gnuplot not found please install");
        return;
    } 

    fprintf(gp , "$points << EOD \n ");

    for (int i = 0; i < n; i++)
    {
        fprintf(gp , "%f %f\n" , points[i][0] , points[i][1]);
    }
    
    fprintf(gp , "EOD \n");

    if (b < 0) {
        fprintf(gp ,  "plot $points with points , %f*x%f \n" , a , b);
    } else fprintf(gp ,  "plot $points with points , %f*x+%f \n" , a , b);
    


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

void getDataf(const char *fileName, int *dim, float ***tA) {
    FILE *pf = fopen(fileName, "r");
    if (!pf) {
        perror("Probleme a l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    if (fscanf(pf, "%d", dim) != 1) {
        perror("Erreur lecture dimension");
        fclose(pf);
        exit(EXIT_FAILURE);
    }

    float **A = (float **)malloc((*dim) * sizeof(float *));
    if (!A) {
        perror("Probleme d'allocation de A");
        fclose(pf);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *dim; i++) {
        A[i] = (float *)malloc(2 * sizeof(float));
        if (!A[i]) {
            perror("Probleme d'allocation d'une ligne de A");
            fclose(pf);
            exit(EXIT_FAILURE);
        }

        if (fscanf(pf, "%f %f", &A[i][0], &A[i][1]) != 2) {
            perror("Erreur lecture des points");
            fclose(pf);
            exit(EXIT_FAILURE);
        }
    }

    fclose(pf);

    *tA = A;
}

