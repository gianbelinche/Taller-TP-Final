#include "Banker.h"
#include "SpriteClipCreator.h"

Banker::Banker(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
               uint16_t posY) : NPC(renderer, anID, posX, posY) {
    image.loadFromFile(BANKER_PATH);
    height = BANKER_HEIGHT;
    width = BANKER_WIDTH;
    horClips = BANKER_HOR_SPRITES;
    vertClips = BANKER_VERT_SPRITES;
    speed = BANKER_SPEED;
    quad = {0, 0, width, height};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Banker::Banker(Banker &&other) : NPC(std::move(other)) {}

Banker& Banker::operator=(Banker&& other) {
    if (this == &other) {
        return *this;
    }

    NPC::operator=(std::move(other));

    return *this;
}

Banker::~Banker() {
}
