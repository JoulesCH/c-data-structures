#include<stdio.h>
#include<stdlib.h>

//macros para usar true y false
#define False 0
#define True 1

//variable globar para capital
float capital = 2000;

//typedef de la estructura del arreglo
typedef struct ARREGLO{
    float *precios;
    int tamanio;
    int capacidad;
}arreglo;

//prototipos de funciones
float* extender_ar(float *ar, int capacidad);
void imprimir_ar(ARREGLO ar);
int compra(arreglo punteroPrecios, int accion_comprada, float *comprado, int ultima, float *capital_ant);
float promedio(arreglo punteroPrecios);
void alza(arreglo punteroPrecios, int *a, int tamanio);
void baja(arreglo punteroPrecios, int *b, int tamanio);

int main(){
    //apertura de archivo
    FILE *archivo = NULL;
    archivo = fopen("GOOGL.txt","r");
    if(archivo==NULL){
        printf("Archivo no encontrado");
        exit(1);
    }


    float actual;
    int accion_comprada = False;
    float comprado = 0;
    int ultima = False;
    float alza =0, baja=0;
    float capital_ant = 0;

    //Creacion de arreglo dinamico con capacidad para 2 elementos
    arreglo acciones_leidas = {NULL, 0, 2};
    acciones_leidas.precios = (float*)calloc(2,sizeof(float));
    if (acciones_leidas.precios==NULL){
        printf("Memoria no separada");
        exit(1);
    }

    printf("Compra\t  \Capital\t  venta\t\t  Capital\t  Ganancia\n");

    //Do-while donde se van leyendo los valores del archivo uno por uno y se realizan criterios para la desicion de compra
    do{
        //Evaluacion y aumento del arreglo en caso de ser necesario
        if(acciones_leidas.capacidad == acciones_leidas.tamanio){
            acciones_leidas.precios = extender_ar(acciones_leidas.precios, acciones_leidas.capacidad);
            acciones_leidas.capacidad *= 2;
        }

        //Lectura del siguiente elemento del archivo
        fscanf(archivo,"%f",&actual);
        *(acciones_leidas.precios+acciones_leidas.tamanio) = actual;

        //Evaluamos si es el ultimo elemento del archivo
        if(feof(archivo))
            ultima = True;

        //llamamos a la función donde se evalua si realizar o no una compra
        accion_comprada = compra(acciones_leidas, accion_comprada, &comprado, ultima, &capital_ant);
        acciones_leidas.tamanio++;

    }while(!feof(archivo));

    printf("\nCapital final: %.2f",capital);

}//fin

//Función para hacer más grande el arreglo, recibe como parametros la posición inicial del arreglo dinamico y su capacidad
float* extender_ar(float *ar, int capacidad){

    //uso de puntero auxiliar
	float *aux = (float *) calloc(capacidad * 2,sizeof(float)); //Reservamos memoria de nuevo tamaño

    //Reasignación de los elementos del arreglo en uno más grande
	for(int n=0; n<capacidad; n++){
		*(aux+n)=*(ar+n);
	}

	//liberacion de la memoria ocupada por el arreglo anterior y devolvemos la dirección del nuevo arreglo
	free(ar);
    return aux;
}

//Funcion que evalua si los costos estan en alza
void alza(arreglo punteroPrecios, int *a, int tamanio){

    //Si el precio actual es mayor que el anterior realizamos recursividad para evaluar el anterior con el anteanterior
    if(*(punteroPrecios.precios+tamanio) > *(punteroPrecios.precios+(tamanio-1))){
        alza(punteroPrecios, a, tamanio-1);

        //cuando nos encontramos con un precio menor que el anterior aumentamos la variable en 1, en caso de nunca encontraros la variable vale 0
        *a = *a +1;
    }

}

//Funcion que evalua si los costos estan en baja
void baja(arreglo punteroPrecios, int *b, int tamanio){

    //Si el precio actual es menor que el anterior realizamos recursividad para evaluar el anterior con el anteanterior
    if(*(punteroPrecios.precios+tamanio) < *(punteroPrecios.precios+(tamanio-1)))
        baja(punteroPrecios, b, tamanio-1);

        //cuando nos encontramos con un mayor menor que el anterior aumentamos la variable en 1, en caso de nunca encontraros la variable vale 0
        *b = *b+1;

}

//Funcion que decide si comprar
int compra(arreglo punteroPrecios, int accion_comprada, float *comprado, int ultima, float *capital_ant){

    //variables para registrar cuantas veces a subido o bajado el precio
    int al=0, ba=0;

    //llamamos a las funciones para calcular las subidas y bajadas de costos
    alza(punteroPrecios, &al, punteroPrecios.tamanio);
    baja(punteroPrecios, &ba, punteroPrecios.tamanio);

    //Si no hemos comprado ninguna accion, la accion ha estado en descenso compramos y ademas no es el ultimo elemento del archivo compramos
    if ((accion_comprada == False) && (ba>al) && (ultima != True)){
        //Guardamos el capital antes de la compra para hacer una comparativa de ganancia despues
        *capital_ant = capital;

        //Restamos el costo del capital global
        capital -= *(punteroPrecios.precios+punteroPrecios.tamanio);

        //Guardamos el costo de compra para evaluar en el criterio de venta
        *comprado = *(punteroPrecios.precios+punteroPrecios.tamanio);

        printf("%.2f\t  %.2f\t",*comprado,capital);


        //Retornamos que se ha comprado una accion
        return True;
    }

    /*
    Si previamente hemos comprado accion, la acción acaba de cambiar de subida a bajada, el precio esta entre el precio comprado o -%45 vendemos
    o
    Si previamente hemos comprado y es el ultimo elemento del archivo vendemos
    */
    if ((accion_comprada == True) && ((al<ba) && ((*(punteroPrecios.precios+punteroPrecios.tamanio) > (*comprado-*comprado/45))) || (ultima == True)) ){

        //Aumentamos el capital con el precio de venta
        capital += *(punteroPrecios.precios+punteroPrecios.tamanio);

        //Actualizamos en 0 el precio de compra porque ya no tenemos una accion
        *comprado = 0;
        printf("  %.2f\t  %.2f\t  %.2f\n",*(punteroPrecios.precios+punteroPrecios.tamanio), capital, capital-*capital_ant);

        //retornamos que no tenemos una accion en nuestro poder
        return False;
    }

    //En caso de realizar ninguna operación retornamos la misma situacion en cuanto a poseer acciones
    return accion_comprada;
}
