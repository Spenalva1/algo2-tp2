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

typedef struct juego{
    funcion_batalla* tipos_de_batallas;
    personaje_t* personaje_principal;
    heap_t* gimnasios;
    bool simular;
}juego_t;

/*
*
*/
void gimnasio_destruir(gimnasio_t* gimnasio);

/*
*
*/
void personaje_principal_mostrar(personaje_t* personaje);

/*
*
*/
funcion_batalla* batallas_cargar();

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

/*
*
*/
int agregar_gimnasio(heap_t* gimnasios);

/*
*
*/
int agregar_personaje(juego_t* juego);

/*
*
*/
void maestro_pokemon(juego_t* juego);

/*
*
*/
void mostrar_combate_informacion(pokemon_t* p1, pokemon_t* p2);

/*
*
*/
void terminar_juego(juego_t* juego);

#endif /* __GIMNASIO_H__ */