#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

class MainWindow {
    private:
        SDL_Window* mainWindow;
        SDL_Renderer* mainRenderer;
        SDL_Event eventHandler;

    public:
        MainWindow();
        ~MainWindow();
        void run();
};

#endif
