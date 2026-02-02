#include <stdio.h>
#include <stdlib.h>

float p(float x , int n , float** points);
float pj(float x , int j , float** points , int n);
void dessinerCourbe(float a ,float b);
float determineB(float a , int n , float** points);
float determineA(int n , float** points);
void afficherResultat(float a , float b ,int n);

int main(){
// initalisation des variables 
    float a;
    float b;
// nombres de points
    int n = 7;
// liste des points 

    float **points = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) points[i] = (float*) malloc(2*sizeof(float));
    
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
    
// calculs

    a = determineA(n,points);
    b = determineB(a,n,points);
    
// affichageDuResultat

	

// affichage 

    afficherResultat(a,b,n);
	dessinerCourbe(a,b);
}

void tracerCourbe(float** points,int n){
	printf("Opening a pipe to gnuplot \n");
	FILE *gp = popen("gnuplot -persist" , "w");

	// int signe = b < 0 ? 1 : 0;

	if(gp){
		fprintf(gp , "set term wxt size 800,600 \n");
		fprintf(gp , "set title 'Affichage du eo moa rangaha' \n");
		fprintf(gp , "set style data linespoint\n");
		
		fprintf(gp , "$data << EOF\n");
		
		int nb = 200;
		float x = 0;
		for(int i = 0 ; i < nb ; i++ ){	
			fprintf(gp,"%f %f\n" , x , p(x,n,points) );
			x += 0.1;	
		}
		
		fprintf(gp , "EOF \n");
		fprintf(gp , "plot $data\n");
		fflush(gp);
		pclose(gp);
	}
	else {
		printf("gnuplot not found ...... \n");
		printf("Can be installed with : \n sudo apt install gnuplot \n");
	}
}

float p(float x , int n , float** points){
	float f=0;
	for(int j = 0 ; j < n ; j++ ){
		f += points[j][1]*pj(x,j,points,n);
	}
	return f;
}

float pj(float x , int j , float** points , int n){
	float p = 0;
	
	for(int k = 0 ; k < n ; k++){
		if ( k != j)
			p *= (x - points[k][0])/(points[j][0] - points[k][0]);
	}

	return p;
}

void dessinerCourbe(float a ,float b){
	printf("Opening a pipe to gnuplot \n");
	FILE *gp = popen("gnuplot -persist" , "w");
	
	// int signe = b < 0 ? 1 : 0;
	
	if(gp){
		fprintf(gp , "set term wxt size 800,600 \n");
		fprintf(gp , "set title 'Affichage du dataset de data.csv' \n");
		fprintf(gp , "set style data linespoint\n");
		fprintf(gp , "set xzeroaxis\n");
		fprintf(gp , "set yzeroaxis\n");
		// if(signe == 0){
		//	fprintf(gp , "plot %f*x+%f , data.csv" , a , b);
		// } else fprintf(gp , "plot %f*x%f , data.csv" , a , b);
		fprintf(gp , "plot x-2-log(x) \n" );
		fflush(gp);
		pclose(gp);
	}
	else {
		printf("gnuplot not found ...... \n");
		printf("Can be installed with : \n sudo apt install gnuplot \n");
	}	
}

float moyenne(int n , float** points , int col){
    float val = 0 ;
    for (int i = 0; i < n; i++)
        val += points[i][col];
    
    return val/n;
}

float determineB(float a , int n , float** points){
    float sumX = moyenne(n,points,0);
    float sumY = moyenne(n,points,1);

    return sumY - a*sumX;
}

float determineA(int n , float** points){
    float sumXY = 0;
    float sumX = 0 , sumY = 0 , sumX2 = 0;

    for (int i = 0; i < n; i++){
        // n*sum(xi*yi)
        sumXY += points[i][0]*points[i][1];
        // sum(xi)
        sumX += points[i][0];
        // sum(yi)
        sumY += points[i][1];
        // sum(xi^2)
        sumX2 +=  points[i][0]* points[i][0];
    }  

    return (n*sumXY - sumX*sumY) / (n*sumX2 - sumX*sumX);
}

void afficherResultat(float a, float b, int n)
{
    printf(" La droite obtenu de l'ajustement lineaire de %d points avec la methode des moindres carres est : \n ", n);
    printf(" y = %f*x + %f  \n ", a, b);
}
