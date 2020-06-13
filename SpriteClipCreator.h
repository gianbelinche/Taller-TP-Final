#ifndef __SPRITE_CLIP_CREATOR_H__
#define __SPRITE_CLIP_CREATOR_H__

#include "SDL2/SDL.h"
#include <vector>

class SpriteClipCreator {
    public:
        SpriteClipCreator(int imgHeight, int imgWidth, int tileHeight,
                          int tileWidth, std::vector<SDL_Rect> &spriteClip);
        ~SpriteClipCreator();
};

#endif
