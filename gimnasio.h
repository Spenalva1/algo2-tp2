#ifndef __GIMNASIO_H__
#define __GIMNASIO_H__

#include "batallas.h"
#include "lista.h"
#include "heap.h"
#include "pokemon.h"

#define MAX_NOMBRE 50
#define MAX_RUTA 100
#define OK 0
#define ERROR -1

typedef struct entrenador{
    char nombre[MAX_NOMBRE];
    lista_t* pokemones; //lista
}entrenador_t;

typedef struct personaje{
    char nombre[MAX_NOMBRE];
    lista_t* pokemon_para_combatir; //lista
    lista_t* pokemon_obtenidos; //lista
}personaje_t;

typedef struct gimnasio{
    char nombre[MAX_NOMBRE];
    int dificultad;
    int id_puntero_funcion;
    entrenador_t* lider;
    lista_t* entrenadores; //pila
}gimnasio_t;

typedef struct juego{
    funcion_batalla tipos_de_batallas[CANT_BATALLAS];
    personaje_t* personaje_principal;
    heap_t* gimnasios;
    bool simular;
}juego_t;

/*
*   Libera la memoria ocupada por un gimnasio
*/
void gimnasio_destruir(gimnasio_t* gimnasio);

/*
*   Muestra la informacion de un personaje principal, detallando su nombre, sus pokemones de combate y los obtenidos
*/
void personaje_principal_mostrar(personaje_t* personaje);

/*
*   permite al usuario cambiar un pokemon de la lista de pokemon_para_combatir por uno de la lista de pokemon_obtenidos
*/
void cambiar_pokemon(personaje_t* personaje);

/*
*   libera la memoria ocupada por el entrenador recibido
*/
void entrenador_destruir(entrenador_t* entrenador);

/*
*   Imprime la informacion del gimnasio recibido, mostrando el nombre del mismo, su dificultad, su id de batalla,
*   el nombre de su lider y el del proximo entrenador
*/
void gimnasio_mostrar(gimnasio_t* gimnasio);

/*
*   Pide al usuario la ruta de un archivo que contenga uno o más gimnasios para leerlo, reservar memoria, y agregarlo/s en el heap recibido
*   Retorna ERROR si hubo un error, OK en caso contrario
*/
void agregar_gimnasios(heap_t* gimnasios);

/*
*   Pide al usuario la ruta de un archivo que contenga un personaje para leerlo. En caso de que ya se haya cargado un personaje principal,
*   se remplazara, y, en caso contrario, se reservará memoria. El puntero al personaje cargado se almacenara en el juego recibido.
*   Retorna ERROR si hubo un error, OK en caso contrario
*/
int agregar_personaje(juego_t* juego);

/*
*   imprime en pantalla el nombre y las habilidades de los pokemones recibidos
*/
void mostrar_combate_informacion(pokemon_t* p1, pokemon_t* p2);

/*
*   liberar toda la memoria reservada por el juego recibido
*/
void terminar_juego(juego_t* juego);

#endif /* __GIMNASIO_H__ */