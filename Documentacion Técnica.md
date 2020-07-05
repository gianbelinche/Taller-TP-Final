# Documentación Técnica

## Requerimientos de software

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

- **Herramientas para compilación, desarrollo, prueba y depuración del programa**:
        - Algún compilador de C++, por ejemplo, g++.
        - Algún editor de texto o IDE, por ejemplo, Visual Studio Code.
        - ***COMPLETAR, CORREGIR***

## Descripción general

El programa consiste de dos aplicaciones, un servidor, y un cliente, cada uno de estos posee diversos modulos que interactuan entre si, a continuación se desarrollaran cada uno de estos modulos.

### Módulo WRAP_SDL

Este módulo se encarga de wrappear las funcionalidades de SDL, para ser capaz de utilizarlo sin preocuparse de su funcionamiento interno, las clases que componen este módulo son

        - Texture
        - Image
        - FilteredImage
        - Text
        - Music
        - SoundEffect
        - MusicPlayer
        - SoundEffectPlayer

La clase Texture, encapsula el renderizado de una textura, y las clases Image, FilteredImage y Text descienden de esta, ya que tienen un comportamiento similar entre si, Image corresponde a una imagen en formato png o similar, mientras que FilteredImage corresponde a una imagen png, pero con la posibilidad de que esta se transparente en relación a su entorno, por último Text encapsula un texto, que para SDL, una vez elegido el texto, funciona exactamente igual que una textura.

Luego, la clase Music y la clase SoundEffect encapsulan la reproducción de musica y Chunks (efectos de sonido), estas representan una unica musica o efecto de sonido, por otro lado, MusicPlayer y SoundEffectPlayer, funcionan como un reproductor, el al cual se le pueden agregar canciones o sonidos respectivamente, y luego elegir cual reproducir entre ellos.

### Módulo Layout

Este módulo consiste de todas las clases que intervienen en el manejo del layout, es decir, la interfaz gráfica del juego, estas clases son:

        - Layout
        - ExpBar
        - GraphicInventory
        - LayoutManager
        - MiniChat

La clase Layout posee el background de la interfaz, y se encarga de graficar todo lo relacionado con la vida, el mana, el oro y el nivel.
ExpBar, como lo indica su nombre, representa la barra de experiencia, la cuál son dos imagenes, una barra vacia y una llena, que se grafican una sobre la otra dependiendo la cantidad de experiencia que se tenga.
GraphicInventory representa el inventario, el cuál grafica los distintos objetos del inventario, y aquellos que se encuentran equipados, además es capaz de saber en que slot esta clickeando un usuario para seleccionar un item.
La clase MiniChat posee un historial de mensajes el cuál es graficado, y es capaz de, si el usuario presiona ENTER, graficar dinamicamente lo que el usuario va escribiendo, y una vez presionado ENTER nuevamente, ese mensaje se agrega al historial, por lo que se grafica junto a los demas.
Por último la clase LayoutManager, se encarga de decodificar los mensajes llegados desde el servidor, y llamar a las funciones correspondientes de las clases explicadas anteriormente.

### Módulo Login

Este módulo representa la pantalla de Login o el Launcher, consiste en las siguiente clases

        - LogIn
        - LogInController

La clase LogIn es la que implementa la pantalla de Login, utilizando la libreria QT, en esta pantalla, primero se selecciona el servidor al cual se quiere conectar, obteniendo un mensaje de error si este no es valido, una vez conectado se ingresa el usuario y contraseña,junto con el tamaño de la ventana que querra que tenga el juego, en caso de que el usuario exista y la contraseña sea incorrecta se le notificara el error, si el usuario no existe, se pasara a la pantalla de creacion de personaje, en la que se debera seleccionar la raza, la clase, luego de esto, o si el usuario ya existia y la contraseña era correcta, la aplicacion finaliza.

LogInController se encarga de inicializar el LogIn y ejecutar la Qapplication, para que la ventana pueda correr, y devuelve si hubo algun error.

Todo este sistema es independiente al resto del juego, debido a que este esta implementado con SDL, a continuacion se explicara mas en detalle la implementación del LogIn:

El LogIn consiste en dos campos en los que se puede ingresar texto, y dos botones que pueden ser pulsados, uno de ellos es el boton de EXIT, que esta conectado a la función que termina el programa, en caso de ser pulsado (o en caso de cerrar el programa con la cruz de la ventana), el programa termina, y el juego principal no es iniciado.
El otro boton depende de la etapa en al que se encuentre, en la primer etapa, es el boton de conectar y esta linkeado a la funcion connecSrv, que ejecuta la conexion al server, y si es exitosa, se llama a la funcion que conecta el boton a la función SigIn, en esta función, si el boton es pulsado, se enviara al servidor los datos del usuario y la contraseña y dependiendo de la respuesta se mostrara un error, se iniciara el juego o se pasara a la tercer pantalla.

## Programas intermedios y de prueba

Algunos programas intermedios usados fueron:

    - Un programa sencillo en el que se testeaba la persistencia, persistiendo algunos usuarios, y viendo que al volver a correr el programa, era posible despersistirlos.
    - Un programa de prueba para la configuración, donde se parseaba el archivo y se verificaba que el contenido fuera el correcto.
    - Un programa en el cual se testeo el correcto funcionamiento del Layout, generando de manera local los cambios necesarios, como la actualización del oro, vida, agregar items al inventario, escribir en el chat, etc.
    - Un servidor de prueba para testear el cliente, harcodeando los mensajes a enviar y viendo que el cliente los recibia correctamente, y además podía enviar sus mensajes al servidor.

## Código Fuente

El código fuente se encuentra en el repositorio de github

[Link al repositorio](https://github.com/gianbelinche/Taller-TP-Final)
