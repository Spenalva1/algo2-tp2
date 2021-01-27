#include "batallas.h"
#include <string.h>

int funcion_batalla_1(void* pkm_1, void* pkm_2){
    if( ((pokemon_t*)pkm_1)->velocidad >= ((pokemon_t*)pkm_2)->velocidad )
        return GANO_PRIMERO;
    return GANO_SEGUNDO;
}

int funcion_batalla_2(void* pkm_1, void* pkm_2){
    if( ((pokemon_t*)pkm_1)->ataque < ((pokemon_t*)pkm_2)->ataque )
        return GANO_SEGUNDO;
    return GANO_PRIMERO;
}

int funcion_batalla_3(void* pkm_1, void* pkm_2){
    if( ((pokemon_t*)pkm_1)->defensa >= ((pokemon_t*)pkm_2)->ataque )
        return GANO_PRIMERO;
    return GANO_SEGUNDO;
}

int funcion_batalla_4(void* pkm_1, void* pkm_2){
    int p1 = ((pokemon_t*)pkm_1)->velocidad + ((pokemon_t*)pkm_1)->ataque + ((pokemon_t*)pkm_1)->defensa;
    int p2 = ((pokemon_t*)pkm_2)->velocidad + ((pokemon_t*)pkm_2)->ataque + ((pokemon_t*)pkm_2)->defensa;
    if(p1 > p2)
        return GANO_PRIMERO;
    else if(p1 < p2)
        return GANO_SEGUNDO;
    else if(strlen(((pokemon_t*)pkm_1)->nombre) >= strlen(((pokemon_t*)pkm_2)->nombre))
        return GANO_PRIMERO;
    return GANO_SEGUNDO;
}

int funcion_batalla_5(void* pkm_1, void* pkm_2){
    if(strlen(((pokemon_t*)pkm_1)->nombre) >= strlen(((pokemon_t*)pkm_2)->nombre))
        return GANO_PRIMERO;
    return GANO_SEGUNDO;
}