#include "Goblin.h"
#include "SpriteClipCreator.h"

Goblin::Goblin(SDL_Renderer *renderer, int anID, int posX, int posY, 
               View aView) : Entity(renderer, anID, posX, posY, aView) {
    image.loadFromFile(GOBLIN_PATH);
    height = GOBLIN_HEIGHT;
    width = GOBLIN_WIDTH;
    horClips = GOBLIN_HOR_SPRITES;
    vertClips = GOBLIN_VERT_SPRITES;
    quad = {0, 0, height, width};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Goblin::~Goblin() {}
