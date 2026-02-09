#include <stdio.h>
#include <stdlib.h>

void lagrange(float **points, int n);
float p(float x, float **points, int n);
float pj(float x, float **points, int j, int n);
void getDataf(const char *fileName, int *dim, float ***tA);

int main()
{
    // les donnees necessaire a la realisation de l'approximatoin
    int n = 0;
    float **points = NULL;

    getDataf("data/data_interpol.txt" , &n , &points);
    
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

    int nb_pts = 200;

    float x_min = points[0][0];
    float x_max = points[n - 1][0];

    float step = (x_max - x_min) / (nb_pts - 1);
    float x = x_min;
    
    
    fprintf(gp , "$data << EOD \n");

	for(int i = 0 ; i < n ; i++ ){
	 		fprintf(gp , "%f %f\n" , points[i][0] , points[i][1]  );
	}
	
	fprintf(gp, "EOD\n");
	
	
    fprintf(gp , " $curve << EOD \n");

    for (int i = 0; i < nb_pts; i++)
    {
        fprintf(gp, "%f %f\n", x, p(x, points, n));
        x += step;
    }

    fprintf(gp, "EOD\n");
    fprintf(gp, "plot $curve with lines , $data with points\n");

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

