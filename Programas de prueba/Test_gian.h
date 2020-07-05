#ifndef __TEST_GIAN_H__
#define __TEST_GIAN_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "Image.h"

class TestGian {
    private:
        SDL_Window* mainWindow;
        SDL_Renderer* mainRenderer;
        SDL_Event eventHandler;

    public:
        TestGian();
        ~TestGian();
        void run();
};

#endif