#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

/* CAMBIAR COMENTARIOS A ESPAÑOL O SACAR */

/* CAMBIAR CONSTANTES DE LUGAR */

/* TAMAÑO DE LA PANTALLA */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WINDOW_NAME "Main"

class MainWindow {
    private:
        SDL_Window* mainWindow;
        SDL_Renderer* mainRenderer;
        SDL_Event eventHandler;

    public:
        MainWindow();
        ~MainWindow();
        void loadMedia();
        void run();
};

#endif
