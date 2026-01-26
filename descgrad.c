#include <stdio.h>

void descGrad(float* a0 , float* b0 , float alpha , float** data);
float gradient(float a0 , float b0);
void afficherResultat(float a0 , float a1 , float alpha );

int main()
{
// donnees du point initial 
	float a0 = 1 , b0 = 1;
  
// pas de la descente
	float alpha = 0.01;
	
// data des points pour l'ajustement
	float** data = NULL;
  
// ajustement avec la methode de descente du gradient
	descGrad(&a0 , &b0 , data);

// affichage des coefficients apres le calcul
	afficherResultat(a0 , b0 , alpha);

	return 0;
}

void descGrad(float a0 , float b0 , float alpha , float** data ){
	float a = 0 , b = 0;
	while( 1 == 1 ) {
		a =  
		b = 
		
		if ((fabs(a0-a) + fabs(b0-b)) < 0.00001) break;
	}
}

float gradient(float a0 , float b0){
	
}

void afficherResultat(float a0 , float a1 , float alpha ){
	printf(" y=%f*x+%f\n avec un pas de alpha = %f\n" , a0 , a1 , alpha );
}
