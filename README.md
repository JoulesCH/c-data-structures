# Estructuras de datos

## Tipo de Organización de un TDA

- Lineal
- Jerárquica
- Red
- Sin relación

## Operaciones
![img](./static/O.png)

## Niveles de Abstracción de Datos

- Nivel Lógico o Abstracto
    - La estructura de datos y las operaciones entre los datos. Deja de lado el lenguaje de programación.
- Nivel Físico o de Implementación
    - En este nivel se define el lenguaje de programaicón que se utilizará y los tipos de datos que se tomarán en cuenta.
- Nivel de Uso o Aplicación

## Diseño de Algoritmos
- Diseño
- Prototipo
- Pruebas

## Asignación dinámica de Memoria
![img](./static/dinamica.png)

Función Memory Allocation: crea nueva memoria
```
tipo *puntero;
puntero = (tipo*) malloc(tamaño en bytes)
```

```c
int *r;
r = (int*)malloc(6*sizeof(int))
```
![img](./static/r.png)

```
Función Free Memory: libera memoria.
free(puntero);
```
Función C Allocation: crea nueva memoria
```
tipo *puntero;
puntero = (tipo*) calloc(número de los elementos, tamaño de cada elemento en bytes)
```

```c
int *r;
r = (int *)calloc(6, sizeof(int)):
```

Función Reallocation: modifica memoria creda.
```
tipo ¨*puntero;
puntero = (tipo*)realloc(puntero a bloque, tamaño total nuevo bloque);
```

```C
AUTOMOVIL *r;
r = (AUTOMOVIL*)malloc(n*sizeof(AUTOMOVIL));
r = (AUTOMOVIL*)realloc(r, (n+1)*sizeof(AUTOMOVIL));
```
