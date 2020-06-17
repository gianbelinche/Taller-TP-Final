#include "SpriteClipCreator.h"

SpriteClipCreator::SpriteClipCreator(int imgHeight, int imgWidth, 
                                     int tileHeight, int tileWidth, 
                                     std::vector<SDL_Rect> &spriteClip) {
    int files = imgHeight / tileHeight;
    int columns = imgWidth / tileWidth;

    for (int i = 0; i < files; i++) {
        for (int j = 0; j < columns; j++) {
            spriteClip.emplace_back(SDL_Rect{j*tileWidth, i*tileHeight, 
                                             tileWidth, tileHeight});
        }
    }
}

SpriteClipCreator::~SpriteClipCreator() {}
