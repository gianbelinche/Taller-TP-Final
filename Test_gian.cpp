#include "Test_gian.h"
#include "SDLError.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

/* TAMAÑO DEL NIVEL */
#define LEVEL_WIDTH 1280
#define LEVEL_HEIGHT 960

/* NOMBRE DE LA PANTALLA */
#define WINDOW_NAME "Main"

/* RUTA DEL BACKGROUND */
#define BACKGROUND_PATH "background.png"

/* FRECUENCIA DE SONIDO */
#define FRECUENCY 22050

TestGian::TestGian() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw SDLError("Error: SDL no pudo inicializarse. SDL_Error: %s", 
                       SDL_GetError());
    }

    if(TTF_Init() == -1){
        throw SDLError("No se pudo inicializar la Font. SDL_ttf Error: %s\n", 
                       TTF_GetError());
    }

    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        // printf( "Warning: Linear texture filtering not enabled!" );
    }

    this->mainWindow = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, 
                                    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
                                    SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (this->mainWindow == NULL) {
        throw SDLError("Error: no se pudo crear ventana. SDL_Error: %s",
                        SDL_GetError());
    }

    this->mainRenderer = SDL_CreateRenderer(this->mainWindow, -1, 
                        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (this->mainRenderer == NULL) {
        throw SDLError("Error: no se pudo crear render. SDL_Error: %s",
                        SDL_GetError());
    }

    SDL_SetRenderDrawColor(this->mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF); //CAMBIAR!!

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        throw SDLError("Error: SDL_image no pudo inicializarse. SDL_Error: %s",
                        SDL_GetError());
    }

    if(Mix_OpenAudio(FRECUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0 ){ //No me acuerdo que son los otros dos numeros, despues me fijo y pongo defines
		throw SDLError("No se pudo inicializar el sonido: %S\n", Mix_GetError());
	}
}

TestGian::~TestGian() {
    IMG_Quit();
    Mix_Quit();
  	TTF_Quit();
    SDL_Quit();
}

void TestGian::run() {
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&eventHandler) != 0) {
            if (eventHandler.type == SDL_QUIT) {
                quit = true;
            }



        }

        SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mainRenderer);



        SDL_RenderPresent(mainRenderer);
    }
}