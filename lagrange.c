#include <stdio.h>
#include <stdlib.h>

void lagrange(float **points, int n);
float p(float x, float **points, int n);
float pj(float x, float **points, int j, int n);

int main()
{
    // les donnees necessaire a la realisation de l'approximatoin
    int n = 7;
    float **points = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++)
    {
        points[i] = (float *)malloc(2 * sizeof(float));
    }

    points[0][0] = 0;
    points[0][1] = 0;
    points[1][0] = 1;
    points[1][1] = 0.75;
    points[2][0] = 2;
    points[2][1] = 0;
    points[3][0] = 3;
    points[3][1] = 1.5;
    points[4][0] = 4;
    points[4][1] = -0.75;
    points[5][0] = 5;
    points[5][1] = -1;
    points[6][0] = 6;
    points[6][1] = 0.5;

    lagrange(points, n);

    return 0;
}

void lagrange(float **points, int n)
{
    FILE *gp = popen("gnuplot -persist", "w");
    if (!gp)
    {
        perror("gnuplot not found please install");
        return;
    }

    // fprintf(gp , "$points << EOD \n");

    // for (int i = 0; i < n; i++)
    // {
    //     fprintf(gp, "%f %f\n", points[i][0], points[i][1]);
    // }

    // fprintf(gp , " EOD \n");


    int nb_pts = 200;

    float x_min = points[0][0];
    float x_max = points[n - 1][0];

    float step = (x_max - x_min) / (nb_pts - 1);
    float x = x_min;

    fprintf(gp , " $curve << EOD \n");

    for (int i = 0; i < nb_pts; i++)
    {
        fprintf(gp, "%f %f\n", x, p(x, points, n));
        x += step;
    }

    fprintf(gp, "EOD\n");
    fprintf(gp, "plot $curve with lines\n");

    fflush(gp);
    pclose(gp);
}

float p(float x, float **points, int n)
{
    float val = 0;

    for (int j = 0; j < n; j++)
    {
        val += points[j][1] * pj(x, points, j, n);
    }

    return val;
}

float pj(float x, float **points, int j, int n)
{
    float val = 1;
    for (int k = 0; k < n; k++)
    {
        if (k != j)
        {
            val *= (x - points[k][0]) / (points[j][0] - points[k][0]);
        }
    }
    return val;
}