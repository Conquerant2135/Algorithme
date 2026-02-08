#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void afficher_pol_horner(int n, float *coeff);
float horner(int n, float *coeff, float x);
void afficher_res(float px, float *coeff, float x, int n);

int main()
{
    // le nombre de coefficient du polynome
    int n = 4;
    // la liste des coefficients
    float *coeff = (float *)malloc(n * sizeof(float));
    // correspond au coeff 0 et ainsi de suite
    coeff[0] = 2;
    coeff[1] = 4;
    coeff[2] = 3;
    coeff[3] = 1;
    // le x avec lequel on va evaluer notre polynome
    float x = 3;
    // variable pour contenir la solution;
    float px = 12.f;

    // calcul de la valeur
    px = horner(n, coeff, x);

    afficher_res(px, coeff, x, n);
}

void m_afficher_pol_horner(int n, float *coeff)
{
    printf(" \n P(x) = " );
    char pol_horner[500];
    char temp[500];

    snprintf(pol_horner , sizeof(pol_horner) , " %f " , coeff[n-1]);

    for (int i = n-1 ; i > 0; i++)
    {
        if ( coeff[i-1] < 0  ) {
            snprintf(temp , sizeof(temp), " ( %s )*x %f " , pol_horner , coeff[i-1] );        
        } else snprintf(temp , sizeof(temp), " ( %s )*x + %f " , pol_horner , coeff[i-1] );        

        strcpy(pol_horner, temp);
    }

    printf(pol_horner);
}

void afficher_pol_horner(int n, float *coeff)
{
    // ouvrir les parentheses
    printf("\n P (x) = ");
    for (int i = 0; i < n - 1; i++)
    {
        printf("(");
    }

    for (int i = n; i > 0; i--)
    {
        if (i - 1 != n - 1)
        {
            printf("+");
        }

        if (i - 1 == 0)
        {
            printf("%f \n ", coeff[i - 1]);
        }
        else
            printf("%f )*x ", coeff[i - 1]);
    }
}

float horner(int n, float *coeff, float x)
{
    float val = 0;
    float x_n = 1;

    for (int i = n; i > 0; i--)
    {
        val = val * x + coeff[i - 1];
    }
    return val;
}

void afficher_res(float px, float *coeff, float x, int n)
{
    printf(" La valeur de notre polynome : \n ");
    printf(" P(x) =");
    for (int i = n; i > 0; i--)
    {
        if (coeff[i - 1] > 0 && i - 1 != n - 1)
            printf("+");

        if (i - 1 == 0)
        {
            printf("%3.f", coeff[i - 1]);
        }
        else if (i - 1 == 1)
        {
            printf("%3.f*x", coeff[i - 1]);
        }
        else
        {
            printf("%3.f*x^%d", coeff[i - 1], i - 1);
        }
    }

    m_afficher_pol_horner(n, coeff);

    printf("\n P(%f) = %f \n", x, px);
}