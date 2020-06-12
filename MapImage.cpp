#include "MapImage.h"

MapImage::MapImage(SDL_Renderer *aRenderer, std::string path, int tileHeight, int tileWidth) : Image(aRenderer, path) {
    SpriteClipCreator(this->tHeight, this->tWidth, tileHeight, tileWidth, this->spriteClips);
}

MapImage::~MapImage() {}

MapImage::MapImage(MapImage &&other) : Image(std::move(other)) {
    this->spriteClips = std::move(other.spriteClips);
}

MapImage& MapImage::operator=(MapImage&& other) {
    if (this == &other) {
        return *this;
    }

    this->spriteClips = std::move(other.spriteClips);
    Image::operator=(std::move(other));
    return *this;
}

void MapImage::renderFromTile(int index, int x, int y) {
    SDL_Rect clip = spriteClips[index];
    SDL_Rect renderQuad = {x, y, clip.w, clip.h};
    this->render(x, y, &clip, &renderQuad); 
}
