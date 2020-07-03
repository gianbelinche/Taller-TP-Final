#include "Spyder.h"
#include "SpriteClipCreator.h"

Spyder::Spyder(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
               uint16_t posY) : NPC(renderer, anID, posX, posY) {
    image.loadFromFile(SPYDER_PATH);
    height = SPYDER_HEIGHT;
    width = SPYDER_WIDTH;
    horClips = SPYDER_HOR_SPRITES;
    vertClips = SPYDER_VERT_SPRITES;
    speed = SPYDER_SPEED;
    quad = {0, 0, width, height};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Spyder::Spyder(Spyder &&other) : NPC(std::move(other)) {}

Spyder& Spyder::operator=(Spyder&& other) {
    if (this == &other) {
        return *this;
    }

    NPC::operator=(std::move(other));

    return *this;
}

Spyder::~Spyder() {}
