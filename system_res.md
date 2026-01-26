# Resolution de systeme d'equation 

Programme C basique pour resoudre un systeme d'equation en utilisant 
la methode de Gauss avec une implementation de la methode de permutation partielle

## Methode de Gauss 

+ etape 1 : transformation de la matrice augmentee en une matrice triangulaire superieur

Dans cette forme ci 3 * 3 , transformer les elements sous les diagonales en 0

```
    a b c
    0 d e
    0 0 f
```

```C 

void makeTriSup(float** a , float* b , int n){
	float alpha = 0;
    for(int k = 0 ; k < n - 1 ; k++ ){
		for(int i = k+1 ; i < n ; i++ ){
            alpha = a[i][k]/a[k][k];
			for(int j = k+1 ; j < n ; j++ ){
				a[i][j] = a[i][j] - alpha*a[k][j];
			}

			b[i] = b[i] - alpha*b[k]; 
			a[i][k] = 0;
		}		
	}
}

``` 

Nous avons besoin de la matrice carree float** a et du second membre float* b ainsi que
de la dimension de la matrice pour les boucles .

La premiere boucle (avec l'indice k ) est celle qui nous permet de changer de ligne pour commencer a etudier le prochain pivot , l'element a[k] est donc la ligne de pivot .

La 2e boucle (avec l'indice i) sert a parcourir chaque ligne afin de pouvoir faire les operation de reduction de ligne sur chaque ligne 

La 3e boucle (avec l'indice j) sert a effectuer le operations de reduction de ligne


``` C

float alpha = a[i][k]/a[k][k];

for(int j = k+1 ; j < n ; j++ ){
	a[i][j] = a[i][j] - alpha*a[k][j];
}

```

alpha : c'est le coefficient qui permet de nullifier les coefficients a supprimer 
sur chaque ligne

```C

b[i] = b[i] - alpha*b[k]; 
a[i][k] = 0;


```

Cette partie calcule a son tour la valeur du second membre par rapport a alpha
On initialiste a[i][k] a 0 car si on fait la soustraction ca va donner 0 , nous protege d'une operation en trop

+ Etape 2 : resolution de la matrice triangulaire superieur 

```C

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

```

Pour ce faire on va partir depuis le pied de la matrice pour remonter (comme avec la methode de substitution) , c'est ce que fait la 1ere boucle 

```C

s = 0;
for( int j=i+1 ; j < n ; j++ ){
	s += a[i][j]*b[j];
}
b[i] = (b[i]-s)/a[i][i];

```


C'est cette partie qui calcule la valeur des inconnues 

La boucle presente fait le le produit des solutions trouvees avec les elements correspondants dans la matrice ( j'espere que azonlah fa zay ny tsotra indrindra raha mety ) . Intuivement ca fait une resolution par substitution d'ou on envoie la somme au second membre et ainsi division par le coefficient de la diagonale ( car c'est la seule inconnue de la ligne)

## Methode de permutation partielle 

La logique des algorithmes de triangularisation et de resolution sont les memes sauf que on doit va entretenir un tableau d'entier des lignes qui est la vraie position des lignes par rapport aux substitution . Raha misy tsy azo afaka mandefa mp , possible misy diso ireny fin de boucle irenly 

```C

void makeTriSupP(float** a , float* b , int n, int* L){
	for(int k = 0 ; k < n - 1 ; k++ ){
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


```