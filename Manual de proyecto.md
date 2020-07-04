# Manual del proyecto

Integrantes:

	- Belinche Gianluca Ernesto 102674
	
	- Botta Guido Tomas 102103
	
	- Crespo Julian  ***Completar Padron***
	
[Link al enunciado]() 	

## División de tareas

Para realizar este proyecto se dividieron las tares en tres grupos, cada uno correspondiente a un integrante.

Los grupos fueron los propuestos en el enunciado, donde el trabajo correspondiente al alumno 1 lo realizó Julian Crespo, el alumno 2 Guido Botta y el alumno 3 Gianluca Belinche.

## Evolución del proyecto

El cronograma propuesto al inicio del proyecto fue el propuesto en el enunciado, este se llevo relativamente bien con algunos cambios menores, por ejemplo, el contenido de la semana 1 y 2 del alumno 3 fue realizado en la primer semana,
el contenido de la semana 3 fue realizado durante las semanas 2 y 3, y el contenido de la semana 4 fue realizado en la semana correspondiente.

Otros casos fueron ***COMPLETAR CON CASOS DE GUIDO Y JULIAN***

## Inconvenientes encontrados

Un inconveniente que se encontró fue, una vez creado el modelo del cliente, se intentó agregar la etapa de login a este, pero por la forma en que se habia diseñado, no encajaba correctamente, generando dependencias circulares dificiles de solucionar, ya que para poder tomar eventos de sdl para el login, por la forma en que se codeo, primero habia que conectarse al servidor, pero no nos podiamos conectar al servidor hasta que el usuario no lo ingresara a travéz de la pantalla de login, por lo que no podiamos hacer que funcionase.
El problema se soluciono haciendo que la pantalla de login se implementara con QT en vez de SDL, de esa manera, se logró independizar la pantalla de login con la conexión al servidor.

Un problema encontrado al intentar realizar el login en QT, es que QT no permite el lanzamiento de excepciones, por lo que no podiamos diferenciar cuando la aplicacion de QT se cerraba porque habia terminado su ejecucion correctamente, o porque el usuario habia presionado la tecla exit o la cruz para salir del programa, el problema principal era la cruz, ya que no era posible redefinir el comportamiento de esta, se decidio usar una variable de estado, inicializada en -1, y en caso de que se saliera correctamente cambiarla a 0, de esta forma, aun no pudiendo redefinir el comportamiento de la cruz, se aseguraba que si esta era presionada, la variable valdria -1 y entonces podriamos verificar que debiamos terminar la ejecucion del programa.

## Analisis de puntos pendientes

## Herramientas

Las herramientas externas para realizar el proyecto fueron, las librerias SDL, QT, msgpack, jsoncpp, ***SHA256???***
El sistema de control de versiones usado fue git a través de github.
Se utilizaron diversos programas para la creación de los gráficos y la música del juego, entre ellos, audacity, ZapSplat (biblioteca online de sonidos) y software de corrección de color para darle variedad a los sprites.

## Conclusiones
