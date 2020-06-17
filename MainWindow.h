#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "Image.h"

class MainWindow {
    private:
        SDL_Window* mainWindow;
        SDL_Renderer* mainRenderer;
        SDL_Event eventHandler;
        SDL_Rect camera;

    public:
        MainWindow();
        ~MainWindow();
        void run();
};

#endif
