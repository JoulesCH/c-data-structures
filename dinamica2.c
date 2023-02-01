#include <stdio.h>
#include <stdlib.h>

struct arreglo_din{
    char* ptr; 
    int tam;
    int cap;

};

struct arreglo_din Push_Back(struct arreglo_din ar, char info);
void Extender_ar(struct arreglo_din *ar);
void imprimir_ar(struct arreglo_din ar);
struct arreglo_din Pop_Back(struct arreglo_din ar);
void Contraer_ar(struct arreglo_din * arr);
struct arreglo_din Push_Front(struct arreglo_din ar, char info);
struct arreglo_din Pop_Front(struct arreglo_din ar);
struct arreglo_din Insert(struct arreglo_din ar, char info, int pos);
struct arreglo_din Remove(struct arreglo_din ar, int pos);
struct arreglo_din Set(struct arreglo_din ar, char info, int pos);
char Get(struct arreglo_din ar, int pos);

int main(){

    struct arreglo_din letras = {NULL, 0,0};

    printf("Arreglo creado en la direccion %p de capacidad %d con tamanio %d", letras.ptr, letras.cap, letras.tam);
    char* p = (char*) malloc(4*sizeof(char));
    letras.ptr = p;
    letras.cap = 4;
    printf("\nArreglo creado en la direccion %p de capacidad %d con tamanio %d", letras.ptr, letras.cap, letras.tam);
    *letras.ptr = 'p';
    letras.tam++;
    printf("\nEl primer valor del arreglo es %c", *letras.ptr);
    
    // pushback
    *(letras.ptr + letras.tam * sizeof(char)) = 'A'; //Cargamos la letra A en la direccion del puntero inicial mas el tamanio
    letras.tam++;
    imprimir_ar(letras);

    *(letras.ptr + letras.tam * sizeof(char)) = 'B';
    letras.tam++;

    imprimir_ar(letras);
    //letras.tam = Push_Back(letras, 'C');
    letras = Push_Back( letras, 'C');
    imprimir_ar(letras);
    letras = Push_Back( letras, 'D');
    imprimir_ar(letras);
    letras = Push_Back( letras, 'F');
    imprimir_ar(letras);
    for (int n = 65; n<91; n++)
        letras = Push_Back( letras, n);

    printf("\n\nHaciendo 4 pop backs:");

    letras = Pop_Back(letras);
    letras = Pop_Back(letras);
    letras = Pop_Back(letras);
    letras = Pop_Back(letras);
    
    imprimir_ar(letras);

    printf("\n\nHaciendo 2 push fronts: ");

    letras = Push_Front( letras, 'F');
    imprimir_ar(letras);

    letras = Push_Front( letras, 'D');
    imprimir_ar(letras);
    
    printf("\n\nHaciendo 3 pop fronts: ");

    letras = Pop_Front(letras);
    letras = Pop_Front(letras);
    letras = Pop_Front(letras);
    imprimir_ar(letras);

    printf("\n\nInsertando t en la pos 2 dos veces: ");
    letras = Insert(letras, 't', 2);
    letras = Insert(letras, 't', 2);
    imprimir_ar(letras);

    printf("\n\nEliminando en la pos 4 dos veces: ");
    letras = Remove(letras,  4);
    letras = Remove(letras, 4);
    imprimir_ar(letras);

    printf("\n\nInsertando b en la pos 2: ");
    letras = Insert(letras, 'b', 2);
    imprimir_ar(letras);

    printf("\n\nObteniendo la pos 7: %c", Get(letras, 7));
    printf("\n");
    return 0;
}

void imprimir_ar(struct arreglo_din ar){
    printf("\n\nEl arreglo esta compuesto por: \n");
    printf("Tamanio %d, Capacidad %d \n", ar.tam, ar.cap);
    for(int n=0; n<ar.cap; n++){
        printf("%c,", *(ar.ptr + n*sizeof(char)) );
    }
}

struct arreglo_din Push_Back(struct arreglo_din ar, char info){
    //Verificar si hay 
    if(ar.tam == ar.cap){
        printf("\n\nCambiando capacidad de %d a %d", ar.cap, ar.cap*2);
        Extender_ar(&ar);
    }
    *(ar.ptr + ar.tam * sizeof(char)) = info;
    ar.tam++;
    return ar;
    
}

void Extender_ar(struct arreglo_din * arr){
    struct arreglo_din ar = *arr;
    char *p = (char*) malloc((ar.cap*2)* sizeof(char));
    
    for(int n=0; n<ar.cap;n++){
        *(p+n*sizeof(char)) = *(ar.ptr + n *sizeof(char));
    }

    ar.ptr = p;
    ar.cap = 2*ar.cap;

    *arr = ar;

}

struct arreglo_din Pop_Back(struct arreglo_din ar){
    
    ar.tam--;
    *(ar.ptr + ar.tam * sizeof(char)) = ' ';
    //Verificar si sobra mucho espacio
    if(ar.tam < ar.cap/2){
        printf("\n\nCambiando capacidad de %d a %d", ar.cap, ar.cap/2);
        Contraer_ar(&ar);
    }
    return ar;
    
}

void Contraer_ar(struct arreglo_din * arr){
    struct arreglo_din ar = *arr;
    char *p = (char*) malloc((ar.cap/2)* sizeof(char));
    
    for(int n=0; n<ar.tam;n++){
        *(p+n*sizeof(char)) = *(ar.ptr + n *sizeof(char));
    }

    ar.ptr = p;
    ar.cap = ar.cap/2;

    *arr = ar;

}

struct arreglo_din Push_Front(struct arreglo_din ar, char info){
    if(ar.tam == ar.cap){
        printf("\n\nCambiando capacidad de %d a %d", ar.cap, ar.cap*2);
        Extender_ar(&ar);
    }
    for(int n=ar.tam; n> 0 ;n--){
        *(ar.ptr + n * sizeof(char)) = *(ar.ptr + (n-1) * sizeof(char));
    }

    *ar.ptr = info;
    ar.tam++;
    return ar;

}
struct arreglo_din Pop_Front(struct arreglo_din ar){

    for(int n=0; n< ar.tam ;n++){
        *(ar.ptr + n * sizeof(char)) = *(ar.ptr + (n+1) * sizeof(char));
    }
    ar.tam--;
    //ar.ptr = ar.ptr + sizeof(char);
    

    if(ar.tam < ar.cap/2){
        printf("\n\nCambiando capacidad de %d a %d", ar.cap, ar.cap/2);
        Contraer_ar(&ar);
    }
    return ar;
}

struct arreglo_din Insert(struct arreglo_din ar, char info, int pos){
    if(ar.tam == ar.cap){
        printf("\n\nCambiando capacidad de %d a %d", ar.cap, ar.cap*2);
        Extender_ar(&ar);
    }

    for(int n=ar.tam; n> pos ;n--){
        *(ar.ptr + n * sizeof(char)) = *(ar.ptr + (n-1) * sizeof(char));
    }

    *(ar.ptr + pos * sizeof(char)) = info;
    ar.tam ++;
    return ar;

}
struct arreglo_din Remove(struct arreglo_din ar, int pos){
    for(int n=pos; n< ar.tam ;n++){
        *(ar.ptr + n * sizeof(char)) = *(ar.ptr + (n+1) * sizeof(char));
    }

    ar.tam--;
    if(ar.tam < ar.cap/2){
        printf("\n\nCambiando capacidad de %d a %d", ar.cap, ar.cap/2);
        Contraer_ar(&ar);
    }
    return ar;
}
struct arreglo_din Set(struct arreglo_din ar, char info, int pos){
        *(ar.ptr + pos* sizeof(char)) = info;
    return ar;
}
char Get(struct arreglo_din ar, int pos){

    return *(ar.ptr + pos*sizeof(char));
}