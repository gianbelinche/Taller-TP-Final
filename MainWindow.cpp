#include "MainWindow.h"

/* CAMBIAR COMENTARIOS A ESPAÑOL O SACAR */

/* CAMBIAR CONSTANTES DE LUGAR */

MainWindow::MainWindow() : mainWindow(NULL), mainRenderer(NULL) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        //printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        // throw SDLException
    } else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            // printf( "Warning: Linear texture filtering not enabled!" );
            // hacer WARNING
        }

        //Create window
        mainWindow = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (mainWindow == NULL) {
            //printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            // throw SDLException
        } else {
            //Create vsynced renderer for window
            mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (mainRenderer == NULL) {
                //printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                // throw SDLException
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    //printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    // throw SDLException
                }
            }
        }
    }
}

MainWindow::~MainWindow() {
}

void MainWindow::loadMedia() {
    //Load dot texture
    if (!gDotTexture.loadFromFile("30_scrolling/dot.bmp")) {
        printf("Failed to load dot texture!\n");
        success = false;
    }

    //Load background texture
    if (!gBGTexture.loadFromFile("30_scrolling/bg.png")) {
        printf("Failed to load background texture!\n");
        success = false;
    }
}

void MainWindow::run() {
    //Main loop flag
    bool quit = false;

    //Event handler
    

    //The dot that will be moving around on the screen
    Dot dot;

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
        gBGTexture.render(0, 0, &camera);

        //Render objects
        dot.render(camera.x, camera.y);

        //Update screen
        SDL_RenderPresent(mainRenderer);
    }
}
