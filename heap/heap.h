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
*
*/
heap_t* heap_crear(heap_comparador comparador, heap_liberar_elemento destructor);

/*
*
*/
int heap_insertar_elemento(heap_t* heap, void* elemento);

/*
*
*/
void* heap_obtener_raiz(heap_t* heap);

/*
*
*/
int heap_quitar_raiz(heap_t* heap);

/*
 * Determina si el heap está vacío.
 * Devuelve true si está vacío o el heap es NULL, false si el árbol tiene elementos.
 */
int heap_vacio(heap_t* heap);

/*
*
*/
void heap_destruir(heap_t* heap);

#endif /* __HEAP_H__ */