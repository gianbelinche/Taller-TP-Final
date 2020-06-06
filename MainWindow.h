#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Image.h"

/* CAMBIAR COMENTARIOS A ESPAÑOL O SACAR */

/* CAMBIAR CONSTANTES DE LUGAR */

class MainWindow {
    private:
        SDL_Window* mainWindow;
        SDL_Renderer* mainRenderer;
        SDL_Event eventHandler;
        Image BGTexture;

    public:
        MainWindow();
        ~MainWindow();
        void run();
};

#endif
