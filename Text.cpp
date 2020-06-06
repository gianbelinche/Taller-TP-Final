#include "Text.h"

Text::Text(SDL_Renderer *aRenderer) : Texture(aRenderer) {}

Text::Text(SDL_Renderer *aRenderer, Uint8 aKeyRed, Uint8 aKeyGreen,
Uint8 aKeyBlue, std::string text,int size) : 
        Texture(aRenderer,aKeyRed,aKeyGreen,aKeyBlue){
        this->loadText(text,size);
}        

Text::Text(Text&& other) : Texture(std::move(other)) {}

Text& Text::operator=(Text&& other) {
    Texture::operator=(std::move(other));
    return *this;
}


void Text::loadText(std::string text,int size){
    this->free();

    SDL_Texture *newTexture = NULL;
    TTF_Font *gFont = TTF_OpenFont("Fonts/OpenSans.ttf", size);
    SDL_Color textColor = {keyRed, keyGreen, keyBlue};

    SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, text.c_str(), textColor);
    if( textSurface == NULL ){
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        //throw Exception
    }
    else{
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(this->renderer, textSurface);
        if(newTexture == NULL){
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
            //throw Exception
        }
        else{
            //Get image dimensions
            this->tWidth = textSurface->w;
            this->tHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    this->texture = newTexture;
}