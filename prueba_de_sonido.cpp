#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include "MusicPlayer.h"
#include "SoundEffectPlayer.h"
#include "SDLError.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void init(SDL_Window** gWindow){
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ){
		throw SDLError("No se pudo inicializar SDL: %S\n", SDL_GetError());
	}
	*gWindow = SDL_CreateWindow( "Prueba de sonido", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( *gWindow == NULL ){
		throw SDLError("No se pudo crear la ventana: %S\n", SDL_GetError());
	}
	if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0 ){
		throw SDLError("No se pudo inicializar el sonido: %S\n", Mix_GetError());
	}
}


void close(SDL_Window** gWindow){
	SDL_DestroyWindow( *gWindow );
	Mix_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] ){
	SDL_Window* gWindow = NULL;
	//Start up SDL and create window
	init(&gWindow);
	MusicPlayer music_player;
	music_player.add(1,"music/cave.wav");
	music_player.add(2,"music/city.wav");
	music_player.add(3,"music/walk.wav");
	music_player.add(4,"music/main_menu.wav");
	SoundEffectPlayer sound_player;
	sound_player.add(1,"sound_effects/sword.wav");
	sound_player.add(2,"sound_effects/high.wav");
	sound_player.add(3,"sound_effects/medium.wav");
	sound_player.add(4,"sound_effects/low.wav");

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			//Handle key press
			else if( e.type == SDL_KEYDOWN )
			{
				switch( e.key.keysym.sym )
				{
					//Play high sound effect
					case SDLK_1:
					sound_player.play(1);
					break;
					
					//Play medium sound effect
					case SDLK_2:
					sound_player.play(2);
					break;
					
					//Play low sound effect
					case SDLK_3:
					sound_player.play(3);
					break;
					
					//Play scratch sound effect
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
					//Stop the music
					music_player.stop();
					break;
				}
			}
		}
}

	//Free resources and close SDL
	close(&gWindow);

	return 0;
}
