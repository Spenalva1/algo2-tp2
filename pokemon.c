#include "pokemon.h"

void batallas_cargar(funcion_batalla* batallas){
    batallas[0] = &funcion_batalla_1;
    batallas[1] = &funcion_batalla_2;
    batallas[2] = &funcion_batalla_3;
    batallas[3] = &funcion_batalla_4;
    batallas[4] = &funcion_batalla_5;
}