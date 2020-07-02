#include "Zombie.h"
#include "SpriteClipCreator.h"

Zombie::Zombie(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
               uint16_t posY) : NPC(renderer, anID, posX, posY) {
    image.loadFromFile(ZOMBIE_PATH);
    height = ZOMBIE_HEIGHT;
    width = ZOMBIE_WIDTH;
    horClips = ZOMBIE_HOR_SPRITES;
    vertClips = ZOMBIE_VERT_SPRITES;
    speed = ZOMBIE_SPEED;
    quad = {0, 0, width, height};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Zombie::Zombie(Zombie &&other) : NPC(std::move(other)) {}

Zombie& Zombie::operator=(Zombie&& other) {
    if (this == &other) {
        return *this;
    }

    NPC::operator=(std::move(other));

    return *this;
}

Zombie::~Zombie() {}
