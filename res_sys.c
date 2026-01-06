#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void afficherSolutionsP(int* L , float* solutions , int n);
void gaussP(float** a , float* b , int n , int* L);
void solveTriSupP(float** a , float* b , int n, int* L);
void makeTriSupP(float** a , float* b , int n, int* L);
void bestPivot(float** a , int col, int* L, int n);
void permutation(int* L , int i , int j);
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
	int* L = NULL;
	
	afficherMatrice(a , dimension);
	afficherSolutions(b , dimension);
	
	gaussP(a,b,dimension,L);
	
	afficherMatrice(a , dimension);
	afficherSolutions(b , dimension);
	
	return 0;
}

void afficherSolutionsP(int* L , float* solutions , int n){
	printf("Solutions :\n");
  for (int i = 0; i < n; i++)
  {
      printf("x%d = %f\n", i + 1, solutions[L[i]]);
  }
}

void gaussP(float** a , float* b , int n , int* L){
	L = malloc(n*sizeof(int));
	for (int i = 0 ; i < n ; i++ ) L[i] = i;
	
	makeTriSupP(a,b,n,L);
	solveTriSupP(a,b,n,L);
}

void solveTriSupP(float** a , float* b , int n, int* L){
	float s = 0;		
	for(int i = n - 1 ; i >= 0 ; i--){
		s = 0;
		for( int j=i+1 ; j < n ; j++ ){
			s += a[L[i]][j]*b[L[j]];
		}
		b[L[i]] = (b[L[i]]-s)/a[L[i]][i];
	}	
}

void makeTriSupP(float** a , float* b , int n, int* L){
	for(int k = 0 ; k < n ; k++ ){
		afficherMatrice(a , n);
		bestPivot(a , k , L , n );
		afficherMatrice(a , n);
		for(int i = k+1 ; i < n ; i++ ){
			for(int j = k+1 ; j < n ; j++ ){
				a[L[i]][j] = a[L[i]][j] - (a[L[i]][k]/a[L[k]][k])*a[L[k]][j];
			}
	
			b[L[i]] = b[L[i]] - (a[L[i]][k]/a[L[k]][k])*b[L[k]]; 
			a[L[i]][k] = 0;
		}
		
	}
}

void bestPivot(float** a , int col, int* L , int n){
	
	for(int j = col + 1 ; j < n ; j++ ){
		if( fabs(a[L[j]][col]) > fabs(a[L[col]][col]) ) {
			permutation(L , col , j);
		}
	}
	
}

void permutation(int* L , int i , int j){
	int temp = L[i];
	L[i] = L[j];
	L[j] = temp;	
}

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
	
	a[0] = 5   ;
	a[1] = 2   ;
	a[2] = 3  ;
	
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

    a[0][0] =  0;  a[0][1] =  2  ; a[0][2] = 3  ; 
    a[1][0] =  1;  a[1][1] =  -1 ; a[1][2] = 1 ; 
    a[2][0] =  2;  a[2][1] =  1  ; a[2][2] = 1  ;  

    return a;
}


	
