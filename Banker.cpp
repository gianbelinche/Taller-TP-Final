#include "Banker.h"
#include "SpriteClipCreator.h"

Banker::Banker(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, uint16_t posY, 
               View aView) : NPC(renderer, anID, posX, posY, aView) {
    image.loadFromFile(BANKER_PATH);
    height = BANKER_HEIGHT;
    width = BANKER_WIDTH;
    horClips = BANKER_HOR_SPRITES;
    vertClips = BANKER_VERT_SPRITES;
    quad = {0, 0, width, height};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Banker::~Banker() {
}
