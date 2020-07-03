#include "Merchant.h"
#include "SpriteClipCreator.h"

Merchant::Merchant(SDL_Renderer *renderer, uint32_t anID, uint16_t posX,
                   uint16_t posY) : NPC(renderer, anID, posX, posY) {
    image.loadFromFile(MERCHANT_PATH);
    height = MERCHANT_HEIGHT;
    width = MERCHANT_WIDTH;
    horClips = MERCHANT_HOR_SPRITES;
    vertClips = MERCHANT_VERT_SPRITES;
    speed = MERCHANT_SPEED;
    quad = {0, 0, width, height};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Merchant::Merchant(Merchant &&other) : NPC(std::move(other)) {}

Merchant& Merchant::operator=(Merchant&& other) {
    if (this == &other) {
        return *this;
    }

    NPC::operator=(std::move(other));

    return *this;
}

Merchant::~Merchant() {}
