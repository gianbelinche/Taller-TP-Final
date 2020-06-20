# Taller-TP-Final
 
## Protocolo

A través de msgpack, se forma de la siguiente manera:

`uint32_t largo  ,  std::vector<uint32_t>`

- **std::vector<uint32_t>**: 
    
    `{comando, enteros necesarios para comando}`

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

       `{00, 1546, 01}` (Mover) a entidad (1546) hacia (abajo)

   - **Tipos de movimiento**: arriba (00), abajo (01), izquierda (02), derecha (03) y parar (04)

2. **Creacion de nuevo NPC/Mob** (01):

    - **Servidor a Cliente**:

       `ID + tipo de NPC/Mob` <- decidir si los npc los manda el servidor o el cliente sabe de antemano la info de estos

3. **Creacion de nuevo Jugador** (02):

    - **Servidor a Cliente**:

       `ID + raza + posX + posY + vivo/muerto` <- En principio esto

4. **Spawn de un drop** (03):

    - **Servidor a Cliente**:

       `ID + tipo de item`