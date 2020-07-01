#ifndef __MAP_IMAGE_H__
#define __MAP_IMAGE_H__

#include "SpriteClipCreator.h"
#include "Image.h"
#include <SDL2/SDL.h>
#include <vector>

class MapImage : public Image {
    private:
        std::vector<SDL_Rect> spriteClips;
        
    public:
        MapImage(SDL_Renderer *aRenderer, std::string path, uint16_t tileHeight,
                 uint16_t tileWidth);
        ~MapImage();

        MapImage(const MapImage &copy) = delete;
        MapImage(MapImage&& other);
        MapImage& operator=(MapImage&& other);

        void renderFromTile(uint16_t index, int x, int y);
};

#endif
