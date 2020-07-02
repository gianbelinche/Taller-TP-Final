#include "Goblin.h"
#include "SpriteClipCreator.h"

Goblin::Goblin(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
               uint16_t posY) : NPC(renderer, anID, posX, posY) {
    image.loadFromFile(GOBLIN_PATH);
    height = GOBLIN_HEIGHT;
    width = GOBLIN_WIDTH;
    horClips = GOBLIN_HOR_SPRITES;
    vertClips = GOBLIN_VERT_SPRITES;
    speed = GOBLIN_SPEED;
    quad = {0, 0, width, height};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Goblin::Goblin(Goblin &&other) : NPC(std::move(other)) {}

Goblin& Goblin::operator=(Goblin&& other) {
    if (this == &other) {
        return *this;
    }

    NPC::operator=(std::move(other));

    return *this;
}

Goblin::~Goblin() {}
