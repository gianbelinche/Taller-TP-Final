# Manual de Usuario

## Instalación

### Requerimientos de Software

- **OS requerido**: 
        - Linux
        - ***MacOS??***
        - ***Windows??***

- **Bibliotecas requeridas**:
        - jsoncpp: https://github.com/open-source-parsers/jsoncpp
        - msgpack: https://github.com/msgpack/msgpack-c/tree/cpp_master
        - SDL2: ***COMPLETAR***
        - QT: ***COMPLETAR***
        - ***COMPLETAR***

- **Herramientas para la instalación del programa**:
        - ***CMake??***
        - ***Makefile?***

### Requerimientos de Hardware

El programa fue probado con las siguientes tres especificaciones de hardware:

1. Primera computadora:

    - Procesador AMD 10-7850K
    - 16 GB de RAM
    - Placa de Video Radeon R9 380

2. Segunda computadora:

    - Procesador Intel i7 8700
    - 16 GB de RAM
    - Placa de Video GTX 1080Ti

2. Tercera computadora:

    - ***COMPLETAR***
    - ***COMPLETAR***
    - ***COMPLETAR***

Se asegura que el programa funcionará en sistemas con especificaciones similares o superiores.

### Proceso de instalación

***COMPLETAR***

## Configuración

Se provee un archivo de configuración en formato JSON, el cual contiene todas las variables que pueden ser modificadas para cambiar el comportamiento del programa.

Las distintas variables configurables son:
    - Frames por segundo
    - Puerto del servidor
    - Datos iniciales del jugador
    - Vida, daño y nivel de los enemigos
    - Distintos factores de las razas y clases
    - Caracteristicas de los objetos, como daño, defensa o rango

Para la resolución de la ventana, se provee una selección de resoluciones al momento del login.

## Forma de uso

En caso de que ningun server se encuentre abierto, se debe iniciar un server.

Para la conexión del cliente se debe iniciar el programa y en la pantalla que aparece ingresar el host y puerto para conectarse a un servidor, en caso de que el servidor ingresado no exista o halla algún otro tipo de error, se mostrará por pantalla y deberá volver a intentarse conectar.

Una vez conectado, se le pedirá el ingreso de un usuario y contraseña, en caso de que sea la primera vez que ingresa, se creará un nuevo usuario junto a la contraseña ingresada, siempre que no exista un usuario con el mismo nombre, en caso de que no sea la primera vez que se conecta, ingresará su usuario y contraseña y si esta es correcta, podrá iniciar el juego, en caso contrario, se le notificará del error.

Si es la primera vez que entra al juego, aparecera una pantalla de creación de personaje, donde tendrá un menu desplegable desde el que podrá elegir su raza y su clase.

Una vez iniciado el juego, se podrá observar el personaje, el cuál puede moverse con las teclas WASD, además se puede observar un layout, en el que se muestra la cantidad de oro, vida, mana y nivel actuales, junto con una barra que representa la experiencia y se ira llenando a medida que se obtiene, además se puede observar unos slots que corresponden al inventario, y a medida que consigan objetos se iran llenando, el inventario puede ser clickeado para seleccionar un objeto, también hay 4 slots especiales en donde figuraran los objetos equipados actualmente, por ultimo se encuentra una ventana de chat, en la que apretando ENTER podrá empezar a escribir, y apretando ENTER nuevamente, enviará el mensaje.

## Apéndice de errores

***COMPLETAR***