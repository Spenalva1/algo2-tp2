#ifndef __HEAP_H__
#define __HEAP_H__
#include <stdlib.h>

#define OK 0
#define ERROR -1

/*
 * Comparador de elementos. Recibe dos elementos del heap y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es menor al
 * segundo o -1 si el primer elemento es mayor al segundo.
 */
typedef int (*heap_comparador)(void*, void*);

/*
 * Destructor de elementos. Cada vez que un elemento deja el arbol
 * (arbol_borrar o arbol_destruir) se invoca al destructor pasandole
 * el elemento.
 */
typedef void (*heap_liberar_elemento)(void*);

typedef struct heap {
    void** vector;
    size_t tope;
    heap_comparador comparador;
    heap_liberar_elemento destructor;
}heap_t; 

/*
*   reserva la memoria para un heap cargando en él el comparador y destructor recibidos. Devuelve el puntero al heap creado
*   y devuelve NULL si no se pudo reservar la memoria
*/
heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor);

/*
*   aumenta la memoria reservada por el vector del heap para insertar el elemento recibido. Devuelve OK si pudo hacerlo o ERROR en caso contrario
*/
int heap_insertar_elemento(heap_t* heap, void* elemento);

/*
*   devuelve el elemento ubicado en la raiz del heap
*/
void* heap_obtener_raiz(heap_t* heap);

/*
*   reduce el tamaño en memoria del vector del heap quitando el elemento de la raiz. Devuelve OK si pudo hacerlo o ERROR en caso contrario
*/
int heap_quitar_raiz(heap_t* heap);

/*
*   devuelve la cantidad de elementos almacenados en el heap
*/
size_t heap_elementos(heap_t* heap);

/*
* Determina si el heap está vacío.
* Devuelve true si está vacío o el heap es NULL, false si el heap tiene elementos.
*/
int heap_vacio(heap_t* heap);

/*
*   libera la memoria ocupada por el heap
*/
void heap_destruir(heap_t* heap);

#endif /* __HEAP_H__ */