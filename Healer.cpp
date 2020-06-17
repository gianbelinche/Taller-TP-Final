#include "Healer.h"
#include "SpriteClipCreator.h"

Healer::Healer(SDL_Renderer *renderer, int anID, int posX, int posY, 
               View aView) : Entity(renderer, anID, posX, posY, aView) {
    image.loadFromFile(HEALER_PATH);
    height = HEALER_HEIGHT;
    width = HEALER_WIDTH;
    horClips = HEALER_HOR_SPRITES;
    vertClips = HEALER_VERT_SPRITES;
    quad = {0, 0, height, width};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Healer::~Healer() {}
