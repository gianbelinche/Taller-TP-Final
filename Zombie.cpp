#include "Zombie.h"
#include "SpriteClipCreator.h"

Zombie::Zombie(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
               uint16_t posY, View aView) : NPC(renderer, anID, posX, posY, 
                                                aView) {
    image.loadFromFile(ZOMBIE_PATH);
    height = ZOMBIE_HEIGHT;
    width = ZOMBIE_WIDTH;
    horClips = ZOMBIE_HOR_SPRITES;
    vertClips = ZOMBIE_VERT_SPRITES;
    quad = {0, 0, width, height};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Zombie::~Zombie() {}
