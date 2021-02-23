#ifndef __POKEMON_H__
#define __POKEMON_H__

#include "batallas.h"

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
}pokemon_t;

void batallas_cargar(funcion_batalla* batallas);


#endif /* __POKEMON_H__ */