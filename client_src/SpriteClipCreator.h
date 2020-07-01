#ifndef __SPRITE_CLIP_CREATOR_H__
#define __SPRITE_CLIP_CREATOR_H__

#include "SDL2/SDL.h"
#include <vector>

class SpriteClipCreator {
    public:
        SpriteClipCreator(uint16_t imgHeight, uint16_t imgWidth, uint16_t tileHeight,
                          uint16_t tileWidth, std::vector<SDL_Rect> &spriteClip);
        ~SpriteClipCreator();
};

#endif
