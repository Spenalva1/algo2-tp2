#ifndef __BATALLAS_H__
#define __BATALLAS_H__

#define MAX_NOMBRE 50
#define GANO_PRIMERO 1
#define GANO_SEGUNDO -1

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

/*
 * Se deberan implementar las 5 funciones de batalla.
 * Las reglas para decidir al ganador las inventan ustedes
 * 
 * Si el ganador es el primer pokemon, se devolvera 1
 * Si el ganador es el segundo pokemon, se devolvera -1
 * 
 * No habran empates.
 */

int funcion_batalla_1(void* pkm_1, void* pkm_2);

int funcion_batalla_2(void* pkm_1, void* pkm_2);

int funcion_batalla_3(void* pkm_1, void* pkm_2);

int funcion_batalla_4(void* pkm_1, void* pkm_2);

int funcion_batalla_5(void* pkm_1, void* pkm_2);


#endif /* __BATALLAS_H__ */