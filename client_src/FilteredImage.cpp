#include "FilteredImage.h"
#include "SDLError.h"

FilteredImage::FilteredImage(SDL_Renderer *aRenderer, Uint8 aKeyRed, 
                             Uint8 aKeyGreen, Uint8 aKeyBlue) : 
                                                            Texture(aRenderer),
                                                            keyRed(aKeyRed),
                                                            keyGreen(aKeyGreen),
                                                            keyBlue(aKeyBlue) {}

FilteredImage::~FilteredImage() {
}

FilteredImage::FilteredImage(FilteredImage&& other) : Texture(std::move(other)) {
    this->keyRed = other.keyRed;
    this->keyGreen = other.keyGreen;
    this->keyBlue = other.keyBlue;
}

FilteredImage& FilteredImage::operator=(FilteredImage&& other) {
    if (this == &other) {
        return *this;
    }

    Texture::operator=(std::move(other));
    this->keyRed = other.keyRed;
    this->keyGreen = other.keyGreen;
    this->keyBlue = other.keyBlue;
    return *this;
}

void FilteredImage::loadFromFile(std::string path) {
    //Libero imagen anterior si la había
    this->free();

    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL) {
        throw SDLError("No se pudo cargar imagen de %s. SDL_Error: %s\n",
                           path.c_str(), SDL_GetError());
    } else {
        //Seteo color a filtrar
        SDL_SetColorKey(loadedSurface, SDL_TRUE, 
                        SDL_MapRGB(loadedSurface->format, this->keyRed, 
                                   this->keyGreen, this->keyBlue));

        //Creo textura desde la superficie cargada
        newTexture = SDL_CreateTextureFromSurface(this->renderer, loadedSurface);
        if (newTexture == NULL) {
            throw SDLError("No se pudo crear textura de %s. SDL_Error: %s\n",
                           path.c_str(), SDL_GetError());
        } else {
            this->tWidth = loadedSurface->w;
            this->tHeight = loadedSurface->h;
        }

        //Libero la superficie cargada
        SDL_FreeSurface(loadedSurface);
    }

    this->texture = newTexture;
}
