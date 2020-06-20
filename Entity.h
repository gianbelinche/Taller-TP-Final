#ifndef __ENTITY_H__
#define __ENTITY_H__ 

enum View {UP, DOWN, LEFT, RIGHT}; //chequear

enum MovementType {MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, STOP};
/* CHEQUEAR SI CAMBIAR EL VALOR O NO (por protocolo), LA IDEA DEL STOP ES PARA DECIR QUE 
DEJO DE MOVERSE Y ASI VOLVER AL FRAME 0 */

#include <vector>

#include "FilteredImage.h"
#include "Camera.h"

class Entity {
    protected:
        uint32_t ID;
        uint16_t posX;
        uint16_t posY;
        bool destroyed;

    public:
        Entity(uint32_t anID, uint16_t aPosX, uint16_t aPosY);
        ~Entity();

        Entity(const Entity &copy) = delete;
        Entity(Entity&& other);
        Entity& operator=(Entity&& other);

        virtual void refreshPosition(MovementType move) = 0;
        virtual void render(Camera &camera) = 0;
        virtual bool collision(uint16_t x, uint16_t y) = 0;

        bool isDestroyed();
        void destroy();
        uint32_t getID();
};

#endif
