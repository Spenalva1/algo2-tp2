#include <stdio.h>
#include <stdbool.h>
#include "heap.h"
#include "gimnasio.h"

#define CANT_TIPO_BATALLAS 5
#define ENTRENADOR 'E'
#define AGREGAR_GIMNASIO 'A'
#define INICIAR_PARTIDA 'I'
#define SIMULAR_PARTIDA 'S'

typedef struct juego{
    funcion_batalla tipos_de_batallas[CANT_TIPO_BATALLAS];
    personaje_t personaje_principal;
    heap_t gimnasios;
    bool simular;
}juego_t;

/*
*
*/
bool letra_menu_inicio_valida(char letra) {
    return letra == ENTRENADOR || letra == AGREGAR_GIMNASIO || letra == INICIAR_PARTIDA || letra == SIMULAR_PARTIDA;
}

/*
*
*/
char mostrar_menu_inicio() {
    char letra_ingresada;
    printf("Bienvenido a ¡Una aventura Pokémon! Seleccioné una de las siguientes opciones:\n");
    printf("E -> Cargar el entrenador principal\n");
    printf("A -> Cargar un gimnasio\n");
    printf("I -> Comenzar partida\n");
    printf("S -> Simular partida\n");
    letra_ingresada = (char)getchar();
    while(!letra_menu_inicio_valida(letra_ingresada)) {
        printf("Caracter Inválido, las opciones son: ");
        printf("E -> Cargar el entrenador principal\n");
        printf("A -> Cargar un gimnasio\n");
        printf("I -> Comenzar partida\n");
        printf("S -> Simular partida\n");
        letra_ingresada = (char)getchar();
    }
    return 'a';
}