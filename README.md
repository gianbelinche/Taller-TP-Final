# Taller-TP-Final
 
## Protocolo

A través de msgpack, se forma de la siguiente manera:

`uint32_t largo  ,  std::vector<uint32_t>`

- **std::vector<uint32_t>**: 
    
    `{comando, enteros necesarios para comando}`

Aclaración: Los ejemplos de tipo `{00, 123}` son siempre vectores de enteros uint32_t

### Comandos Cliente a Servidor

1. **Movimiento del personaje** (00):

   - **Cliente a Servidor**: 

       `ID + tipo de movimiento`

       Ejemplo:

       `{00, 1546, 01}` (Mover) a entidad (1546) hacia (abajo)

   - **Tipos de movimiento**: arriba (00), abajo (01), izquierda (02), derecha (03) y parar (04)

2. **Click en entidad** (01):

   - **Cliente a Servidor**:

       `ID + ID`

       Ejemplo:

       `{01, 12345, 6789}` (Click) de entidad (12345) a entidad (6789)

    - **Tipos de entidad**: Player, NPC / Mob, Drop (o Item)

3. **Click en inventario** (02):

    - **Cliente a Servidor**:

        `ID + obj / slot` <- se debe decidir si mandar qué objeto o qué slot clickeo

        Ejemplo:

        `Agregar ejemplo`

4. **Comandos** (03):

    - **Cliente a Servidor**:

        `ID + comando` <- se debe decidir si mandar qué objeto o qué slot clickeo

        Ejemplo:

        `Agregar ejemplo`

### Comandos Servidor a Cliente

1. **Movimiento del personaje** (00):

   - **Servidor a Cliente**:

       `ID + tipo de movimiento`

       Ejemplo:

       `{00, 1546, 01}` (Mover) a entidad (1546) hacia (abajo)

   - **Tipos de movimiento**: arriba (00), abajo (01), izquierda (02), derecha (03) y parar (04)

2. **Creacion de nuevo NPC/Mob** (01):

    - **Servidor a Cliente**:

       `ID + tipo de NPC/Mob + posX + posY` <- decidir si los npc los manda el servidor o el cliente sabe de antemano la info de estos

        Ejemplo:

        `{01, 98765, 00, 1523, 1968}` (Crear entidad) de ID (98765) de tipo (Araña) en pos ((1523),(1968))

    - **Tipos de NPC/Mobs**: Araña (00), Esqueleto (01), Goblin (02), Zombie (03), Banquero (04), Mercader (05), Sanadora (06)

3. **Creacion de nuevo Jugador** (02):

    - **Servidor a Cliente**:

       `ID + raza + posX + posY + vivo/muerto`

       Ejemplo:

       `{02, 456, 02, 12345, 1523, 0}` (Crear jugador) de ID (456) de raza (Enano) en pos ((12345),(1523)) en estado (vivo)

    - **Razas**: Humano (00), Elfo (01), Enano (02), Gnomo (03)

    - **Vivo/Muerto**: Vivo (00), Muerto (01) <- Muerto sería en modo fantasma

4. **Spawn de un drop** (03):

    - **Servidor a Cliente**:

       `ID + tipo de item + posX + posY`

       Ejemplo:

       `{03, 1595, 06, 1234, 4567}` (Crear drop) de ID (1234) de tipo (Baculo Engarzado) en pos ((1234),(4567))

    - **Tipos de Objetos**: Espada (00), Hacha (01), Martillo (02), Vara de Fresno (03), Flauta Elfica (04), Baculo Nudoso (05), Baculo Engarzado (06), Arco Simple (07), Arco Compuesto (08), Armadura de Cuero (09), Armadura de Placas (10), Tunica Azul (11), Capucha (12), Casco de Hierro (13), Escudo Tortuga (14), Escudo de Hierro (15), Sombrero Magico (16)