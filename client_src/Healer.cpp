#include "Healer.h"
#include "SpriteClipCreator.h"

Healer::Healer(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
               uint16_t posY) : NPC(renderer, anID, posX, posY) {
    image.loadFromFile(HEALER_PATH);
    height = HEALER_HEIGHT;
    width = HEALER_WIDTH;
    horClips = HEALER_HOR_SPRITES;
    vertClips = HEALER_VERT_SPRITES;
    speed = HEALER_SPEED;
    quad = {0, 0, width, height};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Healer::Healer(Healer &&other) : NPC(std::move(other)) {}

Healer& Healer::operator=(Healer&& other) {
    if (this == &other) {
        return *this;
    }

    NPC::operator=(std::move(other));

    return *this;
}

Healer::~Healer() {}
