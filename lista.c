#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

#define SIN_ERROR 0
#define ERROR -1

lista_t* lista_crear(){
    lista_t* lista = malloc(sizeof(lista_t));
    if(!lista)
        return NULL;
    lista->cantidad = 0;
    lista->nodo_inicio = NULL;
    lista->nodo_fin = NULL;
    return lista;
}

int lista_insertar(lista_t* lista, void* elemento){
    if(!lista)
        return ERROR;
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if(!nodo)
        return ERROR;
    nodo->elemento = elemento;
    nodo->siguiente = NULL;
    if(lista_vacia(lista)){
        lista->nodo_inicio = nodo;
        lista->nodo_fin = nodo;
    }else{
        lista->nodo_fin->siguiente = nodo;
        lista->nodo_fin = nodo;
    }
    lista->cantidad++;
    return SIN_ERROR;
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento , size_t posicion){
    if(!lista)
        return ERROR;
        
    if(posicion >= lista_elementos(lista) || lista_vacia(lista))
        return lista_insertar(lista, elemento);

    nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
    if(!nodo_nuevo)
        return ERROR;

    nodo_nuevo->elemento = elemento;

    if(posicion == 0){
        nodo_nuevo->siguiente = lista->nodo_inicio;
        lista->nodo_inicio = nodo_nuevo;
    }else{
        nodo_t* nodo_de_lista = lista->nodo_inicio;

        for(int i = 0; i < posicion - 1; i++){ 
            nodo_de_lista = nodo_de_lista->siguiente;
        }

        nodo_nuevo->siguiente = nodo_de_lista->siguiente;
        nodo_de_lista->siguiente = nodo_nuevo;
    }

    lista->cantidad++;    
    return SIN_ERROR;
}

int lista_borrar(lista_t* lista){
    if(!lista)
        return ERROR;
    if(lista_vacia(lista))
        return ERROR;

    if(lista_elementos(lista) > 1){
        nodo_t* nodo_de_lista = lista->nodo_inicio;
        for(int i = 0; i < lista_elementos(lista) - 2; i++){
            nodo_de_lista = nodo_de_lista->siguiente;
        }
        free(nodo_de_lista->siguiente);
        nodo_de_lista->siguiente = NULL;
        lista->nodo_fin = nodo_de_lista;
    } else{
        free(lista->nodo_inicio);
        lista->nodo_inicio = NULL;
        lista->nodo_fin = NULL;
    }

    lista->cantidad--;

    return SIN_ERROR;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
    if(!lista)
        return ERROR;
    if(lista_vacia(lista))
        return ERROR;
    
    if((posicion >= (lista_elementos(lista) - 1)) || (lista_elementos(lista)== 1))
        return lista_borrar(lista);

    if(posicion == 0){
        nodo_t* nodo_a_liberar = lista->nodo_inicio;
        lista->nodo_inicio = nodo_a_liberar->siguiente;
        free(nodo_a_liberar);
    } else {
        nodo_t* nodo_de_lista = lista->nodo_inicio;
        for(int i = 0; i < posicion - 1; i++){
            nodo_de_lista = nodo_de_lista->siguiente;
        }
        nodo_t* nodo_a_liberar = nodo_de_lista->siguiente;
        nodo_de_lista->siguiente = nodo_a_liberar->siguiente;
        free(nodo_a_liberar);
    }

    lista->cantidad--;
    
    return SIN_ERROR;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
    if(!lista)
        return NULL;
    if(lista_vacia(lista) || posicion >= lista_elementos(lista))
        return NULL;
    nodo_t* nodo_de_lista = lista->nodo_inicio;
    for(int i = 0; i < posicion; i++){
        nodo_de_lista = nodo_de_lista->siguiente;
    }
    return nodo_de_lista->elemento;
}

void* lista_ultimo(lista_t* lista){
    if(!lista)
        return NULL;
    if(lista_vacia(lista))
        return NULL;
    return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t* lista){
    return !lista || !lista_elementos(lista);
}

/*
* si la lista es nula devuelve 0
*/
size_t lista_elementos(lista_t* lista){
    if(!lista)
        return 0;
    return lista->cantidad;
}

int lista_apilar(lista_t* lista, void* elemento){
    return lista_insertar(lista, elemento);
}

int lista_desapilar(lista_t* lista){
    return lista_borrar(lista);
}

void* lista_tope(lista_t* lista){
    return lista_ultimo(lista);
}

int lista_encolar(lista_t* lista, void* elemento){
    return lista_insertar(lista, elemento);
}

int lista_desencolar(lista_t* lista){
    return lista_borrar_de_posicion(lista, 0);
}

void* lista_primero(lista_t* lista){
    return lista_elemento_en_posicion(lista, 0);
}

void lista_destruir(lista_t* lista){
    if(!lista)
        return;
    nodo_t* nodo_a_borrar = lista->nodo_inicio;
    nodo_t* nodo_aux;
    while(nodo_a_borrar){
        nodo_aux = nodo_a_borrar->siguiente;
        free(nodo_a_borrar);
        nodo_a_borrar = nodo_aux;
    }
    free(lista);
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){
    if(!lista)
        return NULL;
    lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
    if(!iterador)
        return NULL;
    iterador->lista = lista;
    iterador->corriente = lista->nodo_inicio;
    return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
    if(!iterador)
        return false;
    return iterador->corriente;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){
    if(!iterador)
        return false;

    if(!(iterador->corriente))
        return false;
    
    iterador->corriente = iterador->corriente->siguiente;
    return iterador->corriente;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
    if(!iterador)
        return NULL;
    if(!(iterador->corriente))
        return NULL;
    return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t* iterador){
    free(iterador);
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
    if(!lista || !funcion)
        return 0;
    size_t iteraciones = 0;
    nodo_t* nodo_actual = lista->nodo_inicio;
    bool iterar = true;
    while(nodo_actual && iterar){
        if((*funcion)(nodo_actual->elemento, contexto))
            nodo_actual = nodo_actual->siguiente;
        else 
            iterar = false;
        iteraciones++;
    }
    return iteraciones;
}