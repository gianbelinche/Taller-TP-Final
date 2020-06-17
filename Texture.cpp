#include "Texture.h"

/* CAMBIAR COMENTARIOS A ESPAÑOL O SACAR */

/* CAMBIAR CONSTANTES DE LUGAR */

Texture::Texture(SDL_Renderer *aRenderer) : renderer(aRenderer), texture(NULL),
                                            tWidth(0), tHeight(0) {}

Texture::~Texture() {
    this->free();
}

Texture::Texture(Texture&& other){
    this->texture = other.texture;
    other.texture = NULL;
    this->renderer = other.renderer;
    this->tHeight = other.tHeight;
    this->tWidth = other.tWidth;
    other.tHeight = 0;
    other.tWidth = 0;
}

Texture& Texture::operator=(Texture&& other){
    if (this == &other) {
        return *this;
    }

    this->texture = other.texture;
    other.texture = NULL;
    this->renderer = other.renderer;
    this->tHeight = other.tHeight;
    this->tWidth = other.tWidth;
    other.tHeight = 0;
    other.tWidth = 0;
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

void Texture::render(int x, int y, SDL_Rect *clip, SDL_Rect *renderQuad) {
    if (renderQuad == NULL){
        SDL_Rect render_Quad = {x, y, this->tWidth, this->tHeight};
        renderQuad = &render_Quad;
    }
    renderQuad->x = x;
    renderQuad->y = y;

    /* Uso renderizado sin rotaciones */
	SDL_RenderCopy(this->renderer, this->texture, clip, renderQuad);
}

int Texture::getWidth() {
    return this->tWidth;
}

int Texture::getHeight() {
    return this->tHeight;
}
