#include <stdio.h>
#include <stdlib.h>
#include "pokemon.h"

#define MAX_BONIFICACIONES 63
#define ROJO "\033[0;31m"
#define VERDE "\033[0;32m"
#define RESET "\033[0m"
#define OK 0
#define ERROR -1

void batallas_cargar(funcion_batalla* batallas){
    batallas[0] = &funcion_batalla_1;
    batallas[1] = &funcion_batalla_2;
    batallas[2] = &funcion_batalla_3;
    batallas[3] = &funcion_batalla_4;
    batallas[4] = &funcion_batalla_5;
}

void mejorar_pokemon(pokemon_t* pokemon){
    if(!pokemon) return;
    if(pokemon->bonificaciones >= MAX_BONIFICACIONES){
        printf("Las habilidades de" VERDE " %s " RESET "ya no pueden ser mejoradas.\n", pokemon->nombre);
        return;
    }
    pokemon->velocidad++;
    pokemon->ataque++;
    pokemon->defensa++;
    pokemon->bonificaciones++;
    printf("Las habilidades de" VERDE " %s " RESET "han sido mejoradas.\n", pokemon->nombre);
}

int elegir_pokemon_rival(lista_t* obtenidos, lista_t* pokemones_rival){
    size_t i = 1;
    printf("Los pokemones de tu rival son:\n");
    lista_con_cada_elemento(pokemones_rival, &mostrar_pokemon_con_id, &i);
    printf("Ingrese el número del pokemon deseado o \"0\" si no desea ninguno: ");
    scanf(" %lu", &i);
    while(i > lista_elementos(pokemones_rival)){
        printf("El número ingresado no es válido, ingrese el número del pokemon deseado o \"0\" si no desea ninguno: ");
        scanf(" %lu", &i);
    }
    if(i == 0) return OK;
    pokemon_t* pokemon = malloc(sizeof(pokemon_t));
    if(!pokemon) return ERROR;
    *pokemon = *(pokemon_t*)lista_elemento_en_posicion(pokemones_rival, i-1);
    lista_insertar(obtenidos, pokemon);
    printf("El pokemon " VERDE "%s " RESET "ha sido añadido a tus pokemones.\n", ((pokemon_t*)lista_elemento_en_posicion(pokemones_rival, i-1))->nombre);
    return OK;
}

bool cambio_valido(lista_t* pokemones, pokemon_t* pokemon){
    lista_iterador_t* it = lista_iterador_crear(pokemones);
    bool cambio_valido = true;
    while(lista_iterador_tiene_siguiente(it) && cambio_valido){
        if(lista_iterador_elemento_actual(it) == pokemon) cambio_valido = false;
        lista_iterador_avanzar(it);
    }
    lista_iterador_destruir(it);
    return cambio_valido;
}

bool mostrar_pokemon(void* pokemon, void* contador){
    if(pokemon){
        printf(VERDE "       %s" RESET "\r\t\t\tVelocidad -> %i   Ataque -> %i   Defensa -> %i\n", ((pokemon_t*)pokemon)->nombre, ((pokemon_t*)pokemon)->velocidad, ((pokemon_t*)pokemon)->ataque, ((pokemon_t*)pokemon)->defensa);
    }
    return true;
}

bool mostrar_pokemon_con_id(void* pokemon, void* contador){
    if(pokemon){
        printf("   [%i] " VERDE "%s" RESET "\r\t\t\tVelocidad -> %i   Ataque -> %i   Defensa -> %i\n", *(int*)contador, ((pokemon_t*)pokemon)->nombre, ((pokemon_t*)pokemon)->velocidad, ((pokemon_t*)pokemon)->ataque, ((pokemon_t*)pokemon)->defensa);
        (*(int*)contador)++;        
    }
    return true;
}
