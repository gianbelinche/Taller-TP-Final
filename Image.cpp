#include "Image.h"

Image::Image(SDL_Renderer *aRenderer) : Texture(aRenderer) {}

Image::Image(SDL_Renderer *aRenderer, std::string path) : Texture(aRenderer) {
    this->loadFromFile(path);             
}

Image::Image(Image&& other) : Texture(std::move(other)) {}

Image& Image::operator=(Image&& other) {
    if (this == &other) {
        return *this;
    }
  
    Texture::operator=(std::move(other));
    return *this;
}

void Image::loadFromFile(std::string path) {
    //Libero imagen anterior si la había
    this->free();

    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL) {
        throw SDLError("No se pudo cargar imagen de %s. SDL_Error: %s\n",
                           path.c_str(), SDL_GetError());
    } else {
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