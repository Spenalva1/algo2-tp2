#ifndef __GIMNASIO_H__
#define __GIMNASIO_H__

#include "batallas.h"
#include "lista.h"
#include "heap.h"

#define MAX_NOMBRE 50
#define MAX_RUTA 100

typedef struct entrenador{
    char nombre[MAX_NOMBRE];
    lista_t* pokemones; //lista
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
gimnasio_t* gimnasio_crear(char ruta[MAX_RUTA]);

/*
*
*/
void gimnasio_destruir(gimnasio_t* gimnasio);

/*
*
*/
personaje_t* personaje_principal_crear(char ruta[MAX_RUTA]);

/*
*
*/
void personaje_principal_mostrar(personaje_t* personaje);

/*
*
*/
void personaje_principal_destruir(personaje_t* personaje);

/*
*
*/
funcion_batalla* batallas_cargar();

/*
*
*/
void batallas_destruir(funcion_batalla* funcion_batalla);

/*
*
*/
int elegir_pokemon_rival(lista_t* obtenidos, lista_t* pokemones_rival);

/*
*
*/
void cambiar_pokemon(personaje_t* personaje);

/*
*
*/
void entrenador_destruir(entrenador_t* entrenador);

/*
*
*/
void mejorar_pokemon(pokemon_t* pokemon);

/*
*
*/
void gimnasio_mostrar(gimnasio_t* gimnasio);

#endif /* __GIMNASIO_H__ */