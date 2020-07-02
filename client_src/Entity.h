#ifndef __ENTITY_H__
#define __ENTITY_H__ 

enum View {UP, DOWN, LEFT, RIGHT};

enum MovementType {MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, STOP};

#include <vector>

#include "FilteredImage.h"
#include "Camera.h"
#include "Equippable.h"

class Entity {
    protected:
        uint32_t ID;
        uint16_t posX;
        uint16_t posY;

    public:
        Entity(uint32_t anID, uint16_t aPosX, uint16_t aPosY);
        ~Entity();

        Entity(const Entity &copy) = delete;
        Entity(Entity&& other);
        Entity& operator=(Entity&& other);

        virtual void refreshPosition(MovementType move) = 0;
        virtual void render(Camera &camera) = 0;
        virtual bool collision(uint16_t x, uint16_t y) = 0;
        virtual void changeState(uint8_t aState) = 0;
        virtual void changeEquipment(EquipType equipType, uint8_t what) = 0;

        uint32_t getID();
        uint16_t getPosX();
        uint16_t getPosY();
};

#endif
