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
        MapImage(SDL_Renderer *aRenderer, std::string path, int tileHeight, int tileWidth);
        ~MapImage();

        MapImage(const MapImage &copy) = delete;
        MapImage(MapImage&& other);
        MapImage& operator=(MapImage&& other);

        void renderFromTile(int index, int x, int y);
};

#endif
