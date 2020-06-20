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

5. **Mensajes que cliente debe imprimir** (05):

COMPLETAR

6. **Daño** (06):

COMPLETAR