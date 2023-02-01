#include <stdio.h>


int factorial(int n);
int main(){

    int n, n_factorial;

    printf("Ingresa n ");
    scanf("%d", &n);
    n_factorial = factorial(n);

    printf("El factorial es %d", n_factorial);
    return 0;
}

int factorial(int n){
    if(n==1 || n==0)
        return 1;
    return n*factorial(n-1);
}