#include "MainWindow.h"
#include "SDLError.h"

/* CAMBIAR COMENTARIOS A ESPAÑOL O SACAR */

/* CAMBIAR CONSTANTES DE LUGAR */

/* TAMAÑO DE LA PANTALLA */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/* NOMBRE DE LA PANTALLA */
#define WINDOW_NAME "Main"

/* RUTA DEL BACKGROUND */
#define BACKGROUND_PATH "background.png"

MainWindow::MainWindow() : BGTexture(NULL) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDLError("Error: SDL no pudo inicializarse. SDL_Error: %s", 
                       SDL_GetError());
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

    this->BGTexture.setRenderer(this->mainRenderer);
    this->BGTexture.loadFromFile(BACKGROUND_PATH);
}

MainWindow::~MainWindow() {
    IMG_Quit();
	SDL_Quit();
}

void MainWindow::run() {
    //Main loop flag
    bool quit = false;

    //The dot that will be moving around on the screen
    Dot dot(this->mainRenderer); //sacar

    //The camera area
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    //While application is running
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&eventHandler) != 0) {
            //User requests quit
            if (eventHandler.type == SDL_QUIT) {
                quit = true;
            }

            //Handle input for the dot
            dot.handleEvent(eventHandler);
        }

        //Move the dot
        dot.move();

        //Center the camera over the dot
        camera.x = (dot.getPosX() + Dot::DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
        camera.y = (dot.getPosY() + Dot::DOT_HEIGHT / 2) - SCREEN_HEIGHT / 2;

        //Keep the camera in bounds
        if (camera.x < 0) {
            camera.x = 0;
        }
        if (camera.y < 0) {
            camera.y = 0;
        }
        if (camera.x > LEVEL_WIDTH - camera.w) {
            camera.x = LEVEL_WIDTH - camera.w;
        }
        if (camera.y > LEVEL_HEIGHT - camera.h) {
            camera.y = LEVEL_HEIGHT - camera.h;
        }

        //Clear screen
        SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mainRenderer);

        //Render background
        this->BGTexture.render(0, 0, &camera);

        //Render objects
        dot.render(camera.x, camera.y);

        //Update screen
        SDL_RenderPresent(mainRenderer);
    }
}
