#include "Spyder.h"
#include "SpriteClipCreator.h"

Spyder::Spyder(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
               uint16_t posY) : NPC(renderer, anID, posX, posY) {
    image.loadFromFile(SPYDER_PATH);
    height = SPYDER_HEIGHT;
    width = SPYDER_WIDTH;
    horClips = SPYDER_HOR_SPRITES;
    vertClips = SPYDER_VERT_SPRITES;
    quad = {0, 0, width, height};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Spyder::~Spyder() {}
