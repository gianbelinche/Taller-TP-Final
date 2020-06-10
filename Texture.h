#ifndef __TEXTURE_H__
#define __TEXTURE_H__

/* CAMBIAR COMENTARIOS A ESPAÑOL O SACAR */

/* CAMBIAR CONSTANTES DE LUGAR */

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <SDL2/SDL_ttf.h>
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
     protected:
          SDL_Renderer *renderer;
          SDL_Texture *texture;
          // Dimension de la imagen
          int tWidth;
          int tHeight;
          // Funcion privada para poder setear Render en MainWindow
          void setRenderer(SDL_Renderer *aRenderer);
          friend class MainWindow; //AMIGOS DEL PADRE NO SON AMIGOS DEL HIJO, CAMBIAR O SACAR (pero funciona en mainwindow)
          // SE PODRIA HACER UNA CLASE MAP O BACKGROUND PARA EL MAINWINDOW
        
     public:
          Texture(SDL_Renderer *aRenderer);

          Texture(Texture &copy) = delete;

          Texture(Texture&& other);
          Texture& operator=(Texture&& other);

          ~Texture();

          void free();
          void render(int x, int y, SDL_Rect *clip, SDL_Rect* renderQuad);
          int getWidth();
          int getHeight();
};

#endif
