# Manual del proyecto

## Integrantes

|           Nombre           | Padrón |
|:--------------------------:|:------:|
| Belinche, Gianluca Ernesto | 102674 |
|     Botta, Guido Tomas     | 102103 |
|       Crespo, Julian       | 100490 |

[Link al enunciado](https://github.com/gianbelinche/Taller-TP-Final/blob/master/documentacion/2020.01.ejercicio.final.Argentum.pdf)

## División de tareas

Para realizar este proyecto se dividieron las tares en tres partes, cada una correspondiente a un integrante:

Estas tres partes se dividen en:

1. **Servidor**: Manejo de lógica del juego, carga de datos y comunicación con múltiples clientes en simultáneo. Fue realizada por Julian Crespo.

2. **Cliente 1**: Manejo de la parte gráfica, diseño del mapa, drops, interacción por parte del usuario y comunicación con servidor. Fue realizada por Guido Botta.

3. **Cliente 2**: Manejo del sonido, interfaz gráfica (inventario, chat, barra de vida, etc), pantalla de login, persistencia, configuración, interacción del usuario y comunicación con servidor. Fue realizada por Gianluca Belinche.

## Evolución del proyecto

### Semanas 1-3

El cronograma propuesto en el enunciado fue llevado a cabo con pocos cambios menores. Por ejemplo, por parte del alumno 3, las semanas 1 y 2 fueron realizadas en la semana 1, mientras que la semana 3 fue realizada entre las semanas 2 y 3. 

Estas situaciones sucedieron de forma similar en todas las partes, pero no son considerablemente diferentes como para ser mencionadas.

### Semana 4

En la semana 4 se terminó la mayor parte del cliente, incluida la pantalla de login, y se empezó a combinar las partes 2 y 3 orientadas al cliente.

### Semana 5

En la semana 5 se cambió la pantalla de login, escrita en SDL, por otra escrita en qt, para poder hacerla más amigable al usuario.

Además, se empezaron a probar servidor y clientes juntos para, al terminar la semana, poder tener el juego completo.

### Semanas 6 y 7

En estas últimas semanas se completaron ciertas funcionalidades que faltaban y se realizaron las correcciones realizadas por los correctores. Además, se agregaron algunas funcionalidades extras como animaciones en los ataques, la posibilidad de recoger y equipar items con doble click, entre otras.

## Inconvenientes encontrados

- Un inconveniente que se encontró fue, una vez creado el modelo del cliente, se intentó agregar la etapa de login a este, pero por la forma en que se habia diseñado, no encajaba correctamente, generando dependencias circulares dificiles de solucionar, ya que para poder tomar eventos de sdl para el login, por la forma en que se codeo, primero habia que conectarse al servidor, pero no nos podiamos conectar al servidor hasta que el usuario no lo ingresara a travéz de la pantalla de login, por lo que no podiamos hacer que funcionase. El problema se soluciono haciendo que la pantalla de login se implementara con QT en vez de SDL, de esa manera, se logró independizar la pantalla de login con la conexión al servidor.

- Un problema encontrado al intentar realizar el login en QT, es que QT no permite el lanzamiento de excepciones, por lo que no podiamos diferenciar cuando la aplicacion de QT se cerraba porque habia terminado su ejecucion correctamente, o porque el usuario habia presionado la tecla exit o la cruz para salir del programa, el problema principal era la cruz, ya que no era posible redefinir el comportamiento de esta, se decidio usar una variable de estado, inicializada en -1, y en caso de que se saliera correctamente cambiarla a 0, de esta forma, aun no pudiendo redefinir el comportamiento de la cruz, se aseguraba que si esta era presionada, la variable valdria -1 y entonces podriamos verificar que debiamos terminar la ejecucion del programa.

- Una vez unidos el servidor y el cliente, se fueron encontrando diversos errores, entre ellos:

  - Al principio si un cliente se desconectaba, el servidor se cerraba abruptamente. Esto logro solucionarse al avanzar el servidor.

  - Una vez solucionado el error anterior, ocurria que si luego de conectarse varios clientes, todos se desconectaban, si se queria conectar un nuevo cliente, el servidor se cerraba.

  - Una vez solucionados estos ultimos, tambien llegaba a suceder, en muy contadas ocaciones, que un cliente se desconectara subitamente.

- Otro error encontrado, fue que si habia varios clientes conectados, solo se visualizaban los objetos equipados del jugador, pero no los de los demas, es decir, los otros jugadores se veian "desnudos"

- Otro de los problemas fue el de renderizar correctamente a cada entidad con respecto a la posición sobre el eje Y. Se necesitaba que se renderice de menor a mayor sobre el eje Y para que no se vieran superpuestos de forma incorrecta. Para esto se planteó primero realizar un `map` ordenado que tuviera de clave a la `posY`, pero el problema era que se pisaban las entidades que compartieran el mismo valor sobre ese eje. Por lo que se decidió armar un `vector` con todas las entidades y ordenarla con un `sort`, pasandole como argumento una función `comp` que indicase qué valor de `posY` de una cierta entidad era el menor.

## Analisis de puntos pendientes

En la pestaña Projects del repositorio de Github se encuentra una lista con las tareas pendientes, las tareas en proceso, y las completadas.

## Herramientas

- **Librerías externas:** Las librerías utilizadas para realizar el proyecto fueron: SDL, QT, msgpack, jsoncpp, SHA256

- **Sistema de Control de Versiones**: El sistema de control de versiones usado fue git a través de GitHub.

- **Gráficos y Sonido**: Se utilizaron diversos programas para la creación de los gráficos y la música del juego, entre ellos, Audacity, ZapSplat (biblioteca online de sonidos) y software de corrección de color para darle variedad a los sprites. Además, se utilizó tiled para la creación del mapa y Photoshop para la edición de ciertos sprites. También utilizamos QT Creator para facilitar la creación de la pantalla de login.

## Conclusiones

Se logró la aplicación de conocimientos obtenidos a lo largo del curso:

- Se realizó la creación de una aplicación cliente y una servidor, utilizando los conocimientos de sockets para conectarlos.
- En ambas aplicaciones se utilizaron hilos para realizar distintas tareas en simultáneo y para la comunicación de distintos clientes a un mismo servidor.
- Se utilizó el patrón de diseño RAII en las distintas clases utilizadas.
- Se utilizaron distintas herramientas de trabajo como Git, Github, CMake, entre otras.
- Se utilizaron librerías externas como msgpack y jsoncpp para realizar tareas complejas que hubiesen demandado mucho más tiempo.

Además, la aplicación realizada está abierta a incluir distintas funcionalidades extra como añadir la posibilidad de desequiparse objetos o que los objetos dropeados despawneen después de cierto tiempo, y también a incluir fúturas mejoras como la de balancear fácilmente el juego a través de cambiar variables en el `gameConfig.json` o mejorar los sprites cambiando las imagenes.

También se solucionaron los distintos inconvenientes mencionados en la sección de `Inconvenientes encontrados`, aunque toda aplicación requiere siempre de mejoras y solución de bugs.