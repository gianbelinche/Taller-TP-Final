#include "Merchant.h"
#include "SpriteClipCreator.h"

Merchant::Merchant(SDL_Renderer *renderer, int anID, int posX, int posY, 
               View aView) : Entity(renderer, anID, posX, posY, aView) {
    image.loadFromFile(MERCHANT_PATH);
    height = MERCHANT_HEIGHT;
    width = MERCHANT_WIDTH;
    horClips = MERCHANT_HOR_SPRITES;
    vertClips = MERCHANT_VERT_SPRITES;
    quad = {0, 0, height, width};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Merchant::~Merchant() {}
