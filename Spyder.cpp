#include "Spyder.h"
#include "SpriteClipCreator.h"

Spyder::Spyder(SDL_Renderer *renderer, int anID, int posX, int posY, 
               View aView) : Entity(renderer, anID, posX, posY, aView) {
    image.loadFromFile(SPYDER_PATH);
    height = SPYDER_HEIGHT;
    width = SPYDER_WIDTH;
    horClips = SPYDER_HOR_SPRITES;
    vertClips = SPYDER_VERT_SPRITES;
    quad = {0, 0, height, width};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Spyder::~Spyder() {}
