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
                 Uint8 aKeyBlue) : renderer(aRenderer), 
                                                     texture(NULL), 
                                                     tWidth(0),
                                                     tHeight(0),
                                                     keyRed(aKeyRed),
                                                     keyGreen(aKeyGreen), 
                                                     keyBlue(aKeyBlue) {}

Texture::~Texture() {
    this->free();
}

Texture::Texture(Texture&& other){
    this->texture = other.texture;
    other.texture = NULL;
}

Texture& Texture::operator=(Texture&& other){
    this->texture = other.texture;
    other.texture = NULL;
    this->renderer = other.renderer;
    this->tHeight = other.tHeight;
    this->tWidth = other.tWidth;
    other.tHeight = 0;
    other.tWidth = 0;
    this->keyRed = other.keyRed;
    this->keyBlue = other.keyBlue;
    this->keyGreen = other.keyGreen;
    return *this;
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

void Texture::render(int x, int y, SDL_Rect *clip,SDL_Rect *renderQuad) {
    if (renderQuad == NULL){
        SDL_Rect render_Quad = {x, y, this->tWidth, this->tHeight};
        renderQuad = & render_Quad;
    }
    renderQuad->x = x;
    renderQuad->y = y;

	/*if( clip != NULL ) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}*/

    /* Uso renderizado sin rotaciones */
	SDL_RenderCopy(this->renderer, this->texture, clip, renderQuad);
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
