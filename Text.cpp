#include "Text.h"

//Text::Text(SDL_Renderer *aRenderer) : Texture(aRenderer) {}

Text::Text(SDL_Renderer *aRenderer, Uint8 aRed, Uint8 aGreen, Uint8 aBlue/*, 
std::string text,TTF_Font* gFont*/) : Texture(aRenderer), red(aRed), 
                                        green(aGreen), blue(aBlue) {
        //this->loadText(text,gFont);
}        

Text::Text(Text&& other) : Texture(std::move(other)) {}

Text& Text::operator=(Text&& other) {
    if (this == &other) {
        return *this;
    }

    Texture::operator=(std::move(other));
    return *this;
}

void Text::loadText(std::string &text,TTF_Font* gFont){
    this->free();

    SDL_Texture *newTexture = NULL;
    //TTF_Font *gFont = TTF_OpenFont("Fonts/OpenSans.ttf", size);
    SDL_Color textColor = {red, green, blue};

    SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, text.c_str(), textColor);
    if (textSurface == NULL) {
        throw SDLError("Error: No se pudo renderizar texto. SDL_ttf_Error: %s",
                        TTF_GetError());
    } else {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(this->renderer, textSurface);
        if (newTexture == NULL) {
            throw SDLError("Error: No se pudo crear textura desde texto renderizado. SDL_ttf_Error: %s",
                        SDL_GetError());
        } else {
            this->tWidth = textSurface->w;
            this->tHeight = textSurface->h;
        }

        //Libero superficie creada
        SDL_FreeSurface(textSurface);
    }

    this->texture = newTexture;
}