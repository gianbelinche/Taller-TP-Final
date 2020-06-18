#include "Test_gian.h"
#include "SDLError.h"
#include "MusicPlayer.h"
#include "SoundEffectPlayer.h"
#include "Layout.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

/* TAMAÑO DEL NIVEL */
#define LEVEL_WIDTH 1280
#define LEVEL_HEIGHT 960

/* NOMBRE DE LA PANTALLA */
#define WINDOW_NAME "Main"

/* RUTA DEL BACKGROUND */
#define BACKGROUND_PATH "background.png"

/* FRECUENCIA DE SONIDO */
#define FRECUENCY 22050
#define FONT_SIZE 50

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
    GraphicInventory inventory(mainRenderer);
    ExpBar expBar(mainRenderer);
    MiniChat chat(mainRenderer);
    int gold = 0;
    int level = 0;
    int life = 1000;
    int mana = 2000;
    layout.changeGold(gold);
    layout.changeLevel(level);
    layout.changeLife(life,life);
    layout.changeMana(mana,mana);
    inventory.addImage("sword");
    inventory.addImage("axe");
    inventory.addImage("baculo nudoso");
    inventory.addImage("composed bow");
    inventory.addImage("fresno rod");
    inventory.addImage("leather armor");
    inventory.select("leather armor");
    inventory.select("sword");
    inventory.addImage("sword");
    inventory.addImage("iron helmet");
    inventory.select("iron helmet");
    inventory.addImage("iron shield");
    inventory.select("iron shield");
    int exp = 0;
    int max_exp = 100;
    expBar.changeExp(exp,max_exp);
    int items = 0;
    int removes = 0;
    int cant_items = 9;
    chat.addMessage("mensaje de largo de mas de una linea si senor");
    chat.addMessage("msj de una linea");
    chat.addMessage("msj de una linea");
    chat.addMessage("mensaje de largo de mas de una linea si senor");
    chat.addMessage("msj de una linea");
    chat.addMessage("mensaje de largo de mas de una linea si senor");
    
    bool writing = false;
    SDL_StopTextInput();

    while (!quit) {

        while (SDL_PollEvent(&eventHandler) != 0) {
            if (eventHandler.type == SDL_QUIT) {
                quit = true;
            }else if( eventHandler.type == SDL_KEYDOWN ){
                if (eventHandler.key.keysym.sym == SDLK_RETURN){
                    if (writing){
                        chat.sendMessage();
                        SDL_StopTextInput();
                    } else {
                        SDL_StartTextInput();
                    }
                    writing = !writing;
                } else if(eventHandler.key.keysym.sym == SDLK_BACKSPACE){
                    chat.deleteCharacter();
                } else if(!writing){
                    switch( eventHandler.key.keysym.sym ){
 
                        break;
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
			}else if(eventHandler.type == SDL_TEXTINPUT){
                chat.putCharacter(eventHandler.text.text);
            }
        }
        

        SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mainRenderer);

        layout.render(SCREEN_WIDTH,SCREEN_HEIGHT);
        inventory.render(SCREEN_WIDTH,SCREEN_HEIGHT);
        expBar.render(SCREEN_WIDTH,SCREEN_HEIGHT);
        chat.render(SCREEN_WIDTH,SCREEN_HEIGHT);
        gold++;
        if (life > 0) life--;
        if (mana > 0) mana--;
        layout.changeGold(gold);
        layout.changeLife(life,1000);
        layout.changeMana(mana,2000);
        items++;
        removes++;
        exp++;
        if (exp == max_exp){
            exp = 0;
            max_exp *= 2;
            level++;
        }
        expBar.changeExp(exp,max_exp);
        layout.changeLevel(level);
        if (items == 200 && cant_items < 20){
            inventory.addImage("baculo engarzado");
            items = 0;
            cant_items++;
        }
        if (removes == 500){
            inventory.removeImage("composed bow");
            inventory.select("axe");
            cant_items--;
        }
        if (removes == 1000){
            inventory.removeImage("baculo nudoso");
            cant_items--;
        }

        SDL_RenderPresent(mainRenderer);
    }
}