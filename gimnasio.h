#ifndef __GIMNASIO_H__
#define __GIMNASIO_H__

#include "batallas.h"
#include "lista.h"
#include "heap.h"

#define MAX_NOMBRE 50
#define MAX_RUTA 100

typedef struct entrenador{
    char nombre[MAX_NOMBRE];
    lista_t* pokemones; //cola
}entrenador_t;

typedef struct personaje{
    char nombre[MAX_NOMBRE];
    lista_t* pokemon_para_combatir; //lista
    lista_t* pokemon_obtenidos; //lista
}personaje_t;

typedef struct gimnasio{
    char nombre[MAX_NOMBRE];
    int dificultad;
    int id_puntero_funcion;
    entrenador_t* lider;
    lista_t* entrenadores; //pila
}gimnasio_t;

/*
*
*/
gimnasio_t* crear_gimnasio(char ruta[MAX_RUTA]);

/*
*
*/
personaje_t* crear_personaje_principal(char ruta[MAX_RUTA]);

#endif /* __GIMNASIO_H__ */