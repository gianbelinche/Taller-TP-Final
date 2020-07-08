# Generar supresiones con Valgrind

Valgrind nos ayuda a encontrar errores en el uso de la memoria de nuestra aplicación. Sin embargo, cuando utilizamos bibliotecas de terceros, es muy común que estas bibliotecas tengan errores y leaks que no podemos evitar cometer. Para filtrar estos errores, utilizamos un archivo de supresiones.

Para generar un archivo de supresiones, el primer paso es crear un archivo con una aplicación lo más pequeña posible y que utilice las bibliotecas que queremos filtrar.

En el siguiente ejemplo usamos un programa minimalista de SDL2

~~~{.c}
#include "SDL.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    SDL_Quit();
    return 0;
}
~~~

Compilamos con gcc

~~~{.bash}
gcc minimal.c -lSDL2 -o minimal
~~~

## Generación de logs

Una vez compilada la aplicación, la ejecutamos con valgrind para chequear errores de memoria, y registramos la salida en un archivo.

~~~{.bash}
valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --gen-suppressions=all --log-file=minimal.log
~~~

Esto genera la salida normal de valgrind, pero le agrega una descripción de los leaks que va encontrando.

## Extracción y uso de supresiones

Usamos el script parser.py para extraer la información relevante del log:

~~~{.bash}
python3 parser.py minimal.log minimal.supp
~~~

Y ahora podemos usar este archivo minimal.supp para filtrar los leaks de las aplicaciones con bibliotecas de terceros

~~~{.bash}
valgrind --leak-check=full --show-leak-kinds=all --suppressions=minimal.supp
~~~
