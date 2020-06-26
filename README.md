# Taller-TP-Final

## Protocolo

A través de msgpack, se forma de la siguiente manera:

`uint32_t largo  ,  std::vector<uint32_t> mensaje`

- **std::vector<uint32_t> mensaje**: 
  
    `{comando, enteros necesarios para comando}`

Aclaración: Los ejemplos de tipo `{00, 123}` son siempre vectores de enteros uint32_t

### Comandos Cliente a Servidor

0. **Movimiento del personaje** (00):

   - **Cliente a Servidor**: 

       `00 + ID + tipo de movimiento`

       Ejemplo:

       `{00, 1546, 01}` -> `Mover` a entidad `1546` hacia `abajo`

   - **Tipos de movimiento**: 
      - 00 -> Arriba
      - 01 -> Abajo
      - 02 -> Izquierda
      - 03 -> Derecha
      - 04 -> Parar

1. **Click en entidad** (01):

   - **Cliente a Servidor**:

       `01 + ID + ID`

       Ejemplo:

       `{01, 12345, 6789}` -> `Click` de entidad `12345` a entidad `6789`

    - **Tipos de entidad**: Player, NPC / Mob, Drop (o Item)

2. **Click en inventario** (02):

    - **Cliente a Servidor**:

        `02 + ID + obj / slot` <- se debe decidir si mandar qué objeto o qué slot clickeo

        Ejemplo:

        `Agregar ejemplo`

3. **Comandos** (03):

    - **Cliente a Servidor**:

        `03 + ID + comando` <- se debe decidir si mandar qué objeto o qué slot clickeo

        Ejemplo:

        `Agregar ejemplo`

### Comandos Servidor a Cliente

0. **Movimiento del personaje** (00):

   - **Servidor a Cliente**:

       `00 + ID + tipo de movimiento`

       Ejemplo:

       `{00, 1546, 01}` -> `Mover` a entidad `1546` hacia `abajo`

   - **Tipos de movimiento**: 
      - 00 -> Arriba
      - 01 -> Abajo
      - 02 -> Izquierda
      - 03 -> Derecha
      - 04 -> Parar

1. **Creacion de nuevo NPC/Mob** (01):

    - **Servidor a Cliente**:

       `01 + ID + tipo de NPC/Mob + posX + posY` <- decidir si los npc los manda el servidor o el cliente sabe de antemano la info de estos

        Ejemplo:

        `{01, 98765, 00, 1523, 1968}` -> `Crear entidad` de ID `98765` de tipo `Araña` en pos (`1523`,`1968`)

    - **Tipos de NPC/Mobs**: 
      - 00 -> Araña
      - 01 -> Esqueleto
      - 02 -> Goblin
      - 03 -> Zombie
      - 04 -> Banquero
      - 05 -> Mercader
      - 06 -> Sanadora

2. **Creacion de nuevo Jugador** (02):

    - **Servidor a Cliente**:

       `02 + ID + raza + posX + posY + estado`

       Ejemplo:

       `{02, 456, 02, 12345, 1523, 0}` -> `Crear jugador` de ID `456` de raza `Enano` en pos (`12345`,`1523`) en estado `vivo`

    - **Razas**: 
      - 00 -> Humano
      - 01 -> Elfo
      - 02 -> Enano
      - 03 -> Gnomo

    - **Estado**: 
      - 00 -> Vivo
      - 01 -> Muerto <- Muerto sería en modo fantasma

3. **Spawn de un drop** (03):

    - **Servidor a Cliente**:

       `03 + ID + tipo de item + posX + posY`

       Ejemplo:

       `{03, 1595, 06, 1234, 4567}` -> `Crear drop` de ID `1234` de tipo `Baculo Engarzado` en pos (`1234`,`4567`)

    - **Tipos de Objetos**: 
      - 00 -> Espada
      - 01 -> Hacha
      - 02 -> Martillo
      - 03 -> Vara de Fresno
      - 04 -> Flauta Elfica
      - 05 -> Baculo Nudoso
      - 06 -> Baculo Engarzado
      - 07 -> Arco Simple
      - 08 -> Arco Compuesto
      - 09 -> Armadura de Cuero
      - 10 -> Armadura de Placas
      - 11 -> Tunica Azul
      - 12 -> Capucha
      - 13 -> Casco de Hierro
      - 14 -> Escudo Tortuga
      - 15 -> Escudo de Hierro
      - 16 -> Sombrero Magico

4. **Eliminación de una entidad** (04):

    - **Servidor a Cliente**:

        `04 + ID`

        Ejemplo:

        `{04, 12345}` -> `Eliminar` la entidad de ID `12345`

        Aclaración: Si bien hay distintos llamados para crear distintos tipos de entidad, para la eliminación con uno solo alcanza. Se usa para todo tipo de entidad (jugador, mob o drop).

5. **Cambiar estado de un personaje** (05):

    - **Servidor a Cliente**:
    
        `05 + ID`

        Ejemplo:

        `{05, 123456}` -> `Murió` el jugador de ID `12345`

        Aclaración: Este llamado es para indicar que un jugador pasó a ser fantasma. Si el jugador se desconectó el llamado es el (04).

6. **Mensajes que cliente debe imprimir** (06):

    ​	Son del estilo:

    ​	`06 + codigo_mensaje_a_imprimir + ...`

    - __Daño provocado (00):__ 

      `06 + 00 + id + daño`

      Ejemplo:

      `{06, 00, 488, 25}` --> El jugador `488` provoco un daño de `25`

    - **Daño recibido (01):** 

      `06 + 01 + id + daño`

      Ejemplo:

      `{06, 01, 987, 5}` --> El jugador `987` recibió 5 de daño

    - __Evasión del contrincante (02):__

      `06 + 02 + id`

      verEjemplo:

      `{06, 02, 47}` --> Se le avisa al jugador `47` que el contrincante esquivo el ataque

    - __Evasión por parte de nuestro jugador (03):__

      `06 + 03 + id`

      Ejemplo:

      `{06, 03, 99}` --> El jugador 99 esquivo el ataque

    - __Mensajes enviados al jugador (04):__

      TBD

7. **Ganancia de experiencia(07):**

    `07 + id + cant_exp`

    Ejemplo:

    `{07, 445, 168}` --> El jugador `445` gano `168` de experiencia

    Aclaración: `cant_exp` nunca va a ser mayor que la cantidad de experiencia que le falta al jugador para subir de nivel

8. **Subida de nivel(08):**

    _Mas que nada para resetear la barrita de experiencia._

    TODO: Ver si hace falta mandar el nuevo nivel del jugador o si con solo decir que se incrementó alcanza

    `08 + id`

    Ejemplo:

    `{08, 11}` --> El jugador `11` subió de nivel

    

9. **Daño** (0X):

    TBD: Se puede hacer con el mensaje (06), del subtipo **Daño recibido(01)**

COMPLETAR