#include "abb.h"
#include <stdio.h>

#define ERROR -1
#define SIN_ERROR 0
#define CARGAR_EN_VECTOR 0
#define ITERAR_CON_FUNCION 0

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
    if(!comparador)
        return NULL;
    abb_t* abb = calloc(1, sizeof(abb_t));
    if(!abb)
        return NULL;
    abb->comparador = comparador;
    abb->destructor = destructor;
    return abb;
}

/*
*   crea un nodo_abb_t que apuntara al elemento recibido y tendra de hijos a izquierda y derecha.
*/
nodo_abb_t* crear_nodo(void* elemento, nodo_abb_t* izquierda, nodo_abb_t* derecha){
    nodo_abb_t* nodo = calloc(1, sizeof(nodo_abb_t));
    if(!nodo)
        return NULL;
    nodo->elemento = elemento;
    nodo->derecha = derecha;
    nodo->izquierda = izquierda;
    return nodo;
}

/*
*   busca recursivamente la posicion para insertar el nodo recibido (Se respetará el orden de la función comparar) y lo inserta
*/
nodo_abb_t* insertar_nodo(nodo_abb_t* nodo, abb_comparador comparador, void* elemento){
    if(!comparador)
        return NULL;
    if(!nodo){
        return crear_nodo(elemento, NULL, NULL);
    }
    nodo_abb_t* nodo_aux;
    int comparacion = comparador(nodo->elemento, elemento);
    if(comparacion < 0){
        nodo_aux = insertar_nodo(nodo->derecha, comparador, elemento);
        if(!nodo_aux)
            return NULL;
        nodo->derecha = nodo_aux;
    }else{
        nodo_aux = insertar_nodo(nodo->izquierda, comparador, elemento);
        if(!nodo_aux)
            return NULL;
        nodo->izquierda = nodo_aux;
    }
    return nodo;
}

int arbol_insertar(abb_t* arbol, void* elemento){
    if(!arbol || !(arbol->comparador))
        return ERROR;
    nodo_abb_t* nueva_raiz = insertar_nodo(arbol->nodo_raiz, arbol->comparador, elemento);
    if(!nueva_raiz)
        return ERROR;
    arbol->nodo_raiz = nueva_raiz;
    return SIN_ERROR;
}

/*
*   libera el espacio en memoria ocupado por un nodo que no tenga hijos
*/
nodo_abb_t* borrar_sin_hijos(nodo_abb_t* nodo, abb_liberar_elemento destructor){
    if(destructor)
        destructor(nodo->elemento);
    free(nodo);
    return NULL;
}

/*
*   libera el espacio en memoria ocupado por un nodo que tenga un hijo. Retorna el puntero al hijo para que 
*   ocupe la posicion de su anterior padre 
*/
nodo_abb_t* borrar_con_un_hijo(nodo_abb_t* nodo, abb_liberar_elemento destructor){
    nodo_abb_t* hijo = nodo->izquierda ? nodo->izquierda : nodo->derecha;
    if(destructor)
        destructor(nodo->elemento);
    free(nodo);
    return hijo;
}

/*
*   libera el espacio en memoria ocupado por un nodo que tenga dos hijos. Se encarga de ocupar la posicion del 
*   nodo por el mayor de los menores (el que esté más a la derecha a la izquierda del nodo recibido) para conservar
*   el orden del ABB. Retorna el puntero al nodo que remplazará al borrado
*/
nodo_abb_t* borrar_con_dos_hijos(nodo_abb_t* nodo, abb_liberar_elemento destructor){
    nodo_abb_t* nodo_aux = nodo->izquierda;
    nodo_abb_t* nodo_a_recolocar = nodo_aux->derecha;
    if(nodo_a_recolocar){
        while(nodo_a_recolocar->derecha){
            nodo_aux = nodo_a_recolocar;
            nodo_a_recolocar = nodo_a_recolocar->derecha;
        }
        nodo_aux->derecha = nodo_a_recolocar->izquierda ? nodo_a_recolocar->izquierda : NULL;
        nodo_a_recolocar->izquierda = nodo->izquierda;
        nodo_a_recolocar->derecha = nodo->derecha;
    }else{
        nodo_a_recolocar = nodo_aux;
        nodo_a_recolocar->derecha = nodo->derecha;
    }
    if(destructor)
        destructor(nodo->elemento);
    free(nodo);
    return nodo_a_recolocar;
}

/*
*   busca el nodo cuyo elemento coincida con el elemento recibido y se encarga de borrarlo, liberando 
*   la memoria.
*/
nodo_abb_t* borrar_nodo(nodo_abb_t* nodo, abb_comparador comparador, abb_liberar_elemento destructor, void* elemento, bool* elemento_borrado){
    if(!comparador || !nodo)
        return NULL;
    int comparacion = comparador(nodo->elemento, elemento);
    if(comparacion < 0){
        nodo->derecha = borrar_nodo(nodo->derecha, comparador, destructor, elemento, elemento_borrado);
    }else if(comparacion > 0){
        nodo->izquierda = borrar_nodo(nodo->izquierda, comparador, destructor, elemento, elemento_borrado);
    } else {
        *elemento_borrado = true;
        if(nodo->izquierda && nodo->derecha){
            return borrar_con_dos_hijos(nodo, destructor);
        } else if (nodo->izquierda || nodo->derecha){
            return borrar_con_un_hijo(nodo, destructor);
        } else {
            return borrar_sin_hijos(nodo, destructor);
        }
    }
    return nodo;
}

int arbol_borrar(abb_t* arbol, void* elemento){
    if(arbol_vacio(arbol) || !(arbol->comparador))
        return ERROR;
    bool elemento_borrado = false;
    arbol->nodo_raiz = borrar_nodo(arbol->nodo_raiz, arbol->comparador, arbol->destructor, elemento, &elemento_borrado);
    return (elemento_borrado) ? SIN_ERROR : ERROR;
}

/*
*   Busca el nodo cuyo elemento coincida con elemento recibido y retorna el elemento almacenado en él
*/
void* buscar_nodo(nodo_abb_t* nodo, abb_comparador comparador, void* elemento){
    if(!nodo || !comparador)
        return NULL;
    int comparacion = comparador(nodo->elemento, elemento);
    if(comparacion < 0)
        return buscar_nodo(nodo->derecha, comparador, elemento);
    else if (comparacion > 0)
        return buscar_nodo(nodo->izquierda, comparador, elemento);
    return nodo->elemento;
}

void* arbol_buscar(abb_t* arbol, void* elemento){
    if(!arbol || !(arbol->comparador))
        return NULL;
    return buscar_nodo(arbol->nodo_raiz, arbol->comparador, elemento);
}

void* arbol_raiz(abb_t* arbol){
    if(!arbol || !(arbol->nodo_raiz))
        return NULL;
    return arbol->nodo_raiz->elemento;
}

bool arbol_vacio(abb_t* arbol){
    return (!arbol || !(arbol->nodo_raiz));
}

void destruir_nodos(nodo_abb_t* nodo, abb_liberar_elemento destructor){
    if(!nodo)
        return;
    destruir_nodos(nodo->izquierda, destructor);
    destruir_nodos(nodo->derecha, destructor);
    if(destructor)
        destructor(nodo->elemento);
    free(nodo);
}

void arbol_destruir(abb_t* arbol){
    if(!arbol)
        return;
    destruir_nodos(arbol->nodo_raiz, arbol->destructor);
    free(arbol);
}

/*
*   Inserta en el array recibi los elementos guardados en el arbol, de forma inorden
*/
void insertar_nodos_inorden(nodo_abb_t* nodo, void** array, size_t tamanio_array, size_t* elementos_insertados){
    if(!nodo || *elementos_insertados >= tamanio_array)
        return;
    insertar_nodos_inorden(nodo->izquierda, array, tamanio_array, elementos_insertados);
    if(*elementos_insertados < tamanio_array){
        array[*elementos_insertados] = nodo->elemento;
        (*elementos_insertados)++;
    }
    insertar_nodos_inorden(nodo->derecha, array, tamanio_array, elementos_insertados);
}

/*
*   Inserta en el array recibi los elementos guardados en el arbol, de forma preorden
*/
void insertar_nodos_preorden(nodo_abb_t* nodo, void** array, size_t tamanio_array, size_t* elementos_insertados){
    if(!nodo || *elementos_insertados >= tamanio_array)
        return;
    array[*elementos_insertados] = nodo->elemento;
    (*elementos_insertados)++;
    insertar_nodos_preorden(nodo->izquierda, array, tamanio_array, elementos_insertados);
    insertar_nodos_preorden(nodo->derecha, array, tamanio_array, elementos_insertados);
}

/*
*   Inserta en el array recibi los elementos guardados en el arbol, de forma postorden
*/
void insertar_nodos_postorden(nodo_abb_t* nodo, void** array, size_t tamanio_array, size_t* elementos_insertados){
    if(!nodo || *elementos_insertados >= tamanio_array)
        return;
    insertar_nodos_postorden(nodo->izquierda, array, tamanio_array, elementos_insertados);
    insertar_nodos_postorden(nodo->derecha, array, tamanio_array, elementos_insertados);
    if(*elementos_insertados < tamanio_array){
        array[*elementos_insertados] = nodo->elemento;
        (*elementos_insertados)++;
    }
}

/*
*   Inserta en el array recibido los elementos almacenados en el arbol de la forma recibida en "recorrido".
*   retorna la cantidad de elementos iterados
*/
size_t recorridos(abb_t* arbol, void** array, size_t tamanio_array, int recorrido){
    if(arbol_vacio(arbol) || !array || tamanio_array == 0)
        return 0;
    size_t elementos_insertados = 0;
    if(recorrido == ABB_RECORRER_INORDEN)
        insertar_nodos_inorden(arbol->nodo_raiz, array, tamanio_array, &elementos_insertados);
    else if(recorrido == ABB_RECORRER_PREORDEN)
        insertar_nodos_preorden(arbol->nodo_raiz, array, tamanio_array, &elementos_insertados);
    else if(recorrido == ABB_RECORRER_POSTORDEN)
        insertar_nodos_postorden(arbol->nodo_raiz, array, tamanio_array, &elementos_insertados);
    return elementos_insertados;
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
    return recorridos(arbol, array, tamanio_array, ABB_RECORRER_INORDEN);
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
    return recorridos(arbol, array, tamanio_array, ABB_RECORRER_PREORDEN);
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
    return recorridos(arbol, array, tamanio_array, ABB_RECORRER_POSTORDEN);
}

/*
*   Recorre los elementos del arbol de forma inorden llamando la función recibida con cada uno de ellos
*   Retorna true o false dependiendo lo que retorne la función llamada.
*/
bool iterar_nodos_inorden(nodo_abb_t* nodo, bool (*fn) (void*, void*), void* extra, size_t* iteraciones){
    if(!nodo)
        return false;
    bool parar_de_iterar = iterar_nodos_inorden(nodo->izquierda, fn, extra, iteraciones);
    if(!parar_de_iterar){
        parar_de_iterar = (*fn)(nodo->elemento, extra);
        (*iteraciones)++;
    }
    if(!parar_de_iterar){
        parar_de_iterar = iterar_nodos_inorden(nodo->derecha, fn, extra, iteraciones);
    }
    return parar_de_iterar;
}

/*
*   Recorre los elementos del arbol de forma preorden llamando la función recibida con cada uno de ellos
*   Retorna true o false dependiendo lo que retorne la función llamada.
*/
bool iterar_nodos_preorden(nodo_abb_t* nodo, bool (*fn) (void*, void*), void* extra, size_t* iteraciones){
    if(!nodo)
        return false;
    bool parar_de_iterar = (*fn)(nodo->elemento, extra);
    (*iteraciones)++;
    if(!parar_de_iterar){
        parar_de_iterar = iterar_nodos_preorden(nodo->izquierda, fn, extra, iteraciones);
    }
    if(!parar_de_iterar){
        parar_de_iterar = iterar_nodos_preorden(nodo->derecha, fn, extra, iteraciones);
    }
    return parar_de_iterar;
}

/*
*   Recorre los elementos del arbol de forma post llamando la función recibida con cada uno de ellos
*   Retorna true o false dependiendo lo que retorne la función llamada.
*/
bool iterar_nodos_postorden(nodo_abb_t* nodo, bool (*fn) (void*, void*), void* extra, size_t* iteraciones){
    if(!nodo)
        return false;
    bool parar_de_iterar = iterar_nodos_postorden(nodo->izquierda, fn, extra, iteraciones);
    if(!parar_de_iterar){
        parar_de_iterar = iterar_nodos_postorden(nodo->derecha, fn, extra, iteraciones);
    }
    if(!parar_de_iterar){
        parar_de_iterar = (*fn)(nodo->elemento, extra);
        (*iteraciones)++;
    }
    return parar_de_iterar;
}

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido , bool (*fn) (void*, void*), void* extra){
    if(arbol_vacio(arbol) || !fn)
        return 0;
    size_t iteraciones = 0;
    if(recorrido == ABB_RECORRER_INORDEN)
        iterar_nodos_inorden(arbol->nodo_raiz, fn, extra, &iteraciones);
    else if(recorrido == ABB_RECORRER_PREORDEN)
        iterar_nodos_preorden(arbol->nodo_raiz, fn, extra, &iteraciones);
    else if(recorrido == ABB_RECORRER_POSTORDEN)
        iterar_nodos_postorden(arbol->nodo_raiz, fn, extra, &iteraciones);
    return iteraciones;
}