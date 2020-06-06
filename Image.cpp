#include "Image.h"

Image::Image(SDL_Renderer *aRenderer) : Texture(aRenderer) {}

Image::Image(SDL_Renderer *aRenderer, Uint8 aKeyRed, Uint8 aKeyGreen,
            Uint8 aKeyBlue, std::string path) : 
            Texture(aRenderer,aKeyRed,aKeyGreen,aKeyBlue) {
    this->loadFromFile(path);             
}

void Image::loadFromFile(std::string path) {
    //Libero imagen anterior si la había
    this->free();

    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL) {
        //printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        //throw Exception
    } else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, 
                        SDL_MapRGB(loadedSurface->format, this->keyRed, 
                                   this->keyGreen, this->keyBlue));

        newTexture = SDL_CreateTextureFromSurface(this->renderer, loadedSurface);
        if (newTexture == NULL) {
            //printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            //throw Exception
        } else {
            //Get image dimensions
            this->tWidth = loadedSurface->w;
            this->tHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    this->texture = newTexture;
}