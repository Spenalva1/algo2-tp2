#include <string.h>
#include "pa2mm.h"
#include "gimnasio.h"

int main(){
    funcion_batalla* batallas = batallas_cargar();
    gimnasio_t* gimnasio_ptr = gimnasio_crear("gimnasios/gimnasio1.txt");
    if(!gimnasio_ptr){
        printf("mal\n");
    }
    personaje_t* personaje_ptr = personaje_principal_crear("personajes/personaje1.txt");
    if(!personaje_ptr){
        printf("mal\n");
    }

    // enfrentamiento(personaje_ptr, gimnasio_ptr->lider, batallas[gimnasio_ptr->id_puntero_funcion - 1]);  
    // elegir_pokemon_rival(personaje_ptr->pokemon_obtenidos, gimnasio_ptr->lider->pokemones);

    cambiar_pokemon(personaje_ptr);

    personaje_principal_destruir(personaje_ptr);
    gimnasio_destruir(gimnasio_ptr);
    batallas_destruir(batallas);

    // PRUEBAS
    // printf("GIMNASIO: nombre -> %s, dificultad -> %i, id -> %i\n", gimnasio_ptr->nombre, gimnasio_ptr->dificultad, gimnasio_ptr->id_puntero_funcion);
    // printf("LIDER: nombre -> %s\n", gimnasio_ptr->lider->nombre);
    // pokemon_t* pokemon_ptr = lista_primero(gimnasio_ptr->lider->pokemones);
    // printf("PRIMER POKEMON LIDER: nombre -> %s, vel -> %i, ata -> %i, def -> %i\n", pokemon_ptr->nombre, pokemon_ptr->velocidad, pokemon_ptr->ataque, pokemon_ptr->defensa);
    // lista_desencolar(gimnasio_ptr->lider->pokemones);
    // pokemon_ptr = lista_primero(gimnasio_ptr->lider->pokemones);
    // printf("SEGUNDO POKEMON LIDER: nombre -> %s, vel -> %i, ata -> %i, def -> %i\n", pokemon_ptr->nombre, pokemon_ptr->velocidad, pokemon_ptr->ataque, pokemon_ptr->defensa);
    // entrenador_t* entrenador_ptr = lista_ultimo(gimnasio_ptr->entrenadores);
    // printf("PRIMER ENTRENADOR: nombre -> %s\n", entrenador_ptr->nombre);
    // pokemon_ptr = lista_primero(entrenador_ptr->pokemones);
    // printf("PRIMER POKEMON ENTRENADOR: nombre -> %s, vel -> %i, ata -> %i, def -> %i\n", pokemon_ptr->nombre, pokemon_ptr->velocidad, pokemon_ptr->ataque, pokemon_ptr->defensa);
    // lista_desencolar(entrenador_ptr->pokemones);
    // pokemon_ptr = lista_primero(entrenador_ptr->pokemones);
    // printf("SEGUNDO POKEMON ENTRENADOR: nombre -> %s, vel -> %i, ata -> %i, def -> %i\n", pokemon_ptr->nombre, pokemon_ptr->velocidad, pokemon_ptr->ataque, pokemon_ptr->defensa);
    // lista_desapilar(gimnasio_ptr->entrenadores);
    // entrenador_ptr = lista_ultimo(gimnasio_ptr->entrenadores);
    // printf("SEGUNDO ENTRENADOR: nombre -> %s\n", entrenador_ptr->nombre);
    // pokemon_ptr = lista_ultimo(entrenador_ptr->pokemones);
    // printf("PRIMER POKEMON ENTRENADOR: nombre -> %s, vel -> %i, ata -> %i, def -> %i\n", pokemon_ptr->nombre, pokemon_ptr->velocidad, pokemon_ptr->ataque, pokemon_ptr->defensa);

    return 0;
}