#include "SpriteClipCreator.h"

SpriteClipCreator::SpriteClipCreator(uint16_t imgHeight, uint16_t imgWidth, 
                                     uint16_t tileHeight, uint16_t tileWidth, 
                                     std::vector<SDL_Rect> &spriteClip) {
    uint16_t files = imgHeight / tileHeight;
    uint16_t columns = imgWidth / tileWidth;

    for (uint16_t i = 0; i < files; i++) {
        for (uint16_t j = 0; j < columns; j++) {
            spriteClip.emplace_back(SDL_Rect{j*tileWidth, i*tileHeight, 
                                             tileWidth, tileHeight});
        }
    }
}

SpriteClipCreator::~SpriteClipCreator() {}
