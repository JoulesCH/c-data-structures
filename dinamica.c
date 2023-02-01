#include <stdio.h>
#include <stdlib.h>
int main(){
    int n, *r;
    char ans;
    printf("La memoria de la variable n: %p es reservada durante la compilacion", &n);
    
    do{
        r = (int*)malloc(sizeof(int));
        printf("\n\nLa memoria de la variable r: %x es reservada durante la compilacion", r);
        printf("\nQuieres reservar otra direccion? s/n ");
        fflush(stdin);
    }while(scanf(" %[s]", &ans)==1);
    
    
    return 0;
}