#include <stdio.h>
#include <stdlib.h>

void gaussP(float** a , float* b , int n);
void gauss(float** a , float* b , int n);
void solveTriSup(float** a , float* b , int n);
void makeTriSup(float** a , float* b , int n);
void afficherSolutions(float* solutions , int n);
float* secondMembre(int n);
void afficherMatrice(float** matrice , int n);
float** matrice(int n);

int main()
{
	int dimension = 3;
	float** a = matrice(dimension);
	float*  b = secondMembre(dimension);
	
	afficherMatrice(a , dimension);
	afficherSolutions(b , dimension);
	
	gauss(a,b,dimension);
	
	afficherMatrice(a , dimension);
	afficherSolutions(b , dimension);
	
	return 0;
}

void gauss

void gauss(float** a , float* b , int n){ 	
	makeTriSup(a,b,n);
	solveTriSup(a,b,n);
}

void solveTriSup(float** a , float* b , int n){
	float s = 0;		
	for(int i = n - 1 ; i >= 0 ; i--){
		s = 0;
		for( int j=i+1 ; j < n ; j++ ){
			s += a[i][j]*b[j];
		}
		b[i] = (b[i]-s)/a[i][i];
	}
}

void makeTriSup(float** a , float* b , int n){
	for(int k = 0 ; k <= n ; k++ ){
		for(int i = k+1 ; i < n ; i++ ){
			for(int j = k+1 ; j < n ; j++ ){
				a[i][j] = a[i][j] - (a[i][k]/a[k][k])*a[k][j];
			}

			b[i] = b[i] - (a[i][k]/a[k][k])*b[k]; 
			a[i][k] = 0;
		}
	}
}

void afficherSolutions(float *solutions, int n) {
    printf("Solutions :\n");
    for (int i = 0; i < n; i++)
    {
        printf("x%d = %f\n", i + 1, solutions[i]);
    }
}

float* secondMembre(int n){
	float* a = malloc(n*sizeof(float));
	
	a[0] = 4   ;
	a[1] = 5   ;
	a[2] = 11  ;
	
	return a;
}

void afficherMatrice( float **matrice , int n ) {
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%8.3f ", matrice[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

float** matrice(int n) {
    float **a = malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        a[i] = malloc(n * sizeof(float));
    }

    a[0][0] =  4;  a[0][1] =  8 ; a[0][2] = 12 ; 
    a[1][0] =  3;  a[1][1] =  8 ; a[1][2] = 13 ; 
    a[2][0] =  2;  a[2][1] =  9 ; a[2][2] = 18 ;  

    return a;
}


	
