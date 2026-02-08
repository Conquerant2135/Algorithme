#include <math.h>
#include <stdio.h>

void newton(int* n , float eps , float* x_0 );
void afficher_res(float res , float eps , int n);
float df(float x);
float f(float x);

int main()
{
    float x_0 = 1;
    int n = 0;
    float eps = 1e-6;

    newton(&n , eps , &x_0);

    afficher_res(x_0 , eps , n);
}

void newton(int* n , float eps , float* x_0 )
{
    while ( fabs( f(*x_0) ) > eps )
    {
        (*x_0) = *x_0 - (f(*x_0))/(df(*x_0));
        (*n)++;
    }
}

void afficher_res(float res , float eps , int n)
{   
    printf( " Pour la fonction f(x) = x^2 - 2 , avec une proximite de %f  \n " , eps );
    printf( " Et apres %d iteration on a : \n " , n );
    printf( " f(%f) = 0  \n\n\n " , res);
}


float df(float x)
{
    return 2*x;
}


float f(float x)
{
    printf( " %f " , x*x-2);   
    return x*x-2;
}
