## Protocolo

A través de msgpack, se forma de la siguiente manera:

`uint32_t largo  ,  std::vector<uint32_t> mensaje`

- **std::vector<uint32_t> mensaje**: 
  
    `{comando, enteros necesarios para comando}`

*Aclaración: Los ejemplos de tipo `{00, 123}` son siempre vectores de enteros uint32_t*

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

       `01 + ID Player + ID Entidad`

       Ejemplo:

       `{01, 12345, 6789}` -> `Click` de jugador `12345` a entidad `6789`

    - **Tipos de entidad**: Player, NPC o Mob

2. **Click en inventario** (02):

    - **Cliente a Servidor**:

        `02 + ID + SLOT` 

        Ejemplo:

        `{02,120,00}` <- El jugador 120 selecciona slot 0

3. **Comandos** (03):

    - **Cliente a Servidor**:

        `03 + ID + comando` (comando esta codificado como vector de ints)

        Ejemplo:

        `{03, 120, "/meditar"}` <- El usuario 120 escribió "/meditar" en el chat

        `{03, 120, "@Personaje2 hola como estas?"}` <- El usuario 120 escribió "@Personaje2 hola como estas?" en el chat

4. **Login** (04):

    - **Cliente a Servidor**:

      `04 + user_size + user + password` (user y password estan codificados como vectores de ints)

      Ejemplo:

      `{04, 6, matias, contraseña}` <- El usuario es matias y la contraseña contraseña.

5. **Aviso conección**:

    `5 + idUsuario`
    
    Sirve como indicativo de que el usuario se conecto, para el cliente es la forma de pedir que le manden el estado del mundo
    
    Ejemplo:
    
    `{5, 1778}` <-- El jugador con id 1778 se conecto 

6. **Creación de Personaje**:

    `6 + raza + clase`

    Ejemplo:

    `{06,00,01}` <- Se creo un personaje de raza Humano y clase Mago

    - **Razas**: 
      - 00 -> Humano
      - 01 -> Elfo
      - 02 -> Enano
      - 03 -> Gnomo

    - **Clases**:
      - 00 -> Guerrero
      - 01 -> Mago
      - 02 -> Clerigo
      - 03 -> Paladin
    


    


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

       `01 + ID + es NPC o Mob + tipo de NPC/Mob + posX + posY`

        Ejemplo:

        `{01, 98765, 01, 00, 1523, 1968}` -> `Crear entidad` de ID `98765`, `Mob` de tipo `Araña` en pos (`1523`,`1968`)

    - **Es NPC o Mob**:
      - 00 -> NPC
      - 01 -> Mob

    - **Tipos de NPC**:
      - 00 -> Banquero
      - 01 -> Sanadora
      - 02 -> Mercader

    - **Tipos de Mobs**: 
      - 00 -> Goblin
      - 01 -> Esqueleto
      - 02 -> Araña
      - 03 -> Zombie

2. **Creacion de nuevo Jugador** (02):

    - **Servidor a Cliente**:

       `02 + ID + raza + posX + posY + estado + arma + armadura + escudo + casco` (lo equipado)

       Ejemplo:

       `{02, 456, 02, 12345, 1523, 00, 02, 00, 00, 13}` -> `Crear jugador` de ID `456` de raza `Enano` en pos (`12345`,`1523`) en estado `vivo` con equipamiento: `Hacha`, `Sin Armadura`, `Sin Escudo` y `Capucha`

    - **Razas**: 
      - 00 -> Humano
      - 01 -> Elfo
      - 02 -> Enano
      - 03 -> Gnomo

    - **Estado**: 
      - 00 -> Vivo
      - 01 -> Muerto *<- Muerto sería en modo fantasma*

    - **Tipos de Equipables**: 
      - 00 -> NADA (Vacío)
      - 01 -> Espada
      - 02 -> Hacha
      - 03 -> Martillo
      - 04 -> Vara de Fresno
      - 05 -> Flauta Elfica
      - 06 -> Baculo Nudoso
      - 07 -> Baculo Engarzado
      - 08 -> Arco Simple
      - 09 -> Arco Compuesto
      - 10 -> Armadura de Cuero
      - 11 -> Armadura de Placas
      - 12 -> Tunica Azul
      - 13 -> Capucha
      - 14 -> Casco de Hierro
      - 15 -> Escudo Tortuga
      - 16 -> Escudo de Hierro
      - 17 -> Sombrero Magico

3. **Spawn de un drop** (03):

    - **Servidor a Cliente**:

       `03 + ID + tipo de item + posX + posY`

       Ejemplo:

       `{03, 1595, 06, 1234, 4567}` -> `Crear drop` de ID `1234` de tipo `Baculo Engarzado` en pos (`1234`,`4567`)

    - **Tipos de Objetos**: 
      - 01 -> Espada
      - 02 -> Hacha
      - 03 -> Martillo
      - 04 -> Vara de Fresno
      - 05 -> Flauta Elfica
      - 06 -> Baculo Nudoso
      - 07 -> Baculo Engarzado
      - 08 -> Arco Simple
      - 09 -> Arco Compuesto
      - 10 -> Armadura de Cuero
      - 11 -> Armadura de Placas
      - 12 -> Tunica Azul
      - 13 -> Capucha
      - 14 -> Casco de Hierro
      - 15 -> Escudo Tortuga
      - 16 -> Escudo de Hierro
      - 17 -> Sombrero Magico
      - 18 -> Pocion de mana
      - 19 -> Pocion de vida
      - 20 -> Oro

4. **Eliminación de una entidad** (04):

    - **Servidor a Cliente**:

        `04 + ID`

        Ejemplo:

        `{04, 12345}` -> `Eliminar` la entidad de ID `12345`

        *Aclaración: Si bien hay distintos llamados para crear distintos tipos de entidad, para la eliminación con uno solo alcanza. Se usa para todo tipo de entidad (jugador, mob o drop).*

5. **Cambiar estado de un personaje** (05):

    - **Servidor a Cliente**:
    
        `05 + ID + estado`

        Ejemplo:

        `{05, 12345, 00}` -> `Revivió` el jugador de ID `12345`

        `{05, 12345, 01}` -> `Murió` el jugador de ID `12345`

    - **Estados**:
      - 00 -> Vivo
      - 01 -> Muerto

        *Aclaración: Este llamado es para indicar que un jugador pasó a ser fantasma. Si el jugador se desconectó el llamado es el (04).*

6. **Equipar/desequipar a un personaje**

    *Aclaración: Este mensaje es para avisar que cierto personaje se equipó cierto objeto y debe ser enviado a todos los clientes conectados para poder renderizar correctamente a los jugadores*

    - **Servidor a Cliente**:

        `06 + ID + Tipo Equip + Objeto`

        Ejemplo:

        `{06, 12345, 0, 03}` -> `Se equipó` jugador de ID `12345` con un `Arma` de tipo `Martillo`

        `{06, 12345, 2, 00}` -> `Se equipó` jugador de ID `12345` con un `Escudo` de tipo `NADA (vacio)`. *Es decir, se desequipó el escudo*

    - **Tipo Equip**:
      - 00 -> Arma
      - 01 -> Armadura
      - 02 -> Escudo
      - 03 -> Casco

    - **Tipos de Objetos**: 
      - 00 -> NADA (Vacío)
      - 01 -> Espada
      - 02 -> Hacha
      - 03 -> Martillo
      - 04 -> Vara de Fresno
      - 05 -> Flauta Elfica
      - 06 -> Baculo Nudoso
      - 07 -> Baculo Engarzado
      - 08 -> Arco Simple
      - 09 -> Arco Compuesto
      - 10 -> Armadura de Cuero
      - 11 -> Armadura de Placas
      - 12 -> Tunica Azul
      - 13 -> Capucha
      - 14 -> Casco de Hierro
      - 15 -> Escudo Tortuga
      - 16 -> Escudo de Hierro
      - 17 -> Sombrero Magico

    *Aclaración: Si un jugador se desequipa cierto objeto se debe mandar este mismo mensaje con valor 00 en Objeto*

7. **Mensajes que cliente debe imprimir** (07):

    ​	Son del estilo:

    ​	`07 + codigo_mensaje_a_imprimir + ...`

    - __Daño provocado (00):__ 

      `07 + 00 + id + daño`

      Ejemplo:

      `{07, 00, 488, 25}` --> El jugador `488` provoco un daño de `25`

    - **Daño recibido (01):** 

      `07 + 01 + id + daño`

      Ejemplo:

      `{07, 01, 987, 5}` --> El jugador `987` recibió 5 de daño

    - __Curación(02)__:

      `07 + 02 + id + puntos_curacion`

      Ejemplo:

      `{07, 02, 35, 100}` --> El jugador `35` recuperó `100` puntos de vida

    - __Evasión del contrincante (03):__

      `07 + 03 + id`

      Ejemplo:

      `{07, 03, 47}` --> Se le avisa al jugador `47` que el contrincante esquivo el ataque

    - __Evasión por parte de nuestro jugador (04):__

      `07 + 04 + id`

      Ejemplo:

      `{07, 04, 99}` --> El jugador 99 esquivo el ataque

    - __Mensajes enviados al jugador (05):__

      `07 + 05 + mensaje` (mensaje codificado como vector de ints)

      Ejemplo:

      `{07,05,"El Jugador @Mariano dice: hola que tal"}` 

    - __Ganancia de experiencia(06):__

      `07 + 06 + id + cant_exp`

      Ejemplo:

      `{07, 06, 445, 168}` --> El jugador `445` gano `168` de experiencia

      Aclaración: `cant_exp` nunca va a ser mayor que la cantidad de experiencia que le falta al jugador para subir de nivel

    - __Subida de nivel(07):__

      `07 + 07 + id`

      Ejemplo:

      `{07, 07, 11}` --> El jugador `11` subió de nivel

8. **Comandos de inventario** (08):

    `08 + ID comando + SLOT/OBJ/POS`

    Ejemplo:

    `{08, 00, 00}` <- poner espada en inventario

    `{08, 01, 02}` <- sacar objeto en slot 2 del inventario

    `{08, 02, 03}` <- equipar espada

    `{08, 03, 01}` <- desequipar objeto de la posicion 1

    Posiciones:
      - 00 -> Arma
      - 01 -> Armadura
      - 02 -> Escudo
      - 03 -> Casco

    IDs:
      - 00 <- poner objeto
      - 01 <- quitar objeto de slot
      - 02 <- equipar objeto
      - 03 <- desequipar

    OBJs:
      - 01 -> Espada
      - 02 -> Hacha
      - 03 -> Martillo
      - 04 -> Vara de Fresno
      - 05 -> Flauta Elfica
      - 06 -> Baculo Nudoso
      - 07 -> Baculo Engarzado
      - 08 -> Arco Simple
      - 09 -> Arco Compuesto
      - 10 -> Armadura de Cuero
      - 11 -> Armadura de Placas
      - 12 -> Tunica Azul
      - 13 -> Capucha
      - 14 -> Casco de Hierro
      - 15 -> Escudo Tortuga
      - 16 -> Escudo de Hierro
      - 17 -> Sombrero Magico
      - 18 -> Pocion

9. **Actualizar estado**:

    `09 + ID + cantidad + cant_max(opcional)`

    - __Oro(00)__:

      `09 + 00 + oro`

      Ejemplo:

      `{09, 00, 150}` <- La cantidad de oro actual es 150

    - __Vida(01)__:

      `09 + 01 + vida + vida_max`

      Ejemplo:

      `{09, 01, 150, 300}` <- La cantidad de vida actual es 150 de 300

    - __Mana(02)__:

      `09 + 02 + mana + mana_max`

      Ejemplo:

      `{09, 02, 230, 570}` <- La cantidad de mana actual es 230 de 570

    - __Nivel(03)__:

      `09 + 03 + nivel`

      Ejemplo:

      `{09, 03, 5}` <- El nivel actual es 5

    - __Experiencia(04)__:

      `09 + 04 + experiencia + experiencia_max`

      Ejemplo:

      `{09, 04, 1020, 2500}` <- La cantidad de experiencia actual es 1020 de 2500     


10. **Login**:

    `10 + logueado`

    Ejemplo:

    `{10,0}` <- El jugador no se logueo correctamente

    `{10,1}` <- El jugador se logueo correctamente, en un usuario ya existente

    `{10,2}` <- El jugador se logue correctamente, pero el usuario es nuevo y hay que crear el personaje

11. **Ataque a un NPC para Sonido (solo a usuario atacante)**:

    `11 + ARMA EQUIPADA`

    Ejemplo:

    `{11,03}` <- El jugador ataco con Martillo

    - **Armas**:
      - 01 -> Espada
      - 02 -> Hacha
      - 03 -> Martillo
      - 04 -> Vara de Fresno
      - 05 -> Flauta Elfica
      - 06 -> Baculo Nudoso
      - 07 -> Baculo Engarzado
      - 08 -> Arco Simple
      - 09 -> Arco Compuesto

12. **Tomar una pocion**:      

    `12`

    Ejemplo:

    `{12}` <- El jugador tomo una poción 

13. **Teletransportar**:

  `13 + ID + posX + posY`

  Ejemplo:

  `{13, 20, 1200, 1350}` <- El jugador 20 se teletransporto a la posicion (1200,1350)

14. **Ataque a un NPC para animación (a todos los usuarios)**:

    - **Servidor a Cliente**:

      `14 + objeto equipado + posX + posY`

      Ejemplo:

      `{14, 03, 2500, 3000}` -> `Hubo un ataque` con arma `Martillo` en la posición `(2500, 300)`

    - **Armas**:
      - 01 -> Espada
      - 02 -> Hacha
      - 03 -> Martillo
      - 04 -> Vara de Fresno
      - 05 -> Flauta Elfica
      - 06 -> Baculo Nudoso
      - 07 -> Baculo Engarzado
      - 08 -> Arco Simple
      - 09 -> Arco Compuesto