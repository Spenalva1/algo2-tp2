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
    funcion_batalla* tipos_de_batallas;
    personaje_t* personaje_principal;
    heap_t* gimnasios;
    bool simular;
}juego_t;

int comparador(void* g1_ptr, void* g2_ptr){
    gimnasio_t* g1 = (gimnasio_t*)g1_ptr;
    gimnasio_t* g2 = (gimnasio_t*)g2_ptr;
    if(g1->dificultad < g2->dificultad)
        return 1;
    else if(g1->dificultad > g2->dificultad)
        return -1;
    else
        return 0;
}

void destructor(void* g){
    gimnasio_destruir(g);
}

/*
*
*/
int agregar_gimnasio(heap_t* gimnasios){
    return 1;
}

/*
*
*/
int agregar_personaje(juego_t* juego){
    return 1;
}

void menu_gimnasio(juego_t* juego){
    return;
}

/*
*
*/
void menu_inicio(juego_t* juego){
    char letra_ingresada;
    printf("Bienvenido a ¡Una aventura Pokémon! Seleccioné una de las siguientes opciones:\n");
    if(!(juego->personaje_principal))
        printf("E -> Cargar el entrenador principal\n");
    printf("A -> Cargar un gimnasio\n");
    if(juego->personaje_principal && heap_elementos(juego->gimnasios) > 0){
        printf("I -> Comenzar partida\n");
        printf("S -> Simular partida\n");
    }
    printf("Ingrese uno de los caracteres indicados: ");
    letra_ingresada = (char)getchar();
    bool menu_terminado = false;
    bool letra_valida = false;
    while(!menu_terminado){
        letra_valida = false;
        if(letra_ingresada == AGREGAR_GIMNASIO){
            agregar_gimnasio(juego->gimnasios);
            letra_valida = true;
        }
        if(letra_ingresada == ENTRENADOR && !(juego->personaje_principal)){
            agregar_personaje(juego);
            letra_valida = true;
        }
        if((letra_ingresada == INICIAR_PARTIDA || letra_ingresada == SIMULAR_PARTIDA) && juego->personaje_principal && heap_elementos(juego->gimnasios) > 0){
            juego->simular = letra_ingresada == SIMULAR_PARTIDA;
            menu_gimnasio(juego);
            letra_valida = true;
            menu_terminado = true;
        }

        if(!menu_terminado){
            if(!letra_valida) printf("Caracter Inválido, las opciones son: \n");

            if(!(juego->personaje_principal))
                printf("E -> Cargar el entrenador principal\n");
            printf("A -> Cargar un gimnasio\n");
            if(juego->personaje_principal && heap_elementos(juego->gimnasios) > 0){
                printf("I -> Comenzar partida\n");
                printf("S -> Simular partida\n");
            }
            printf("Ingrese uno de los caracteres indicados: ");
            letra_ingresada = (char)getchar();
            printf("LETRA -> %c.\n", letra_ingresada);
        } //PROBLEMA, GETCHAR LEE EL SALTO DE LINEA
    }
}

int main(){
    juego_t* juego = malloc(sizeof(juego));
    if(!juego){
        printf("Error al inicializar el juego, intente devuelta");
        return -1;
    }
    juego->gimnasios = heap_crear(&comparador, &destructor);
    if(!juego->gimnasios){
        free(juego);
        printf("Error al inicializar el juego, intente devuelta");
    }
    juego->tipos_de_batallas = batallas_cargar();
    if(!juego->tipos_de_batallas){
        heap_destruir(juego->gimnasios);
        free(juego);
        printf("Error al inicializar el juego, intente devuelta");
    }
    menu_inicio(juego);
    return 0;
}