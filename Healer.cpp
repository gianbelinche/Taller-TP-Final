#include "Healer.h"
#include "SpriteClipCreator.h"

Healer::Healer(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
               uint16_t posY, View aView) : NPC(renderer, anID, posX, posY, 
                                            aView) {
    image.loadFromFile(HEALER_PATH);
    height = HEALER_HEIGHT;
    width = HEALER_WIDTH;
    horClips = HEALER_HOR_SPRITES;
    vertClips = HEALER_VERT_SPRITES;
    quad = {0, 0, width, height};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Healer::~Healer() {}
