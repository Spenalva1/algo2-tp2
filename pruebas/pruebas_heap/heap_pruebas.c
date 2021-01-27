#include "heap.h"
#include "pa2mm.h"

typedef struct gimnasio {
    char nombre;
    int dificultad;
}gimnasio_t;

int comparador(void* el1, void* el2) {
    if(((gimnasio_t*)el1)->dificultad < ((gimnasio_t*)el2)->dificultad)
        return 1;
    else if(((gimnasio_t*)el1)->dificultad > ((gimnasio_t*)el2)->dificultad)
        return -1;
    return 0;
}

void destructor(void* el) {
    if(el) free((gimnasio_t*)el);
}

int main(){

    pa2m_nuevo_grupo("Pruebas heap crear");
    heap_t* heap = heap_crear(NULL, NULL);
    pa2m_afirmar(heap == NULL, "Devuelve null si no recibe comparador válido");
    heap_destruir(heap);
    heap = heap_crear(comparador, NULL);
    pa2m_afirmar(heap, "Crea el heap aunque no reciba destructor");
    heap_destruir(heap);
    heap = heap_crear(comparador, destructor);
    pa2m_afirmar(heap, "Crea el heap recibiendo destructor");
    heap_destruir(heap);


    pa2m_nuevo_grupo("Pruebas heap insertar");
    heap = heap_crear(comparador, destructor);
    gimnasio_t* gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'G';
    gimnasio->dificultad = 7;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == OK, "Inserto 1 gimnasio");
    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'B';
    gimnasio->dificultad = 2;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == OK, "Inserto 2 gimnasio");
    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'E';
    gimnasio->dificultad = 5;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == OK, "Inserto 3 gimnasio");
    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'A';
    gimnasio->dificultad = 1;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == OK, "Inserto 4 gimnasio");
    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'F';
    gimnasio->dificultad = 6;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == OK, "Inserto 5 gimnasio");
    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'C';
    gimnasio->dificultad = 3;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == OK, "Inserto 6 gimnasio");
    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'D';
    gimnasio->dificultad = 4;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == OK, "Inserto 7 gimnasio");
    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'I';
    gimnasio->dificultad = 9;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == OK, "Inserto 7 gimnasio");
    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'J';
    gimnasio->dificultad = 10;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == OK, "Inserto 7 gimnasio");
    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'H';
    gimnasio->dificultad = 8;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == OK, "Inserto 7 gimnasio");
    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'L';
    gimnasio->dificultad = 12;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == OK, "Inserto 7 gimnasio");
    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'K';
    gimnasio->dificultad = 11;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == OK, "Inserto 7 gimnasio");
    gimnasio = calloc(1, sizeof(gimnasio_t));
    gimnasio->nombre = 'M';
    gimnasio->dificultad = 13;
    pa2m_afirmar(heap_insertar_elemento(heap, gimnasio) == OK, "Inserto 7 gimnasio");


    pa2m_nuevo_grupo("Pruebas heap obtener y quitar raiz");
    printf("Elementos quitados:\n");
    while(!heap_vacio(heap)){
        printf("Raiz -> %c\n", ((gimnasio_t*)heap_obtener_raiz(heap))->nombre);
        heap_quitar_raiz(heap);
    }


    heap_destruir(heap);
    return 0;
}