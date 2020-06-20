#include "Entity.h"
#include "SpriteClipCreator.h"

Entity::Entity(uint32_t anID, uint16_t aPosX, uint16_t aPosY) : ID(anID), 
                                                                posX(aPosX), 
                                                                posY(aPosY) {}

Entity::~Entity() {}

Entity::Entity(Entity&& other) : ID(other.ID), posX(other.posX), 
                                 posY(other.posY) {}

Entity& Entity::operator=(Entity&& other) {
    if (this == &other) {
        return *this;
    }

    ID = other.ID;
    posX = other.posX;
    posY = other.posY;
}

bool Entity::isDestroyed() {
    return destroyed;
}

void Entity::destroy() {
    destroyed = true;
}

uint32_t Entity::getID() {
    return ID;
}