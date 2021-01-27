#include <stdio.h>
#include "gimnasio.h"

// CREAR DESTRUCTORES

#define GIMNASIO 'G'
#define LIDER 'L'
#define POKEMON 'P'
#define ENTRENADOR 'E'
#define MAX_HABILIDAD 63
#define MIN_HABILIDAD 0

/*
*
*/
bool letra_gimnasio_valida(char letra){
    return letra == LIDER || letra == POKEMON || letra == ENTRENADOR;
}

/*
*
*/
bool pokemon_valido(pokemon_t pokemon){
    return pokemon.ataque >= 0 && pokemon.defensa >= 0 && pokemon.velocidad >= 0;
}

gimnasio_t* crear_gimnasio(char ruta[MAX_RUTA]){
    FILE* archivo = fopen(ruta, "r");
    if(!archivo) return NULL;
    char letra = (char)fgetc(archivo);
    if(letra != GIMNASIO){
        fclose(archivo);
        return NULL;
    }
    gimnasio_t gimnasio;
    int leidos = fscanf(archivo, ";%49[^;]; %i; %i\n", gimnasio.nombre, &(gimnasio.dificultad), &(gimnasio.id_puntero_funcion));
    if(leidos != 3){
        fclose(archivo);
        return NULL;
    }

    letra = (char)fgetc(archivo);
    if(letra != LIDER){
        fclose(archivo);
        return NULL;
    }
    entrenador_t entrenador;
    leidos = fscanf(archivo, ";%49[^\n]\n", entrenador.nombre);
    if(leidos != 1){
        fclose(archivo);
        return NULL;
    }

    
    letra = (char)fgetc(archivo);
    if(letra != POKEMON){
        fclose(archivo);
        return NULL;
    }

    pokemon_t pokemon;
    leidos = fscanf(archivo, ";%49[^;]; %i; %i; %i\n", pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
    if(leidos != 4 || !pokemon_valido(pokemon)){
        fclose(archivo);
        return NULL;
    }

    gimnasio_t* gimnasio_ptr = malloc(sizeof(gimnasio_t));
    if(!gimnasio_ptr){
        fclose(archivo);
        return NULL;
    }
    entrenador_t* entrenador_ptr = malloc(sizeof(entrenador_t));
    if(!entrenador_ptr){
        fclose(archivo);
        free(gimnasio_ptr);
        return NULL;
    }
    pokemon_t* pokemon_ptr = malloc(sizeof(pokemon_t));
    if(!pokemon_ptr){
        fclose(archivo);
        free(gimnasio_ptr);
        free(entrenador_ptr);
        return NULL;
    }

    *gimnasio_ptr = gimnasio;
    *entrenador_ptr = entrenador;
    *pokemon_ptr = pokemon;
    gimnasio_ptr->lider = entrenador_ptr;
    
    gimnasio_ptr->lider->pokemones = lista_crear();
    if(!(gimnasio_ptr->lider->pokemones)){
        fclose(archivo);
        free(gimnasio_ptr);
        free(entrenador_ptr);
        free(pokemon_ptr);
        return NULL;
    }

    lista_encolar(gimnasio_ptr->lider->pokemones, pokemon_ptr);
    pokemon_ptr = NULL;

    bool hay_error = false;
    letra = fgetc(archivo);
    while(letra == POKEMON && !hay_error){
        leidos = fscanf(archivo, ";%49[^;]; %i; %i; %i\n", pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));

            // printf("LLEGUE, %d, %c, %d\n", hay_error, letra, leidos);
        if(leidos != 4 || !pokemon_valido(pokemon)){
            hay_error = true;
        } else {
            pokemon_ptr = malloc(sizeof(pokemon_t));
            if(!pokemon_ptr){
                hay_error = true;
            } else {
                *pokemon_ptr = pokemon;
                lista_encolar(gimnasio_ptr->lider->pokemones, pokemon_ptr);
                pokemon_ptr = NULL;
            }
        }
        letra = fgetc(archivo);
    }

    gimnasio_ptr->entrenadores = lista_crear();

    bool entrenador_valido = false;
    

    while(letra == ENTRENADOR && !hay_error){
        leidos = fscanf(archivo, ";%49[^\n]\n", entrenador.nombre);

        if(leidos != 1){
            hay_error = true;
        }

        letra = fgetc(archivo);

        if(letra != POKEMON) {
            hay_error = true;
        } else {
            leidos = fscanf(archivo, ";%49[^;]; %i; %i; %i\n", pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
            if(leidos != 4 || !pokemon_valido(pokemon)){
                hay_error = true;
            } else {
                pokemon_ptr = malloc(sizeof(pokemon_t));
                if(!pokemon_ptr){
                    hay_error = true;
                } else {
                    entrenador_ptr = malloc(sizeof(entrenador_t));
                    if(!entrenador_ptr){
                        hay_error = true;
                    } else {
                        *pokemon_ptr = pokemon;
                        *entrenador_ptr = entrenador;
                        entrenador_ptr->pokemones = lista_crear();
                        if(!(entrenador_ptr->pokemones)){
                            hay_error = true;
                        } else {
                            lista_encolar(entrenador_ptr->pokemones, pokemon_ptr);
                            pokemon_ptr = NULL;
                            entrenador_valido = true;
                        }
                    }
                }
            }
            letra = fgetc(archivo);
        }
        while(letra == POKEMON && !hay_error){
            leidos = fscanf(archivo, ";%49[^;]; %i; %i; %i\n", pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));

            if(leidos != 4 || !pokemon_valido(pokemon)){
                hay_error = true;
            } else {
                pokemon_ptr = malloc(sizeof(pokemon_t));
                if(!pokemon_ptr){
                    hay_error = true;
                } else {
                    *pokemon_ptr = pokemon;
                    lista_encolar(entrenador_ptr->pokemones, pokemon_ptr);
                    pokemon_ptr = NULL;
                }
            }
            letra = fgetc(archivo);
        }
        if(entrenador_valido){
            lista_apilar(gimnasio_ptr->entrenadores, entrenador_ptr);
            entrenador_ptr = NULL;
            entrenador_valido = false;
        }

    }

    printf("GIMNASIO: nombre -> %s, dificultad -> %i, id -> %i\n", gimnasio_ptr->nombre, gimnasio_ptr->dificultad, gimnasio_ptr->id_puntero_funcion);
    printf("LIDER: nombre -> %s\n", gimnasio_ptr->lider->nombre);
    pokemon_ptr = lista_primero(gimnasio_ptr->lider->pokemones);
    printf("PRIMER POKEMON LIDER: nombre -> %s, vel -> %i, ata -> %i, def -> %i\n", pokemon_ptr->nombre, pokemon_ptr->velocidad, pokemon_ptr->ataque, pokemon_ptr->defensa);
    lista_desencolar(gimnasio_ptr->lider->pokemones);
    pokemon_ptr = lista_primero(gimnasio_ptr->lider->pokemones);
    printf("SEGUNDO POKEMON LIDER: nombre -> %s, vel -> %i, ata -> %i, def -> %i\n", pokemon_ptr->nombre, pokemon_ptr->velocidad, pokemon_ptr->ataque, pokemon_ptr->defensa);
    entrenador_ptr = lista_ultimo(gimnasio_ptr->entrenadores);
    printf("PRIMER ENTRENADOR: nombre -> %s\n", entrenador_ptr->nombre);
    pokemon_ptr = lista_primero(entrenador_ptr->pokemones);
    printf("PRIMER POKEMON ENTRENADOR: nombre -> %s, vel -> %i, ata -> %i, def -> %i\n", pokemon_ptr->nombre, pokemon_ptr->velocidad, pokemon_ptr->ataque, pokemon_ptr->defensa);
    lista_desencolar(entrenador_ptr->pokemones);
    // pokemon_ptr = lista_primero(entrenador_ptr->pokemones);
    // printf("SEGUNDO POKEMON ENTRENADOR: nombre -> %s, vel -> %i, ata -> %i, def -> %i\n", pokemon_ptr->nombre, pokemon_ptr->velocidad, pokemon_ptr->ataque, pokemon_ptr->defensa);
    // lista_desapilar(gimnasio_ptr->entrenadores);
    // entrenador_ptr = lista_ultimo(gimnasio_ptr->entrenadores);
    // printf("SEGUNDO ENTRENADOR: nombre -> %s\n", entrenador_ptr->nombre);
    // pokemon_ptr = lista_ultimo(entrenador_ptr->pokemones);
    // printf("PRIMER POKEMON ENTRENADOR: nombre -> %s, vel -> %i, ata -> %i, def -> %i\n", pokemon_ptr->nombre, pokemon_ptr->velocidad, pokemon_ptr->ataque, pokemon_ptr->defensa);


    fclose(archivo);
    if(pokemon_ptr) free(pokemon_ptr);
    if(entrenador_ptr) free(entrenador_ptr);
    return gimnasio_ptr;
}

personaje_t* crear_personaje_principal(char ruta[MAX_RUTA]){
    return NULL;
}