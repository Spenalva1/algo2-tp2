#include "heap.h"
#include <stdio.h> // BORRAR

/*
*   intercambia dos posiciones del vector recibido
*/
void swap(void** vector, size_t posicion_1, size_t posicion_2){
    void* aux = vector[posicion_1];
    vector[posicion_1] = vector[posicion_2];
    vector[posicion_2] = aux;
}

/*
*   retorna la posicion correspondiente al padre de la posicion recibida
*/
size_t posicion_padre(size_t posicion){
    return (posicion-1)/2;
}

/*
*   retorna la posicion correspondiente al hijo izquierdo de la posicion recibida
*/
size_t posicion_hijo_izquierdo(size_t posicion){
    return posicion*2+1;
}

/*
*   retorna la posicion correspondiente al hijo derecho de la posicion recibida
*/
size_t posicion_hijo_derecho(size_t posicion){
    return posicion*2+2;
}

/*
*   mueve el elemeno de la posicion recibida a su lugar correspondiente de acuerdo al comparador del heap
*/
void shift_up(heap_t* heap, size_t posicion){
    if(!heap || posicion >= heap->tope || posicion <= 0) return;
    size_t pos_padre = posicion_padre(posicion);
    int comparacion = heap->comparador(heap->vector[posicion], heap->vector[pos_padre]);
    if(comparacion == 1){
        swap(heap->vector, posicion, pos_padre);
        shift_up(heap, pos_padre);
    }
}

/*
*   mueve el elemeno de la posicion recibida a su lugar correspondiente de acuerdo al comparador del heap
*/ 
void shift_down(heap_t* heap, size_t posicion){
    if(!heap || heap_elementos(heap) < 2) return;
    size_t pos_izq = posicion_hijo_izquierdo(posicion);
    size_t pos_der = posicion_hijo_derecho(posicion);
    size_t pos_hijo_a_comparar = pos_izq;
    if(pos_izq >= heap->tope) return;
    int comparacion;
    if(pos_der < heap->tope) {
        comparacion = heap->comparador(heap->vector[pos_izq], heap->vector[pos_der]);
        if(comparacion == -1)
            pos_hijo_a_comparar = pos_der;        
    }
    comparacion = heap->comparador(heap->vector[posicion], heap->vector[pos_hijo_a_comparar]);
    if(comparacion == -1) {
        swap(heap->vector, posicion, pos_hijo_a_comparar);
        shift_down(heap, pos_hijo_a_comparar);
    }
}

heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor){
    if(!comparador) return NULL;
    heap_t* heap = calloc(1, sizeof(heap_t));
    if(heap){
        heap->comparador = comparador;
        heap->destructor = destructor;
    }
    return heap;
}

int heap_insertar_elemento(heap_t* heap, void* elemento){
    if(!heap) return ERROR;
    if(!heap->comparador) return ERROR;
    void* vector_aux;
    if(heap_elementos(heap) == 0){
        vector_aux = malloc(sizeof(void*));
    }else{
        vector_aux = realloc(heap->vector, sizeof(void*) * (heap->tope + 1));
    }
    if(!vector_aux) return ERROR;
    heap->tope++;
    heap->vector = vector_aux;
    heap->vector[heap->tope-1] = elemento;
    shift_up(heap, heap->tope-1);
    return OK;
}

void* heap_obtener_raiz(heap_t* heap){
    if(!heap || !heap->vector) return NULL;
    return heap->vector[0];
}

int heap_quitar_raiz(heap_t* heap){
    if(!heap || heap->tope <= 0) return ERROR;
    if(heap_elementos(heap) == 1){
        if(heap->destructor) heap->destructor((heap->vector[0]));
        free(heap->vector);
        heap->vector = NULL;
        heap->tope = 0;
    }else{
        void* ultimo = heap->vector[heap->tope-1];
        void* vector_aux = realloc(heap->vector, sizeof(void*) * (heap->tope - 1));
        if(!vector_aux) return ERROR;
        heap->vector = vector_aux;
        if(heap->destructor) heap->destructor((heap->vector[0]));
        heap->vector[0] = ultimo;
        heap->tope--;
        if(heap->tope > 1) shift_down(heap, 0);
    }
    return OK;
}

size_t heap_elementos(heap_t* heap){
    if(!heap) return 0;
    return heap->tope;
}

int heap_vacio(heap_t* heap){
    return !heap || heap->tope == 0;
}

void heap_destruir(heap_t* heap) {
    if(!heap) return;
    if(heap->destructor){
        while (heap->tope > 0){
            heap_quitar_raiz(heap);
        }        
    }
    free(heap);
}