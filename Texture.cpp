#include "Texture.h"

/* CAMBIAR COMENTARIOS A ESPAÑOL O SACAR */

/* CAMBIAR CONSTANTES DE LUGAR */

#define RBLACK 0
#define GBLACK 0
#define BBLACK 0

Texture::Texture(SDL_Renderer *aRenderer) : renderer(aRenderer), texture(NULL),
                                            tWidth(0), tHeight(0), 
                                            keyRed(RBLACK), keyGreen(GBLACK), 
                                            keyBlue(BBLACK) {}

Texture::Texture(SDL_Renderer *aRenderer, Uint8 aKeyRed, Uint8 aKeyGreen,
                 Uint8 aKeyBlue, std::string path) : renderer(aRenderer), 
                                                     texture(NULL), 
                                                     tWidth(0),
                                                     tHeight(0),
                                                     keyRed(aKeyRed),
                                                     keyGreen(aKeyGreen), 
                                                     keyBlue(aKeyBlue) {
    this->loadFromFile(path);
}

Texture::~Texture() {
    this->free();
}

void Texture::loadFromFile(std::string path) {
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

void Texture::loadText(std::string text, int size){
    this->free();

    SDL_Texture *newTexture = NULL;
    TTF_Font *gFont = TTF_OpenFont("Fonts/OpenSans.ttf", size);
    SDL_Color textColor = {keyRed, keyGreen, keyBlue};

    SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, text.c_str(), textColor);
    if( textSurface == NULL ){
        //printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        //throw Exception
    }
    else{
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(this->renderer, textSurface);
        if(newTexture == NULL){
            //printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
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

void Texture::free() {
    if(this->texture != NULL) {
		SDL_DestroyTexture(this->texture);
		this->texture = NULL;
		this->tWidth = 0;
		this->tHeight = 0;
	}
}

void Texture::setKeyColor(Uint8 red, Uint8 green, Uint8 blue) {
    this->keyRed = red;
    this->keyGreen = green;
    this->keyBlue = blue;
}

void Texture::render(int x, int y, SDL_Rect *clip) {
	SDL_Rect renderQuad = {x, y, this->tWidth, this->tHeight};

	if( clip != NULL ) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

    /* Uso renderizado sin rotaciones */
	SDL_RenderCopy(this->renderer, this->texture, clip, &renderQuad);
}

int Texture::getWidth() {
    return this->tWidth;
}

int Texture::getHeight() {
    return this->tHeight;
}

void Texture::setRenderer(SDL_Renderer *aRenderer) {
    this->renderer = aRenderer;
}
