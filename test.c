#include <stdlib.h>
#include <stdio.h>

/* prototypes */
float *newVect(int dim);
void problem(char* message);
void getDataf(const char *fileName, int *dim, float ***tA);

void tridiag(float *a, float *b, float *c, float *r, float *u, int n);
void solveS2(float lambda, float rho, float *Y, float *s2, int dim);

void coeff(float **points, int n, float **va, float **vb, float **vs2);
float s(float **points, float *s2, float *a, float *b, int j, float x);
void cSpline(float **points, int n, float *a, float *b, float *s2);

/* ===================== MAIN ===================== */

int main(void)
{
    int n = 0;
    float **points = NULL;
    float *a = NULL, *b = NULL, *s2 = NULL;

    getDataf("data/data_spline.txt", &n, &points);
    coeff(points, n, &a, &b, &s2);
    cSpline(points, n, a, b, s2);

    return 0;
}

/* ===================== SPLINE ===================== */

void cSpline(float **points, int n, float *a, float *b, float *s2)
{
    FILE *gp = popen("gnuplot -persist", "w");
    if (!gp) {
        perror("gnuplot");
        return;
    }

    int nb_points = 200;
    fprintf(gp, "$data << EOD\n");

    for (int j = 0; j < n - 1; j++) {
        float x_min = points[j][0];
        float x_max = points[j+1][0];
        float step = (x_max - x_min) / (nb_points - 1);
        float x = x_min;

        for (int i = 0; i < nb_points; i++) {
            fprintf(gp, "%f %f\n", x, s(points, s2, a, b, j, x));
            x += step;
        }
    }

    fprintf(gp, "EOD\n");
    fprintf(gp, "plot $data with lines\n");
    pclose(gp);
}

float s(float **points, float *s2, float *a, float *b, int j, float x)
{
    float h = points[j+1][0] - points[j][0];
    float dx1 = points[j+1][0] - x;
    float dx2 = x - points[j][0];

    return (s2[j]   * dx1*dx1*dx1 +
            s2[j+1] * dx2*dx2*dx2) / (6.0f * h)
           + a[j] * dx1
           + b[j] * dx2;
}

/* ===================== COEFFICIENTS ===================== */

void coeff(float **points, int n, float **va, float **vb, float **vs2)
{
    float dx = points[1][0] - points[0][0];
    float lambda = 0.5f, rho = 0.5f;

    float *Y  = newVect(n-2);
    float *s2 = newVect(n);
    float *a  = newVect(n-1);
    float *b  = newVect(n-1);

    s2[0] = 0.0f;
    s2[n-1] = 0.0f;

    for (int j = 1; j < n-1; j++) {
        Y[j-1] = (6.0f / (2.0f * dx)) *
                 ((points[j+1][1] - points[j][1]) / dx
                - (points[j][1]   - points[j-1][1]) / dx);
    }

    solveS2(lambda, rho, Y, &s2[1], n-2);

    for (int j = 0; j < n-1; j++) {
        a[j] = (points[j][1]   / dx) - (dx / 6.0f) * s2[j];
        b[j] = (points[j+1][1] / dx) - (dx / 6.0f) * s2[j+1];
    }

    *va = a;
    *vb = b;
    *vs2 = s2;
}

/* ===================== SYSTEME ===================== */

void solveS2(float lambda, float rho, float *Y, float *s2, int dim)
{
    float *A = newVect(dim);
    float *B = newVect(dim);
    float *C = newVect(dim);

    for (int j = 0; j < dim; j++) {
        A[j] = rho;
        B[j] = 2.0f;
        C[j] = lambda;
    }

    tridiag(A, B, C, Y, s2, dim);
}

/* ===================== TRIDIAG ===================== */

void tridiag(float *a, float *b, float *c, float *r, float *u, int n)
{
    float gam[n];
    float bet = b[0];

    if (bet == 0.0f) problem("Division par 0");

    u[0] = r[0] / bet;

    for (int j = 1; j < n; j++) {
        gam[j] = c[j-1] / bet;
        bet = b[j] - a[j] * gam[j];
        if (bet == 0.0f) problem("Division par 0");
        u[j] = (r[j] - a[j] * u[j-1]) / bet;
    }

    for (int j = n-2; j >= 0; j--)
        u[j] -= gam[j+1] * u[j+1];
}

/* ===================== UTIL ===================== */

float *newVect(int dim)
{
    float *v = malloc(dim * sizeof(float));
    if (!v) problem("Allocation impossible");
    return v;
}

void problem(char *message)
{
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

void getDataf(const char *fileName, int *dim, float ***tA)
{
    FILE *pf = fopen(fileName, "r");
    if (!pf) problem("Ouverture fichier");

    fscanf(pf, "%d", dim);

    float **A = malloc(*dim * sizeof(float*));
    for (int i = 0; i < *dim; i++) {
        A[i] = malloc(2 * sizeof(float));
        fscanf(pf, "%f %f", &A[i][0], &A[i][1]);
    }

    fclose(pf);
    *tA = A;
}
