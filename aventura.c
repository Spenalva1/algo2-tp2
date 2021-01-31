#include <stdio.h>
#include <stdbool.h>
#include "heap.h"
#include "gimnasio.h"

#define ROJO "\033[0;31m"
#define VERDE "\033[0;32m"
#define RESET "\033[0m"
#define POKEMONES_BATALLA 6
#define CANT_TIPO_BATALLAS 5
#define CAMBIAR_POKEMONES 'C'
#define CAMBIAR_POKEMONES_MIN 'c'
#define ENTRENADOR 'E'
#define ENTRENADOR_MIN 'e'
#define GIMNASIO 'G'
#define GIMNASIO_MIN 'g'
#define AGREGAR_GIMNASIO 'A'
#define AGREGAR_GIMNASIO_MIN 'a'
#define INICIAR_PARTIDA 'I'
#define INICIAR_PARTIDA_MIN 'i'
#define SIMULAR_PARTIDA 'S'
#define SIMULAR_PARTIDA_MIN 's'
#define BATALLAR 'B'
#define BATALLAR_MIN 'b'
#define PROXIMO 'N'
#define PROXIMO_MIN 'n'
#define TOMAR_PRESTADO 'T'
#define TOMAR_PRESTADO_MIN 't'
#define REINTENTAR 'R'
#define REINTENTAR_MIN 'r'
#define FINALIZAR 'F'
#define FINALIZAR_MIN 'f'

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
int agregar_gimnasio(heap_t* gimnasios);

/*
*
*/
int agregar_personaje(juego_t* juego);

/*
*
*/
void menu_victoria(juego_t* juego);

/*
*
*/
void maestro_pokemon(juego_t* juego);

/*
*
*/
void menu_derrota(juego_t* juego);

/*
*
*/
void mostrar_combate_informacion(pokemon_t* p1, pokemon_t* p2);

/*
*
*/
void batallar(juego_t* juego);

/*
*
*/
void menu_gimnasio(juego_t* juego);

/*
*
*/
void menu_inicio(juego_t* juego);

/*
*
*/
void terminar_juego(juego_t* juego);

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

int agregar_gimnasio(heap_t* gimnasios){
    printf("Ingrese la ruta del archivo del gimnasio que desea agregar: ");
    char ruta[MAX_RUTA];
    scanf("%s", ruta);
    gimnasio_t* gimnasio = gimnasio_crear(ruta);
    int resultado;
    if(gimnasio && (resultado = heap_insertar_elemento(gimnasios, gimnasio) == OK)) return OK;
    printf("Error al cargar gimnasio, intente devuelta.\n");
    return ERROR;
}

int agregar_personaje(juego_t* juego){
    printf("Ingrese la ruta del archivo del personaje que desea cargar: ");
    char ruta[MAX_RUTA];
    scanf("%s", ruta);
    personaje_t* personaje = personaje_principal_crear(ruta);
    if(personaje){
        juego->personaje_principal = personaje;
        return OK;
    }
    printf("Error al cargar gimnasio, intente devuelta.\n");
    return ERROR;
}

void menu_victoria(juego_t* juego){
    char letra_ingresada;
    gimnasio_t* gimnasio = (gimnasio_t*)heap_obtener_raiz(juego->gimnasios);
    bool tomo_prestado = false;
    printf("Felicitaciones, has ganado la medalla del gimnasio" VERDE " %s" RESET ". Seleccione una de las siguientes opciones:\n", gimnasio->nombre);
    if(!tomo_prestado) printf("T -> Tomar prestado un pokemon del lider del gimnasio\n");
    printf("C -> Cambiar pokemones de batalla\n");
    printf("N -> %s\n", (heap_elementos(juego->gimnasios)-1) ? "Proximo gimnasio" : "Continuar");
    printf("Ingrese uno de los caracteres indicados: ");
    scanf(" %c", &letra_ingresada);
    bool menu_terminado = false, letra_valida = false;
    while(!menu_terminado){
        letra_valida = false;
        if(letra_ingresada == TOMAR_PRESTADO || letra_ingresada == TOMAR_PRESTADO_MIN){
            elegir_pokemon_rival(juego->personaje_principal->pokemon_obtenidos, gimnasio->lider->pokemones);
            tomo_prestado = true;
            letra_valida = true;
        }
        if(letra_ingresada == CAMBIAR_POKEMONES || letra_ingresada == CAMBIAR_POKEMONES_MIN){
            cambiar_pokemon(juego->personaje_principal);
            letra_valida = true;
        }
        if(letra_ingresada == PROXIMO || letra_ingresada == PROXIMO_MIN){
            heap_quitar_raiz(juego->gimnasios);
            (heap_elementos(juego->gimnasios)-1) ? menu_gimnasio(juego) : maestro_pokemon(juego);
            menu_terminado = true;
        }

        if(!menu_terminado){
            if(!letra_valida) printf("Caracter Inválido, las opciones son: \n");
            if(!tomo_prestado) printf("T -> Tomar prestado un pokemon del lider del gimnasio\n");
            printf("C -> Cambiar pokemones de batalla\n");
            printf("N -> %s\n", (heap_elementos(juego->gimnasios)-1) ? "Proximo gimnasio" : "Continuar");
            printf("Ingrese uno de los caracteres indicados: ");
            scanf(" %c", &letra_ingresada);
        }
    }   
}

void maestro_pokemon(juego_t* juego){
    printf("¡Has obtenido las medallas de todos los gimnasios!\n");
    printf("¡Te has convertido en un maestro pokemon!\n");
}

void terminar_juego(juego_t* juego){ //VOY POR ACA
    personaje_principal_destruir(juego->personaje_principal);
    heap_destruir(juego->gimnasios);
    if(juego->tipos_de_batallas) free(juego->tipos_de_batallas);
    free(juego);
}

void menu_derrota(juego_t* juego){
    gimnasio_t* gimnasio = heap_obtener_raiz(juego->gimnasios);
    entrenador_t* rival = (lista_vacia(gimnasio->entrenadores)) ? gimnasio->lider : lista_ultimo(gimnasio->entrenadores);
    printf(ROJO"¡Has perdido la batalla contra %s!\n" RESET" Seleccione una de las siguientes opciones:\n", rival->nombre);
    printf("C -> Cambiar pokemones de batalla\n");
    printf("R -> Reintenta\n");
    printf("F -> Finalizar partida\n");
    printf("Ingrese uno de los caracteres indicados: ");
    char letra_ingresada;
    scanf(" %c", &letra_ingresada);
    bool menu_terminado = false, letra_valida = false;
    while(!menu_terminado){
        letra_valida = false;
        if(letra_ingresada == CAMBIAR_POKEMONES || letra_ingresada == CAMBIAR_POKEMONES_MIN){
            cambiar_pokemon(juego->personaje_principal);
            letra_valida = true;
        }
        if(letra_ingresada == REINTENTAR || letra_ingresada == REINTENTAR_MIN){
            menu_gimnasio(juego);
            letra_valida = true;
            menu_terminado = true;
        }
        if(letra_ingresada == FINALIZAR || letra_ingresada == FINALIZAR_MIN){
            terminar_juego(juego);
            letra_valida = true;
            menu_terminado = true;
        }


        if(!menu_terminado){
            if(!letra_valida) printf("Caracter Inválido, las opciones son: \n");
            printf("C -> Cambiar pokemones de batalla\n");
            printf("R -> Reintenta\n");
            printf("F -> Finalizar partida\n");
            printf("Ingrese uno de los caracteres indicados: ");
            scanf(" %c", &letra_ingresada);
        }
    }
}

void mostrar_combate_informacion(pokemon_t* p1, pokemon_t* p2){
    printf(VERDE "\t%s" RESET "\tVelocidad -> %i   Ataque -> %i   Defensa -> %i\n", p1->nombre, p1->velocidad, p1->ataque, p1->defensa);
    printf("VS.\n");
    printf(ROJO "\t%s" RESET "\tVelocidad -> %i   Ataque -> %i   Defensa -> %i\n", p2->nombre, p2->velocidad, p2->ataque, p2->defensa);
}

void batallar(juego_t* juego){
    gimnasio_t* gimnasio = heap_obtener_raiz(juego->gimnasios);
    bool es_lider = lista_vacia(gimnasio->entrenadores);
    funcion_batalla batalla = juego->tipos_de_batallas[gimnasio->id_puntero_funcion-1];
    entrenador_t* rival = es_lider ? gimnasio->lider : lista_ultimo(gimnasio->entrenadores);
    lista_iterador_t* it1 = lista_iterador_crear(juego->personaje_principal->pokemon_para_combatir);
    lista_iterador_t* it2 = lista_iterador_crear(rival->pokemones);
    char letra_ingresada;
    int i = 1;
    printf(VERDE "%s" RESET " vs. " ROJO "%s %s" RESET "\n", juego->personaje_principal->nombre, rival->nombre, es_lider ? "(lider)" : "");
    while(lista_iterador_tiene_siguiente(it1) && lista_iterador_tiene_siguiente(it2)){
        printf("Combate n°%i:\n", i);
        mostrar_combate_informacion(lista_iterador_elemento_actual(it1), lista_iterador_elemento_actual(it2));
        printf("Ingrese N para realizar el combate: ");
        scanf(" %c", &letra_ingresada);
        while(letra_ingresada != PROXIMO && letra_ingresada != PROXIMO_MIN){
            printf("Ingrese N para realizar el combate: ");
            scanf(" %c", &letra_ingresada);
        }
        if(batalla(lista_iterador_elemento_actual(it1), lista_iterador_elemento_actual(it2)) == GANO_PRIMERO){
            printf("Tu " VERDE "%s " RESET "ha derrotado a " ROJO "%s" RESET ".\n", ((pokemon_t*)lista_iterador_elemento_actual(it1))->nombre, ((pokemon_t*)lista_iterador_elemento_actual(it2))->nombre);
            mejorar_pokemon(lista_iterador_elemento_actual(it1));
            lista_iterador_avanzar(it2);
        }else{
            printf(ROJO"%s " RESET "ha derrotado a tu " VERDE "%s" RESET ".\n", ((pokemon_t*)lista_iterador_elemento_actual(it2))->nombre, ((pokemon_t*)lista_iterador_elemento_actual(it1))->nombre);
            lista_iterador_avanzar(it1);
        }
        i++;
    }
    bool victoria = lista_iterador_tiene_siguiente(it1);
    lista_iterador_destruir(it1);
    lista_iterador_destruir(it2);
    if(victoria){
        printf(VERDE"¡Has ganado la batalla contra %s!\n"RESET, rival->nombre);
        if(es_lider){
            menu_victoria(juego);
            return;
        }
        entrenador_destruir(rival);
        lista_desapilar(gimnasio->entrenadores);
        printf("Continuamos con el proximo entrenador...\n");
        batallar(juego);
        return;
    }
    menu_derrota(juego);
}

void menu_gimnasio(juego_t* juego){
    char letra_ingresada;
    gimnasio_t* gimnasio = heap_obtener_raiz(juego->gimnasios);
    bool lider_habilitado = lista_vacia(gimnasio->entrenadores);
    printf("Bienvenido al gimnasio " VERDE "\"%s\"" RESET " Seleccione una de las siguientes opciones:\n", gimnasio->nombre);
    printf("E -> Mostrar entrenador principal\n");
    printf("G -> Mostrar informacion del gimnasio actual\n");
    printf("C -> Cambiar pokemones de batalla\n");
    printf("B -> Batallar con el %s\n", (lider_habilitado) ? "lider" : "próximo entrenador");
    printf("Ingrese uno de los caracteres indicados: ");
    scanf(" %c", &letra_ingresada);
    bool menu_terminado = false, letra_valida = false;
    while(!menu_terminado){
        letra_valida = false;
        if(letra_ingresada == ENTRENADOR || letra_ingresada == ENTRENADOR_MIN){
            personaje_principal_mostrar(juego->personaje_principal);
            letra_valida = true;
        }
        if(letra_ingresada == GIMNASIO || letra_ingresada == GIMNASIO_MIN){
            gimnasio_mostrar(gimnasio);
            letra_valida = true;
        }
        if((letra_ingresada == CAMBIAR_POKEMONES || letra_ingresada == CAMBIAR_POKEMONES_MIN) 
            && lista_elementos(juego->personaje_principal->pokemon_obtenidos) > POKEMONES_BATALLA){
            cambiar_pokemon(juego->personaje_principal);
            letra_valida = true;
        }
        if(letra_ingresada == BATALLAR || letra_ingresada == BATALLAR_MIN){
            batallar(juego);
            menu_terminado = true;
            letra_valida = true;
        }


        if(!menu_terminado){
            if(!letra_valida) printf("Caracter Inválido, las opciones son: \n");
            printf("E -> Mostrar entrenador principal\n");
            printf("G -> Mostrar informacion del gimnasio actual\n");
            printf("C -> Cambiar pokemones de batalla\n");
            printf("B -> Batallar con el %s\n", (lider_habilitado) ? "lider" : "próximo entrenador");
            printf("Ingrese uno de los caracteres indicados: ");
            scanf(" %c", &letra_ingresada);
        }
    }
}

void menu_inicio(juego_t* juego){
    char letra_ingresada;
    printf("Bienvenido a ¡Una aventura Pokémon! Seleccione una de las siguientes opciones:\n");
    if(!(juego->personaje_principal))
        printf("E -> Cargar el entrenador principal\n");
    printf("A -> Cargar un gimnasio\n");
    if(juego->personaje_principal && heap_elementos(juego->gimnasios) > 0){
        printf("I -> Comenzar partida\n");
        printf("S -> Simular partida\n");
    }
    printf("Ingrese uno de los caracteres indicados: ");
    scanf(" %c", &letra_ingresada);
    bool menu_terminado = false;
    bool letra_valida = false;
    while(!menu_terminado){
        letra_valida = false;
        if(letra_ingresada == AGREGAR_GIMNASIO || letra_ingresada == AGREGAR_GIMNASIO_MIN){
            agregar_gimnasio(juego->gimnasios);
            letra_valida = true;
        }
        if((letra_ingresada == ENTRENADOR || letra_ingresada == ENTRENADOR_MIN) && !(juego->personaje_principal)){
            agregar_personaje(juego);
            letra_valida = true;
        }
        if((letra_ingresada == INICIAR_PARTIDA
            || letra_ingresada == SIMULAR_PARTIDA
            || letra_ingresada == INICIAR_PARTIDA_MIN
            || letra_ingresada == SIMULAR_PARTIDA_MIN) 
            && juego->personaje_principal && heap_elementos(juego->gimnasios) > 0){
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
            scanf(" %c", &letra_ingresada);
        }
    }
}