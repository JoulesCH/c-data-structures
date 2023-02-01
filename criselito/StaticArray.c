#include <stdio.h>
#include <stdlib.h>

struct{
    int size;
    int *head;
}typedef array;

void init(array *a, int size){
    a->size = size;
    a->head = (int*)malloc(size * sizeof(int));
    printf("%d \n \n", a->size);
}

int main(){
    
    array a;

    init(&a, 27);

    printf("%d", a.size);
    

    return 0;
}