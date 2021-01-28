#include <string.h>
#include "pa2mm.h"
#include "gimnasio.h"

int main(){
    personaje_t* personaje = crear_personaje_principal("personajes/personaje1.txt");
    if(!personaje){
        printf("mal\n");
    }
    return 0;
}