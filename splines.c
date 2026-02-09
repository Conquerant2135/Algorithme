#include <stdlib.h>
#include <stdio.h>

float *newVect(int dim);
void problem(char* message);
void getDataf(const char *fileName, int *dim, float ***tA);
void solveS2(float lambda, float rho, float *Y, float *s2, int dim);
void tridiag(float *a, float *b, float *c,float *r, float *u, int n);
void coeff(float** points , int n , float** va , float** vb , float** vs2);
float s(float** points , float* s2 , float* a , float* b , int j , float x);
void cSpline(float** points , int n , float* a , float* b , float* s2);

int main () 
{
	int n = 0;
	float** points = NULL;
	float* va = NULL;
	float* vb = NULL;
	float* vs2 = NULL;
	
	getDataf("data/data_spline.txt" , &n , &points);
    
	coeff(points , n , &va , &vb , &vs2);
	
	cSpline(points,n,va,vb,vs2);
}

void cSpline(float** points , int n , float* a , float* b , float* s2){
	FILE *gp = popen("gnuplot -persist", "w");
    if (!gp)
    {
        perror("gnuplot not found please install");
        return;
    }
    
    int nb_points = 200;
    int x_min = points[0][0];
    int x_max = points[1][0];
	float step = (x_max - x_min )/(nb_points-1);
    float x = x_min;
    
    fprintf(gp , "$data << EOD \n");
    
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
	
	fprintf(gp , "EOD \n");
	
	fprintf(gp , "plot $data with lines \n");
    
    fprintf(gp , "\n");
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

// dans cet exemple on assume que les points x sont equidistant 
void coeff(float** points , int n , float** va , float** vb , float** vs2){
	float lambda = 0.5 , rho = 0.5, dx = points[1][0] - points[0][0];
	int j = 0;
	float* Y = newVect(n-1);
	float* s2 = newVect(n); 
	float* a = newVect(n-1);  
	float* b = newVect(n-1);


    s2[0] = 0.0f;
    s2[n-1] = 0.0f;
	
	for (int j = 1; j < n-1; j++) {
        Y[j-1] = (6.0f / (2.0f * dx)) *
                 ((points[j+1][1] - points[j][1]) / dx
                - (points[j][1]   - points[j-1][1]) / dx);
    }
	
	s2++;
	solveS2(lambda , rho , Y , s2 , n);
	s2--;
	
	// etablissement de a et b 
	for (j = 0 ; j < n - 1; j++){
		a[j] = (points[j][1]   / dx) - (dx / 6.0f) * s2[j];
        b[j] = (points[j+1][1] / dx) - (dx / 6.0f) * s2[j+1];
        // printf(" a[%d] = %f  b[%d] = %f \n" , j , a[j] , j , b[j]);	
	}
	
	*va = a;
	*vb = b;
	*vs2 = s2;
}

void solveS2(float lambda, float rho, float *Y, float *s2, int dim){
    float *B=NULL, *C=NULL, *D=NULL;
    int j=0;

    B = newVect(dim);		// diagonale principale
    C = newVect(dim);		// première surdiagonale
    D = newVect(dim);		// première sous-diagonale
    for(j=0; j<dim; j++){
        B[j] = 2;
        C[j] = lambda;		// on suppose que les points sont équidistant
        D[j] = rho;			// donc c_j et d_j sont constant
    }
    tridiag(D,B,C,Y,s2,dim);
 }

/* Tridiagonal matrix solver.  Nonzero diagonals of the matrix are
   represented by arrays a, b, and c (see Numerical Recipes).
   All arrays start at 0
 [b_0 c_0                  ] [ u_0 ]   [ r_0 ]
 [a_1 b_1 c_1              ] [ u_1 ]   [ r_1 ]
 [          ...            ] [ ... ] = [ ... ]
 [        a_n-2 b_n-2 c_n-2] [u_n_2]   [r_n-2]
 [              a_n-1 b_n-1] [u_n-1]   [r_n-1]
 */
 
void tridiag(float *a, float *b, float *c,float *r, float *u, int n){
    int j;
    float bet, gam[n];

    if (b[0] == 0.0) problem("Division par 0");
    u[0] = r[0] / (bet=b[0]);
    for (j = 1; j < n; j++) {
        gam[j] = c[j-1]/bet;
        bet = b[j] - a[j]*gam[j];
        if (bet == 0.0) problem("Division par 0");
        u[j] = (r[j]-a[j]*u[j-1]) / bet;
    }
    for (j = n-2; j >= 0; j--)
        u[j] -= gam[j+1]*u[j+1];
}

float *newVect(int dim){
	float* v=NULL;
	v = malloc(dim*sizeof(float));
	if(v==NULL) problem("Ne peut allouer un vecteur");
	return v;
}

void problem(char* message){
	printf("%s\n", message);
	exit(2);
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
