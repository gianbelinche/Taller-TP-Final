#include "Goblin.h"
#include "SpriteClipCreator.h"

Goblin::Goblin(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
               uint16_t posY, View aView) : NPC(renderer, anID, posX, posY, 
                                                aView) {
    image.loadFromFile(GOBLIN_PATH);
    height = GOBLIN_HEIGHT;
    width = GOBLIN_WIDTH;
    horClips = GOBLIN_HOR_SPRITES;
    vertClips = GOBLIN_VERT_SPRITES;
    quad = {0, 0, width, height};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Goblin::~Goblin() {}
