#include <iostream>

float horner(float* coeff , int size , float x);
void equation(float * coeff , int size);

int main() {
    return 0;
}

void equation(float * coeff , int size){

    std::cout << "P(x)=";

    for (int i = 0; i < size; i++) {
        std::cout << "(";
    }
    

    for (int i = size - 2 ; i > 0 ; i--) {
        std::cout << "" ;
    }
    
    std::cout << "+" << coeff[0];
}

float horner(float* coeff , int size , float x){
    float value = coeff[size-1];

    for (int i = size - 2 ; i >= 0 ; i--) {
        value = coeff[i] + x*value;
    }
    return value;
}