#include "Merchant.h"
#include "SpriteClipCreator.h"

Merchant::Merchant(SDL_Renderer *renderer, uint32_t anID, uint16_t posX,
                   uint16_t posY, View aView) : NPC(renderer, anID, posX, posY,
                                                    aView) {
    image.loadFromFile(MERCHANT_PATH);
    height = MERCHANT_HEIGHT;
    width = MERCHANT_WIDTH;
    horClips = MERCHANT_HOR_SPRITES;
    vertClips = MERCHANT_VERT_SPRITES;
    quad = {0, 0, width, height};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Merchant::~Merchant() {}
