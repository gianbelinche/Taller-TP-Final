#ifndef __TEXTURE_H__
#define __TEXTURE_H__

/* CAMBIAR COMENTARIOS A ESPAÑOL O SACAR */

/* CAMBIAR CONSTANTES DE LUGAR */

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>

/*
 * Clase para texturas.
 * 
 * Se puede llamar al constructor con solo el renderer, luego, se debe 
 * construir manualmente. El Color Key por defecto es negro (0,0,0).
 * La textura NULL y los tamaños (0,0).
 * 
 * Se puede construir con el constructor completo, pasando el renderer,
 * el color RGB para el Color Key y la ruta de imagen para setear en
 * la textura.
*/
class Texture {
     private:
          SDL_Renderer *renderer;
          SDL_Texture *texture;
          // Dimension de la imagen
          int tWidth;
          int tHeight;
          // Color Key
          Uint8 keyRed;
          Uint8 keyGreen;
          Uint8 keyBlue;
          // Funcion privada para poder setear Render en MainWindow
          void setRenderer(SDL_Renderer *aRenderer);
          friend class MainWindow;
        
     public:
          Texture(SDL_Renderer *aRenderer);
          Texture(SDL_Renderer *aRenderer, Uint8 aKeyRed, Uint8 aKeyGreen,
                  Uint8 aKeyBlue, std::string path);
          ~Texture();
          void loadFromFile(std::string path);
          void free();

          //Set color modulation
          //void setColor(Uint8 red, Uint8 green, Uint8 blue);

          //Set blending
          //void setBlendMode(SDL_BlendMode blending);

          //Set alpha modulation
          //void setAlpha(Uint8 alpha);

          void setKeyColor(Uint8 red, Uint8 green, Uint8 blue);

          //Renderiza textura en el punto indicado
          void render(int x, int y, SDL_Rect *clip = NULL);
          
          int getWidth();
          int getHeight();
};

#endif
