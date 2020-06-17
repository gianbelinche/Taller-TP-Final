#include "Zombie.h"
#include "SpriteClipCreator.h"

Zombie::Zombie(SDL_Renderer *renderer, int anID, int posX, int posY, 
               View aView) : Entity(renderer, anID, posX, posY, aView) {
    image.loadFromFile(ZOMBIE_PATH);
    height = ZOMBIE_HEIGHT;
    width = ZOMBIE_WIDTH;
    horClips = ZOMBIE_HOR_SPRITES;
    vertClips = ZOMBIE_VERT_SPRITES;
    quad = {0, 0, height, width};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Zombie::~Zombie() {}
