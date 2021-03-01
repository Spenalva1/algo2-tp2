Se entrega la implementacion de TP 2 "¡Una aventura Pokémon!". 

Compilacion: 
    gcc *.c -o aventura -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

Ejecucion:
    ./aventura

Ejecucion con valgrind:
    valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb
    
Ademas de los archivos necesarios para ejecutar el juego, se entregan archivos de 10 personajes principales y 10 gimnasios para utilizar. Tambien se encuentra un archivo que contiene 10 gimnasios para demostrar que los mismos pueden cargarse desde un sólo archivo.

Para realizar la implementacion del trabajo se utilizaron los siguientes structs: juego_t, personaje_t, entrenador_t, gimnasio_t, pokemon_t, heap_t y tambien se hizo uso de los tdas implementados durante el cuatri como lista_t (utilizando listas y pilas) e iterador_t.

juego_t contiene toda la informacion del juego: 
  - las 5 funciones de batalla
  - un personaje_t que representa al personaje principal
  - un heap_t minimal donde se guardan los gimnasios segun su dificultad
  - Un bool simular usado en las distintas secciones del juego para saber si se debe consultar al usuario como proceder o si se seguirá automaticamente el flujo por defecto del juego
  
personaje_t es utilizado para representar el personaje principal del juego y posee:
  - un char* como nombre
  - una lista con los pokemones obtenidos
  - otra lista donde se apunta a, como maximo, 6 pokemones de los obtenidos que son los elegidos para el combate. Durante el juego el usuario tiene la posibilidad de cambiarlos.

entrenador_t se usa para los personajes pertenecientes a los gimnasios, ya sean simples entrenadores o el lider:
  - un char* como nombre
  - una lista de pokemones para combatir

gimnasio_t representa a cada gimnasio cargado por el usuario y consta de: 
  - un char* como nombre
  - un int indicando la dificultad
  - un int indicando que funcion de pelea se utilizará 
  - un entrenador_t representando al lider del gimnasio
  - una pila que contiene a los entrenadores del gimnasio. Uso una pila debido a que el orden en el que deben pelear los entrenadores el inverso a como aparecen en el archivo del gimnasio
  
pokemon_t representa a los pokemones y posee:
  - un char* como nombre
  - un int indicando la velocidad
  - un int indicando el ataque
  - un int indicando la defensa

En el trabajo se realizo la implementacion de un heap para ser utilizado para almacenar los gimnasios cargados por el usuario. Ya que sin importar el orden en el que éste los ingrese, en el juego los gimnasios deben aparecer de menor a mayor segun su dificultad. Es por eso que, mediante una funcion comparadora, se utiliza el heap como un heap minimal.

Para las batallas entre el personaje principal y un entrenador, se utilizan los iteradores implementados en el cuatrimestre. Se crea un iterador para la listas de pokemones de batalla de cada uno. Se realiza la batalla entre dos pokemones, y se itera sobre la lista del pokemon perdedor y así sucesivamente hasta que un iterador llegue al final de su lista, lo que significara que el poseedor de dicha lista es el perdedor de la batalla. Ademas de para hacer uso de iteradores, la razon por la cual decidí utilizar listas para los conjuntos de pokemones, sobretodo para el personaje principal, es para poder insertar y eliminar de posiciones especificas a la hora de cambiar los pokemons de batlla. De esta manera se permite al usuario intercambiar cualquier pokemon de la lista por cualquier otro de los obtenidos.
  
Las funciones utilizadas pra cargar los gimnasios y el personaje principal son extensas debido a los chequeos que se realizan para validar los mismo. En el caso del gimnasiose chequea que tenga un nombre, un id de batalla entre 1 y 5 inclusive, y un numero indicando la dificultad. Luego se verifica que posea un lider y que éste tenga al menos 1 pokemon. Una vez garantizado lo anterior, el gimnasio ya es valido y luego, por cada entrenador que se encuentre, se chequea que cada, al igula que el lider, contenga al menos 1 pokemon. Por otro lado, para el personaje principal, se chequea que que este tenga un nombre y que posea al menos un pokemon.
