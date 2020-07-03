#ifndef __SPRITE_CLIP_CREATOR_H__
#define __SPRITE_CLIP_CREATOR_H__

#include "SDL2/SDL.h"
#include <vector>

/*
 * Functor utilizado para generar Sprite Clips a partir del
 * tamaño y ancho de las imagenes y de los tiles deseados.
*/
class SpriteClipCreator {
    public:
        SpriteClipCreator(uint16_t imgHeight, uint16_t imgWidth, uint16_t tileHeight,
                          uint16_t tileWidth, std::vector<SDL_Rect> &spriteClip);
        ~SpriteClipCreator();

        SpriteClipCreator(const SpriteClipCreator &copy) = delete;
        SpriteClipCreator(SpriteClipCreator&& other) = delete;
};

#endif
