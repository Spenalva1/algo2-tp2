#include <stdio.h>
#include <stdbool.h>

#define ENTRENADOR 'E'
#define AGREGAR_GIMNASIO 'A'
#define INICIAR_PARTIDA 'I'
#define SIMULAR_PARTIDA 'S'

bool letra_menu_inicio_valida(char letra) {
    return letra != ENTRENADOR && letra != AGREGAR_GIMNASIO && letra != INICIAR_PARTIDA != letra != SIMULAR_PARTIDA;
}

char mostrar_menu_inicio() {
    char letra_ingresada;
    printf("Bienvenido a ¡Una aventura Pokémon! Seleccioné una de las siguientes opciones:\n");
    printf("E -> Cargar el entrenador principal\n");
    printf("A -> Cargar un gimnasio\n");
    printf("I -> Comenzar partida\n");
    printf("S -> Simular partida\n");
    letra_ingresada = getchar();
    while(!letra_menu_inicio_valida(letra_ingresada)) {
        printf("Caracter Inválido, las opciones son: ");
        printf("E -> Cargar el entrenador principal\n");
        printf("A -> Cargar un gimnasio\n");
        printf("I -> Comenzar partida\n");
        printf("S -> Simular partida\n");
        letra_ingresada = getchar();
    }
}