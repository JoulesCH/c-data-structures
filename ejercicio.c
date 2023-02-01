/*
Escribir un programa de conteo de votos para unas elecciones

El usuario ingresará la cantidad de votos para cada uno de los 4 candidatos en cada distrito

El programa debe insertar los votos en un arreglo dinámico y posteriormente sumarlos
*/

#include <stdio.h>
#include <stdlib.h>

int NO_CANDIDATOS = 4;
int NO_DISTRITOS = 2;
struct distrito{
    int  no_distrito;
    int * candidatosCuenta;
    int tamanio;

};
void contarVotos(struct distrito ** distritos);
struct distrito capturarVotos(struct distrito ** distritos);
int main(){

    //Inicializar la cuenta
    struct distrito * distritos = (struct distrito*) malloc(NO_DISTRITOS*sizeof(struct distrito));;
    for(int i=0; i<NO_DISTRITOS; i++){
        struct distrito district = {i, NULL, NO_DISTRITOS};
        district.candidatosCuenta = (int*) malloc(NO_CANDIDATOS*sizeof(int));
        for (int j=0; j<NO_CANDIDATOS; j++){
            *(district.candidatosCuenta + j*sizeof(int)) = 0;
        }
        *(distritos + i*sizeof(struct distrito)) = district;
    }

    int res=1;
    *distritos = capturarVotos(&distritos);
    printf("\n\n");
    contarVotos(&distritos);

    return 0;
}

void contarVotos(struct distrito ** distritos){
    int cuentas[NO_CANDIDATOS];
    for (int j=0; j<NO_CANDIDATOS; j++){
        cuentas[j]= 0;
    }
    for(int i=0; i<NO_DISTRITOS; i++){
        for (int j=0; j<NO_CANDIDATOS; j++){
            cuentas[j] += *(((*distritos + i*sizeof(struct distrito) ) -> candidatosCuenta) + j*sizeof(int));
        }
    }
    for(int k=0; k<NO_CANDIDATOS;k++){
        printf("El candidato %d tiene cuenta de: %d\n", k+1, cuentas[k]);
    }
}

struct distrito capturarVotos(struct distrito ** distritos){
    int cuenta;

    for(int i=0; i<NO_DISTRITOS; i++){
        printf("*************************\nCAPTURANDO DISTRITO %d\n", i+1);
        for (int j=0; j<NO_CANDIDATOS; j++){
            printf("Ingresa cuenta del candidato %d: ", j+1);
            scanf("%d", &cuenta);
            *(((*distritos + i*sizeof(struct distrito) ) -> candidatosCuenta) + j*sizeof(int)) = cuenta;
        }
    }
    return **distritos;
}