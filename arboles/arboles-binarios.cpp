#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX(a,b) (((a)>(b))?(a):(b))

//forma de nodos del arbol
typedef struct nodo{
	char info;			//informacion del nodo
	nodo *hijo_izquierdo;
	nodo *hijo_derecho;
}NODO;

nodo* raiz;

//prototipos de funciones
NODO* Crear_nodo(char valor);
void Preorden(nodo* p);
void Enorden(nodo* p);
void Posorden(nodo* p);
NODO* buscar(nodo* p, char val);
int Size(nodo* p);
int altura(nodo* p);

int main(){
	NODO *p;
	p = (NODO*)malloc(sizeof(NODO));	//
	p->info = 'A';
	p->hijo_derecho = NULL;				//iniciamos los apuntadores de hijos a null
	p->hijo_izquierdo = NULL;

	raiz = p;							//insertamos el nodo creado en la raiz


	printf("El valor de la raiz es: %c", raiz->info);

	NODO *s;

	s = Crear_nodo('B');				//Creamos un nodo por funci�n

	raiz->hijo_izquierdo = s;

	printf("\nEl valor del hijo izquierdo es %c",raiz->hijo_izquierdo->info);

	raiz->hijo_derecho = Crear_nodo('C');						//Creamos un nodo por funcion y lo insertamos por funci�n
	printf("\nEl valor del hijo derecho es %c",raiz->hijo_derecho->info);

	raiz->hijo_izquierdo->hijo_izquierdo = Crear_nodo('D');
	printf("\nEl valor del hijo izquierdo del hijo izquierdo es %c",raiz->hijo_izquierdo->hijo_izquierdo->info);

	raiz->hijo_izquierdo->hijo_derecho = Crear_nodo('E');
	printf("\nEl valor del hijo derecho del hijo izquierdo es %c",raiz->hijo_izquierdo->hijo_derecho->info);

	raiz->hijo_derecho->hijo_derecho = Crear_nodo('F');
	printf("\nEl valor del hijo derecho del hijo derecho es %c",raiz->hijo_derecho->hijo_derecho->info);

	printf("\nEl recorrido preorden es: ");
	Preorden(raiz);

	printf("\nEl recorrido Enorden es: ");
	Enorden(raiz);

	printf("\nEl recorrido Posorden es: ");
	Posorden(raiz);

	char val;
	printf("\nIngrese un valor para buscar en el arbol: ");
	fflush(stdin);
	scanf("%c",&val);

	p = buscar(raiz, val);

	printf("\nEl tama�o del arbol es: %d", Size(raiz));

	printf("\nLa altura del arbol es: %d", altura(raiz));

    
	return 0;
}


NODO* Crear_nodo(char valor){
	NODO* p = (NODO*)malloc(sizeof(NODO));
	p->info = valor;
	p->hijo_derecho = NULL;
	p->hijo_izquierdo = NULL;
	return p;
}

void Preorden(NODO* p){
    //Visitar Raiz
    printf("%c,  ",p->info);

    //Recorrer subarbor izquierdo
    if(p->hijo_izquierdo != NULL)
        Preorden(p->hijo_izquierdo);

    //Recorrer subarbol Derecho
    if(p->hijo_derecho != NULL)
        Preorden(p->hijo_derecho);
}

void Enorden(nodo* p){
    //Recorrer el arbol subarbol izquierdo
    if(p->hijo_izquierdo != NULL)
        Enorden(p->hijo_izquierdo);

    //Visitar raiz
    printf("%c, ", p->info);

    //Recorrer subarbol derecho
    if(p->hijo_derecho != NULL)
        Enorden(p->hijo_derecho);
}

void Posorden(nodo* p){
    //recorrer subarbol izquierto
    if(p->hijo_izquierdo != NULL)
        Posorden(p->hijo_izquierdo);

    //recorrer subarbol derecho
    if(p->hijo_derecho != NULL)
        Posorden(p->hijo_derecho);

    //visitar raiz
    printf("%c, ",p->info);
}

NODO* buscar(nodo* p, char val){
	//utilizamos recorrido en preorden
	//Visitar raiz
	if(p->info == val){
		printf("\nNodo encontrado!");
		return p;
	}
	else{
        NODO* aux;
        aux = NULL;
		if(p->hijo_izquierdo != NULL)
			aux = buscar(p->hijo_izquierdo, val);
		if(aux == NULL && p->hijo_derecho != NULL)
			aux = buscar(p->hijo_derecho,val);
        return aux;
	}
}

int Size(nodo* p){
    //Se pueden usar cualquiera de los 3 recorridos
    //se selecciona Enorden
    int contador=0; //Declaramos una variable para contar los nodos

    //Recorremos subarbol izquierdo
    if(p->hijo_izquierdo != NULL){
        contador += Size(p->hijo_izquierdo);
    }
    //Visitamos Raiz
    contador++; //sumamos 1 para contar el nodo en el estamos actualmente

    //Recorremos subarbol derecho
    if(p->hijo_derecho != NULL)
        contador +=Size(p->hijo_derecho);

    return contador; //Regresamos el tama�o de este subarbol
}

int altura(nodo* p){
    //Se pueden utilizar cualquiera de los 3 recorridos
    //Se selecciona preorden

    //visitar raiz
    int Hi, Hd; //Decramos una variable para cargar la altura
    Hi = 0;
    Hd = 0;

    //Recorrer Subarbor izquierdo
    if(p->hijo_izquierdo != NULL)
        Hi = altura(p->hijo_izquierdo);

    //Recorrer subarbor derecho
    if(p->hijo_derecho != NULL)
        Hd = altura(p->hijo_derecho);

    return MAX(Hi,Hd)+1;
}
