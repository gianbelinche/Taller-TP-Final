#ifndef __SPRITE_CLIP_CREATOR_H__
#define __SPRITE_CLIP_CREATOR_H__

#include "SDL2/SDL.h"

class SpriteClipCreator {
    private:
        SDL_Rect spriteClip;

    public:
        SpriteClipCreator(int imgHeight, int imgWidth, int tileHeight, int tileWidth);
        ~SpriteClipCreator();
        SDL_Rect getSpriteClip();
};

#endif
