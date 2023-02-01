#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX(a,b) (((a)>(b))?(a):(b))

//forma de nodos del arbol
typedef struct nodo{
	int info;			//informacion del nodo
	nodo *hijo_izquierdo;
	nodo *hijo_derecho;
}NODO;

nodo* raiz;

//prototipos de funciones
NODO* Crear_nodo(int valor);
void Preorden(nodo* p);
void Enorden(nodo* p);
void Posorden(nodo* p);
NODO* buscar(nodo* p, int val);
int Size(nodo* p);
int altura(nodo* p);
void Insert(nodo*p, int val);
void Delete(NODO** p, int val);

int main(){
	NODO *p;
	p = (NODO*)malloc(sizeof(NODO));	//
	p->info = 120;
	p->hijo_derecho = NULL;				//iniciamos los apuntadores de hijos a null
	p->hijo_izquierdo = NULL;

	raiz = p;							//insertamos el nodo creado en la raiz


	printf("El valor de la raiz es: %d", raiz->info);

	NODO *s;

	s = Crear_nodo(96);				//Creamos un nodo por funci�n

	raiz->hijo_izquierdo = s;

	printf("\nEl valor del hijo izquierdo es %d",raiz->hijo_izquierdo->info);

	raiz->hijo_derecho = Crear_nodo(127);						//Creamos un nodo por funcion y lo insertamos por funci�n
	printf("\nEl valor del hijo derecho es %d",raiz->hijo_derecho->info);

	raiz->hijo_izquierdo->hijo_izquierdo = Crear_nodo(88);
	printf("\nEl valor del hijo izquierdo del hijo izquierdo es %d",raiz->hijo_izquierdo->hijo_izquierdo->info);

	raiz->hijo_izquierdo->hijo_derecho = Crear_nodo(107);
	printf("\nEl valor del hijo derecho del hijo izquierdo es %d",raiz->hijo_izquierdo->hijo_derecho->info);

	raiz->hijo_derecho->hijo_derecho = Crear_nodo(145);
	printf("\nEl valor del hijo derecho del hijo derecho es %d",raiz->hijo_derecho->hijo_derecho->info);

	printf("\nEl recorrido preorden es: ");
	Preorden(raiz);

	printf("\nEl recorrido Enorden es: ");
	Enorden(raiz);

	printf("\nEl recorrido Posorden es: ");
	Posorden(raiz);

	int val;
	printf("\nIngrese un valor para buscar en el arbol: ");
	fflush(stdin);
	scanf("%d",&val);

	p = buscar(raiz, val);

    fflush(stdin);
    printf("\nIngrese un nuevo valor para insertar en el arbol: ");
    scanf("%d", &val);

    Insert(raiz, val);


    for(int i=0; i<20; i++)
        Insert(raiz, rand()%200);
    
    printf("\nEl recorrido Enorden es: ");
	Enorden(raiz);

	printf("\nEl tama�o del arbol es: %d", Size(raiz));

	printf("\nLa altura del arbol es: %d", altura(raiz));

	fflush(stdin);

    printf("\nIngrese un nuevo valor para eliminar del arbol: ");
	scanf("%i",&val);

    Delete(&raiz, val);
    
    printf("\nEl recorrido Enorden es: ");
	Enorden(raiz);

    for(int i=0; i<20; i++)
        Delete(&raiz, rand()%200);
    printf("\nElimnacion aleatoria: ");
	Enorden(raiz);

    printf("\n");
    return 0;
}

void Delete(NODO** p, int val){  
    if (*p == NULL)
        printf("\nNodo no encontrado");
    else if((*p) -> info > val){
        Delete(&((*p)->hijo_izquierdo), val);
    }
    else if((*p)-> info < val ){
        Delete(&((*p)->hijo_derecho), val);
    }
    else{
        NODO *aux1;
        aux1 = *p;

        if(aux1->hijo_izquierdo == NULL)
            (*p) = aux1->hijo_derecho;
        else if(aux1 -> hijo_derecho == NULL)
            (*p) = aux1->hijo_izquierdo;
        else{
            NODO *aux2, *aux3;

            aux3 = aux1;
            aux2 = aux1->hijo_izquierdo;

            while(aux2->hijo_derecho!=NULL){
                aux3 = aux2;
                aux2 = aux2->hijo_derecho;
            }

            aux1->info=aux2->info;

            if(aux1==aux3)
                aux3->hijo_izquierdo=aux2->hijo_izquierdo;
            else
                aux3->hijo_derecho=aux2->hijo_izquierdo;

            aux1 = aux2;
        } 
        free(aux1);
    }
}


NODO* Crear_nodo(int valor){
	NODO* p = (NODO*)malloc(sizeof(NODO));
	p->info = valor;
	p->hijo_derecho = NULL;
	p->hijo_izquierdo = NULL;
	return p;
}

void Preorden(NODO* p){
    //Visitar Raiz
    printf("%d,  ",p->info);

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
    printf("%d, ", p->info);

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
    printf("%d, ",p->info);
}

NODO* buscar(nodo* p, int val){
	//utilizamos recorrido en preorden
	//Visitar raiz
	if(p->info == val){
		printf("\nNodo encontrado");
		return p;
	}
	else{
        NODO* aux;
        aux = NULL;
		if(p->hijo_izquierdo != NULL && p ->info > val)
			aux = buscar(p->hijo_izquierdo, val);
		else if(p->hijo_derecho != NULL && p ->info < val)
			aux = buscar(p->hijo_derecho,val);
        if(!aux)
            printf("\nNodo no encontrado");
        return aux;
	}
}

void Insert(nodo*p, int val){
    //utilizamos recorrido en preorden
	//Visitar raiz
	if(p->info == val){
		return;
	}
	else{
        NODO* aux;
        aux = NULL;
		if(p ->info > val)
            if(p->hijo_izquierdo != NULL )
			    Insert(p->hijo_izquierdo, val);
            else
                p->hijo_izquierdo = Crear_nodo(val);
		else 
            if(p->hijo_derecho != NULL )
			    Insert(p->hijo_derecho,val);
            else
                p->hijo_derecho = Crear_nodo(val);
        
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
