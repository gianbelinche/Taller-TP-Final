#ifndef __TEXTURE_H__
#define __TEXTURE_H__

/* CAMBIAR COMENTARIOS A ESPAÑOL O SACAR */

/* CAMBIAR CONSTANTES DE LUGAR */

#include "SDL2/SDL.h"
#include <string>

#define BLACK_COLOR_KEY 0,0,0

class Texture {
   private:
		SDL_Texture* texture;

		//Dimension de la imagen
		int texWidth;
		int texHeight;
        
   public:
        Texture();
        Texture(Uint8 keyRed, Uint8 keyGreen, Uint8 keyBlue);
        ~Texture();

        //Loads image at specified path
        bool loadFromFile(std::string path);

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor(Uint8 red, Uint8 green, Uint8 blue);

        //Set blending
        void setBlendMode(SDL_BlendMode blending);

        //Set alpha modulation
        void setAlpha(Uint8 alpha);

        //Renders texture at given point
        void render( int x, int y, SDL_Rect* clip = NULL );

        int getWidth();
        int getHeight();
};

Texture::Texture() {
}

Texture::~Texture() {
}

#endif
