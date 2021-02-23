#include <stdio.h>
#include <string.h>
#include "gimnasio.h"

#define GIMNASIO 'G'
#define FORMATO_GIMNASIO ";%49[^;];%i;%i\n"
#define FORMATO_ENTRENADOR ";%49[^\n]\n"
#define FORMATO_POKEMON ";%49[^;];%i;%i;%i\n"
#define LIDER 'L'
#define POKEMON 'P'
#define ENTRENADOR 'E'
#define MAX_HABILIDAD 63
#define MAX_POKEMONES_COMBATE 6
#define ROJO "\033[0;31m"
#define VERDE "\033[0;32m"
#define RESET "\033[0m"

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

/*
*   Lee el gimnasio de la ruta recibida, esperando como minimo la informacion del gimnasio, un lider, y al menos un pokemon por lider/entrenador
*/
void gimnasios_cargar(char ruta[MAX_RUTA], heap_t* gimnasios, FILE* archivo){
    char letra;
    if(!archivo) {
        archivo = fopen(ruta, "r");
        if(!archivo) {
            printf("No se pudo abrir el archivo de la ruta indicada.\n");
            return;
        }
        letra = (char)fgetc(archivo);
        if(letra != GIMNASIO){
            fclose(archivo);
            printf("Error al leer el archivo.");
            return;
        }
    }
    
    gimnasio_t gimnasio;
    int leidos = fscanf(archivo, FORMATO_GIMNASIO, gimnasio.nombre, &(gimnasio.dificultad), &(gimnasio.id_puntero_funcion));
    if(leidos != 3){
        fclose(archivo);
        printf("Error al leer el archivo.");
        return;
    }

    letra = (char)fgetc(archivo);
    if(letra != LIDER){
        fclose(archivo);
        printf("Error al leer el archivo.");
        return;
    }
    entrenador_t entrenador;
    leidos = fscanf(archivo, FORMATO_ENTRENADOR, entrenador.nombre);
    if(leidos != 1){
        fclose(archivo);
        printf("Error al leer el archivo.");
        return;
    }

    
    letra = (char)fgetc(archivo);
    if(letra != POKEMON){
        fclose(archivo);
        printf("Error al leer el archivo.");
        return;
    }

    pokemon_t pokemon;
    leidos = fscanf(archivo, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
    if(leidos != 4){
        fclose(archivo);
        printf("Error al leer el archivo.");
        return;
    }

    gimnasio_t* gimnasio_ptr = malloc(sizeof(gimnasio_t));
    if(!gimnasio_ptr){
        fclose(archivo);
        printf("Error al leer el archivo.");
        return;
    }
    entrenador_t* entrenador_ptr = malloc(sizeof(entrenador_t));
    if(!entrenador_ptr){
        fclose(archivo);
        free(gimnasio_ptr);
        printf("Error al leer el archivo.");
        return;
    }
    pokemon_t* pokemon_ptr = malloc(sizeof(pokemon_t));
    if(!pokemon_ptr){
        fclose(archivo);
        free(gimnasio_ptr);
        free(entrenador_ptr);
        printf("Error al leer el archivo.");
        return;
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
        printf("Error al leer el archivo.");
        return;
    }

    lista_insertar(gimnasio_ptr->lider->pokemones, pokemon_ptr);
    pokemon_ptr = NULL;

    bool hay_error = false;
    letra = (char)fgetc(archivo);
    while(letra == POKEMON && !hay_error){
        leidos = fscanf(archivo, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));

        if(leidos != 4){
            hay_error = true;
        } else {
            pokemon_ptr = malloc(sizeof(pokemon_t));
            if(!pokemon_ptr){
                hay_error = true;
            } else {
                *pokemon_ptr = pokemon;
                lista_insertar(gimnasio_ptr->lider->pokemones, pokemon_ptr);
                pokemon_ptr = NULL;
            }
        }
        letra = (char)fgetc(archivo);
    }

    gimnasio_ptr->entrenadores = lista_crear();

    bool entrenador_valido = false;
    

    while(letra == ENTRENADOR && !hay_error){
        leidos = fscanf(archivo, FORMATO_ENTRENADOR, entrenador.nombre);

        if(leidos != 1){
            hay_error = true;
        }

        letra = (char)fgetc(archivo);

        if(letra != POKEMON) {
            hay_error = true;
        } else {
            leidos = fscanf(archivo, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
            if(leidos != 4){
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
                            lista_insertar(entrenador_ptr->pokemones, pokemon_ptr);
                            pokemon_ptr = NULL;
                            entrenador_valido = true;
                        }
                    }
                }
            }
            letra = (char)fgetc(archivo);
        }
        while(letra == POKEMON && !hay_error){
            leidos = fscanf(archivo, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));

            if(leidos != 4){
                hay_error = true;
            } else {
                pokemon_ptr = malloc(sizeof(pokemon_t));
                if(!pokemon_ptr){
                    hay_error = true;
                } else {
                    *pokemon_ptr = pokemon;
                    lista_insertar(entrenador_ptr->pokemones, pokemon_ptr);
                    pokemon_ptr = NULL;
                }
            }
            letra = (char)fgetc(archivo);
        }
        if(entrenador_valido){
            lista_apilar(gimnasio_ptr->entrenadores, entrenador_ptr);
            entrenador_ptr = NULL;
            entrenador_valido = false;
        }

    }

    heap_insertar_elemento(gimnasios, gimnasio_ptr);
    printf(VERDE "%s" RESET " agregado con éxito.\n", gimnasio_ptr->nombre);

    if(pokemon_ptr) free(pokemon_ptr);
    if(entrenador_ptr) free(entrenador_ptr);

    if(letra == GIMNASIO && !hay_error) {
        gimnasios_cargar(ruta, gimnasios, archivo);
        return;
    }
    fclose(archivo);
}

/*
*   libera la memoria ocupada por el pokemon recibido
*/
void pokemon_destruir(pokemon_t* pokemon){
    if(pokemon) free(pokemon);
}

void entrenador_destruir(entrenador_t* entrenador){
    if(!entrenador) return;
    while(!lista_vacia(entrenador->pokemones)){
        pokemon_destruir(lista_ultimo(entrenador->pokemones));
        lista_desapilar(entrenador->pokemones);
    }
    lista_destruir(entrenador->pokemones);
    free(entrenador);
}

/*
*   libera la lista de entrenadores recibida
*/
void entrenadores_destruir(lista_t* entrenadores){
    while(!lista_vacia(entrenadores)){
        entrenador_destruir(lista_ultimo(entrenadores));
        lista_desapilar(entrenadores);
    }
    lista_destruir(entrenadores);
}

void gimnasio_destruir(gimnasio_t* gimnasio) {
    if(!gimnasio) return;
    entrenadores_destruir(gimnasio->entrenadores);
    entrenador_destruir(gimnasio->lider);
    free(gimnasio);
}

/*
*   Lee el personaje de la ruta recibida, esperando como minimo la informacion del personaje y al menos 1 pokemon válido
*/
personaje_t* personaje_principal_crear(char ruta[MAX_RUTA]){
    FILE* archivo = fopen(ruta, "r");
    if(!archivo){
        printf("No se pudo abrir el archivo de la ruta indicada.\n");
        return NULL;
    }
    bool hay_error = false;
    pokemon_t* pokemon_ptr = NULL;
    personaje_t* personaje_ptr = NULL;
    pokemon_t pokemon;
    personaje_t personaje;

    char letra = (char)fgetc(archivo);
    if(letra != ENTRENADOR){
        fclose(archivo);
        return NULL;
    }

    int leidos = fscanf(archivo, FORMATO_ENTRENADOR, personaje.nombre);

    if(leidos != 1){
        fclose(archivo);
        return NULL;
    }

    letra = (char)fgetc(archivo);

    if(letra != POKEMON) {
        hay_error = true;
    } else {
        leidos = fscanf(archivo, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));
        if(leidos != 4){
            hay_error = true;
        } else {
            pokemon_ptr = malloc(sizeof(pokemon_t));
            if(!pokemon_ptr){
                hay_error = true;
            } else {
                personaje_ptr = malloc(sizeof(personaje_t));
                if(!personaje_ptr){
                    hay_error = true;
                } else {
                    *pokemon_ptr = pokemon;
                    *personaje_ptr = personaje;
                    personaje_ptr->pokemon_obtenidos = lista_crear();
                    if(!(personaje_ptr->pokemon_obtenidos)){
                        hay_error = true;
                    } else {
                        personaje_ptr->pokemon_para_combatir = lista_crear();
                        if(!(personaje_ptr->pokemon_obtenidos)){
                            hay_error = true;
                        } else {
                            lista_insertar(personaje_ptr->pokemon_obtenidos, pokemon_ptr);
                            pokemon_ptr = NULL;
                        }
                    }
                }
            }
        }
    }

    if(hay_error){
        fclose(archivo);
        if(pokemon_ptr) free(pokemon_ptr); 
        if(personaje_ptr && personaje_ptr->pokemon_obtenidos) lista_destruir(personaje_ptr->pokemon_obtenidos);
        if(personaje_ptr) free(personaje_ptr); 
        return NULL;
    }

    letra = (char)fgetc(archivo);

    while(letra == POKEMON && !hay_error){
        leidos = fscanf(archivo, FORMATO_POKEMON, pokemon.nombre, &(pokemon.velocidad), &(pokemon.ataque), &(pokemon.defensa));

        if(leidos != 4){
            hay_error = true;
        } else {
            pokemon_ptr = malloc(sizeof(pokemon_t));
            if(!pokemon_ptr){
                hay_error = true;
            } else {
                *pokemon_ptr = pokemon;
                lista_insertar(personaje_ptr->pokemon_obtenidos, pokemon_ptr);
                pokemon_ptr = NULL;
            }
        }

        if(!hay_error) letra = (char)fgetc(archivo);
    }

    lista_iterador_t* it = lista_iterador_crear(personaje_ptr->pokemon_obtenidos);
    while(lista_iterador_tiene_siguiente(it) && lista_elementos(personaje_ptr->pokemon_para_combatir) < MAX_POKEMONES_COMBATE){
        lista_insertar(personaje_ptr->pokemon_para_combatir, lista_iterador_elemento_actual(it));
        lista_iterador_avanzar(it);
    }
    lista_iterador_destruir(it);

    fclose(archivo);
    return personaje_ptr;
}

/*
*   libera la memoria ocupada por el personaje recibido
*/
void personaje_principal_destruir(personaje_t* personaje){
    if(!personaje) return;
    while(!lista_vacia(personaje->pokemon_obtenidos)){
        pokemon_destruir(lista_ultimo(personaje->pokemon_obtenidos));
        lista_desapilar(personaje->pokemon_obtenidos);
    }
    lista_destruir(personaje->pokemon_obtenidos);
    lista_destruir(personaje->pokemon_para_combatir);
    free(personaje);
}

void mejorar_pokemon(pokemon_t* pokemon){
    bool mejora = false;
    if(pokemon->ataque < MAX_HABILIDAD){
        pokemon->ataque++;
        mejora = true;
    }
    if(pokemon->velocidad < MAX_HABILIDAD){
        pokemon->velocidad++;
        mejora = true;
    }
    if(pokemon->defensa < MAX_HABILIDAD){
        pokemon->defensa++;
        mejora = true;
    }
    if(mejora)
        printf("Las habilidades de %s han sido mejoradas.\n", pokemon->nombre);
    else
        printf("Las habilidades de %s ya no pueden ser mejoradas.\n", pokemon->nombre);
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

/*
*   devuelve true su el pokemon recivido se encuentra en la lista de pokemones. Devuelve false en caso contrario
*/
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

void agregar_gimnasios(heap_t* gimnasios){
    printf("Ingrese la ruta del archivo del gimnasio que desea agregar: ");
    char ruta[MAX_RUTA];
    scanf(" %s", ruta);
    gimnasios_cargar(ruta, gimnasios, NULL);
}

int agregar_personaje(juego_t* juego){
    printf("Ingrese la ruta del archivo del personaje que desea cargar: ");
    char ruta[MAX_RUTA];
    scanf(" %s", ruta);
    personaje_t* personaje = personaje_principal_crear(ruta);
    if(personaje){
        juego->personaje_principal = personaje;
        return OK;
    }
    printf("Error al cargar el personaje, intente devuelta.\n");
    return ERROR;
}

void terminar_juego(juego_t* juego){
    personaje_principal_destruir(juego->personaje_principal);
    heap_destruir(juego->gimnasios);
}

void mostrar_combate_informacion(pokemon_t* p1, pokemon_t* p2){
    printf(VERDE "\t%s" RESET "\tVelocidad -> %i   Ataque -> %i   Defensa -> %i\n", p1->nombre, p1->velocidad, p1->ataque, p1->defensa);
    printf("VS.\n");
    printf(ROJO "\t%s" RESET "\tVelocidad -> %i   Ataque -> %i   Defensa -> %i\n", p2->nombre, p2->velocidad, p2->ataque, p2->defensa);
}

void cambiar_pokemon(personaje_t* personaje){
    size_t i = 1;
    printf("Pokemones de batalla:\n");
    lista_con_cada_elemento(personaje->pokemon_para_combatir, &mostrar_pokemon_con_id, &i);
    printf("Pokemones obtenidos:\n");
    lista_con_cada_elemento(personaje->pokemon_obtenidos, &mostrar_pokemon, NULL);
    printf("Ingrese el número del pokemon que desee reemplazar o \"0\" si desea salir: ");
    scanf(" %lu", &i);
    while(i > lista_elementos(personaje->pokemon_para_combatir)){
        printf("El número ingresado no es válido. Ingrese el número del pokemon que desee reemplazar o \"0\" si desea salir: ");
        scanf(" %lu", &i);
    }
    if(i == 0) return;
    size_t j = 1;
    printf("Pokemones obtenidos:\n");
    lista_con_cada_elemento(personaje->pokemon_obtenidos, &mostrar_pokemon_con_id, &j);
    printf("Ingrese el número del pokemon que desee para reemplazar a " ROJO "%s " RESET "o \"0\" si desea salir: ", ((pokemon_t*)lista_elemento_en_posicion(personaje->pokemon_para_combatir, i-1))->nombre);
    scanf(" %lu", &j);
    while(j > lista_elementos(personaje->pokemon_obtenidos)){
        printf("El número ingresado no es válido. Ingrese el número del pokemon que desee o \"0\" si desea salir: ");
        scanf(" %lu", &j);
    }
    if(j == 0) return;
    while(j > lista_elementos(personaje->pokemon_obtenidos) || !cambio_valido(personaje->pokemon_para_combatir, lista_elemento_en_posicion(personaje->pokemon_obtenidos, j-1))){
        if(j > lista_elementos(personaje->pokemon_obtenidos))
            printf("El número ingresado no es válido. Ingrese el número del pokemon que desee o \"0\" si desea salir: ");
        if(!cambio_valido(personaje->pokemon_para_combatir, (pokemon_t*)lista_elemento_en_posicion(personaje->pokemon_obtenidos, j-1)))
            printf("El pokemon elegido ya se encuentra para combatir. Ingrese el número del pokemon que desee o \"0\" si desea salir: ");
        scanf(" %lu", &j);
    }
    if(j == 0) return;
    lista_borrar_de_posicion(personaje->pokemon_para_combatir, i-1);
    lista_insertar_en_posicion(personaje->pokemon_para_combatir, lista_elemento_en_posicion(personaje->pokemon_obtenidos, j-1), i-1);
    cambiar_pokemon(personaje);
}

void gimnasio_mostrar(gimnasio_t* gimnasio){
    printf("Nombre del gimnasio: %s\n", gimnasio->nombre);
    printf("Dificultad: %i\n", gimnasio->dificultad);
    printf("ID Batalla: %i\n", gimnasio->id_puntero_funcion);
    printf("Lider: %s\n", gimnasio->lider->nombre);
    if(!lista_vacia(gimnasio->entrenadores)){
        entrenador_t* prox_entrenador = lista_ultimo(gimnasio->entrenadores);
        printf("Proximo entrenador: %s\n", prox_entrenador->nombre);
    }
}

void personaje_principal_mostrar(personaje_t* personaje){
    printf("Nombre: %s\n", personaje->nombre);
    printf("Pokemones de batalla:\n");
    lista_con_cada_elemento(personaje->pokemon_para_combatir, &mostrar_pokemon, NULL);
    printf("Pokemones obtenidos:\n");
    lista_con_cada_elemento(personaje->pokemon_obtenidos, &mostrar_pokemon, NULL);
}