#include <iostream>
#include <cstdlib>

float horner( float* coeff , int size , float x );

int main(){
    const int taille = 5;

    // allocate and initialize a size-5 float array
    float* coeff = (float*) malloc(taille * sizeof(float));
    if (!coeff) return 1;

    // example coefficients: 1.0, 2.0, 3.0, 4.0, 5.0
    coeff[0] = 1.0f;
    coeff[1] = 2.0f;
    coeff[2] = 3.0f;
    coeff[3] = 4.0f;
    coeff[4] = 5.0f;
    
    // example usage
    float x = 2.0f;
    float value = horner(coeff, taille, x);
    
    std::cout << "P(" << x << ") = " << value << std::endl;

    free(coeff);
    return 0;
}

float horner( float* coeff , int size , float x ) {
    float value = 0;
    float x_n = 1;

    for (int i = 0 ; i < size ; i++) {
        value += coeff[i] * x_n;
        x_n *= x; 
    }
    
    return value;
}