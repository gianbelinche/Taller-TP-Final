#include "MainWindow.h"
#include "SDLError.h"
#include "MusicPlayer.h"
#include "SoundEffectPlayer.h"
#include "Layout.h"

/* CAMBIAR COMENTARIOS A ESPAÑOL O SACAR */

/* CAMBIAR CONSTANTES DE LUGAR */

/* TAMAÑO DE LA PANTALLA */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/* NOMBRE DE LA PANTALLA */
#define WINDOW_NAME "Main"

/* RUTA DEL BACKGROUND */
#define BACKGROUND_PATH "background.png"

/* FRECUENCIA DE SONIDO */
#define FRECUENCY 22050

MainWindow::MainWindow() : BGTexture(NULL) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
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

    if(Mix_OpenAudio(FRECUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0 ){ //No me acuerdo que son los otros dos numeros, despues me fijo y pongo defines
		throw SDLError("No se pudo inicializar el sonido: %S\n", Mix_GetError());
	}

    if( TTF_Init() == -1 ){
        throw SDLError("No se pudo inciliazar la Font, SDL_ttf Error: %s\n", TTF_GetError());
    }

    this->BGTexture.setRenderer(this->mainRenderer);
    //this->BGTexture.loadFromFile(BACKGROUND_PATH);
}

MainWindow::~MainWindow() {
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
	SDL_Quit();
}

void MainWindow::run() {
    //Main loop flag
    bool quit = false;
    MusicPlayer music_player;
	music_player.add(1,"music/cave.wav");
	music_player.add(2,"music/city.wav");
	music_player.add(3,"music/walk.wav");
	music_player.add(4,"music/main_menu.wav");
	SoundEffectPlayer sound_player;
	sound_player.add(1,"sound_effects/sword.wav");
	sound_player.add(2,"sound_effects/hammer.wav");
	sound_player.add(3,"sound_effects/potion.wav");
	sound_player.add(4,"sound_effects/axe.wav"); 
    Layout layout(mainRenderer);
    int gold = 0;
    layout.changeGold(gold);
    //The dot that will be moving around on the screen
    //Dot dot(this->mainRenderer); //sacar

    //The camera area
    //SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    //While application is running
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&eventHandler) != 0) {
            //User requests quit
            if (eventHandler.type == SDL_QUIT) {
                quit = true;
            }else if( eventHandler.type == SDL_KEYDOWN ){
				switch( eventHandler.key.keysym.sym ){
					case SDLK_1:
					sound_player.play(1);
					break;
					case SDLK_2:
					sound_player.play(2);
					break;
					case SDLK_3:
					sound_player.play(3);
					break;
					case SDLK_4:
					sound_player.play(4);
					break;
					case SDLK_6:
					music_player.play(1);
					break;
					case SDLK_7:
					music_player.play(2);
					break;
					case SDLK_8:
					music_player.play(3);
					break;
					case SDLK_9:
					music_player.play(4);
					break;
					case SDLK_0:
					music_player.stop();
					break;
				}
			}

            //Handle input for the dot
            //dot.handleEvent(eventHandler);
        }

        //Move the dot
        //dot.move();

        //Center the camera over the dot
        //camera.x = (dot.getPosX() + Dot::DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
        //camera.y = (dot.getPosY() + Dot::DOT_HEIGHT / 2) - SCREEN_HEIGHT / 2;

        //Keep the camera in bounds
        //if (camera.x < 0) {
        //    camera.x = 0;
        //}
        //if (camera.y < 0) {
        //    camera.y = 0;
        //}
        //if (camera.x > LEVEL_WIDTH - camera.w) {
         //   camera.x = LEVEL_WIDTH - camera.w;
        //}
        //if (camera.y > LEVEL_HEIGHT - camera.h) {
         //   camera.y = LEVEL_HEIGHT - camera.h;
        //}

        //Clear screen
        SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mainRenderer);

        //Render background
        //this->BGTexture.render(0, 0);
        //text.render(text.getWidth()/2,text.getHeight()/2);
        layout.render(SCREEN_WIDTH,SCREEN_HEIGHT);
        gold++;
        layout.changeGold(gold);
        

        //Render objects
        //dot.render(camera.x, camera.y);

        //Update screen
        SDL_RenderPresent(mainRenderer);
    }
}
