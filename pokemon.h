#ifndef __POKEMON_H__
#define __POKEMON_H__

#include <stdbool.h>
#include "batallas.h"
#include "lista.h"

#define MAX_NOMBRE 50
#define CANT_BATALLAS 5

/*
*   devuelve 1 si el ganador de la batalla es el primer pokemon, y -1 en caso contrario
*/
typedef int (*funcion_batalla)(void*, void*);

typedef struct pokemon{
    char nombre[MAX_NOMBRE];
    int velocidad;
    int defensa;
    int ataque;
    int bonificaciones;
}pokemon_t;

void batallas_cargar(funcion_batalla* batallas);

/*
*   mejora cada habilidad del pokemon recibido si su bonificaciones es menor a 63
*/
void mejorar_pokemon(pokemon_t* pokemon);

/*
*   devuelve true su el pokemon recivido se encuentra en la lista de pokemones. Devuelve false en caso contrario
*/
bool cambio_valido(lista_t* pokemones, pokemon_t* pokemon);

/*
*   lista en pantalla los pokemones del entrenador recibido (pokemones_rival) y permite al usuario elegir uno de ellos
*   para insertarlo en la lista de obtenidos recivida. Si al elegir un pokemon ocurre un error, devuelve ERROR. En caso
*   contrario devuelve OK
*/
int elegir_pokemon_rival(lista_t* obtenidos, lista_t* pokemones_rival);

bool mostrar_pokemon(void* pokemon, void* contador);

bool mostrar_pokemon_con_id(void* pokemon, void* contador);

#endif /* __POKEMON_H__ */