#include "NPC.h"

#include <iostream>

NPC::NPC(SDL_Renderer *renderer, NPCType type, uint32_t anID, uint16_t aPosX, 
        uint16_t aPosY) : Entity(anID, aPosX, aPosY), image(renderer, 0, 0, 0) {
    switch (type) {
        case BANKER:
            height = BANKER_HEIGHT;
            width = BANKER_WIDTH;
            image.loadFromFile(BANKER_PATH);
            break;
        
        case HEALER:
            height = HEALER_HEIGHT;
            width = HEALER_WIDTH;
            image.loadFromFile(HEALER_PATH);
            break;

        case MERCHANT:
            height = MERCHANT_HEIGHT;
            width = MERCHANT_WIDTH;
            image.loadFromFile(MERCHANT_PATH);
            break;

        default:
            break;
    }
    
    quad = {0, 0, width, height};
    clip = {0, 0, width, height};
}

NPC::~NPC() {}

NPC::NPC(NPC&& other) : Entity(std::move(other)), image(std::move(other.image)),
                        height(other.height), width(other.width),
                        quad(other.quad) {}

NPC& NPC::operator=(NPC&& other) {
    if (this == &other) {
        return *this;
    }
    
    Entity::operator=(std::move(other));
    height = other.height;
    width = other.width;
    quad = other.quad;
    image = std::move(other.image);

    return *this;
}

void NPC::refreshPosition(MovementType move) {}

void NPC::render(Camera &camera) {
    quad.x = posX - camera.getX();
    quad.y = posY - camera.getY();

    image.render(quad.x, quad.y, &clip, &quad);
}

bool NPC::collision(uint16_t x, uint16_t y) {
    return (x > posX) && (x < posX + width) && (y > posY) && (y < posY + height);
}

void NPC::changeState(uint8_t aState) {}

void NPC::changeEquipment(EquipType equipType, uint8_t what) {}

void NPC::teleportTo(uint16_t posX, uint16_t posY) {}
