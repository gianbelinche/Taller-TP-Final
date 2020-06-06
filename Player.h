#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "SDL2/SDL_events.h"
#include "Texture.h"

/* VELOCIDAD DEL JUGADOR */
#define SPEED 6

/* RUTA A LA IMAGEN DEL JUGADOR */
#define PLAYER_PATH "13.png"

/* MEDIDAS DEL JUGADOR */
#define PLAYER_WIDTH 25
#define PLAYER_HEIGHT 47

/* CANTIDAD DE CUADROS POR ANIMACIÓN */
#define WALKING_ANIMATION_FRAMES 5

class Player {
    private:
        const int speed;
        int posX;
        int posY;
        int frameX;
        int frameY;
        Texture plTexture;
        SDL_Rect spriteClips[WALKING_ANIMATION_FRAMES];

    public:
        Player(SDL_Renderer *aRenderer);
        ~Player();
        void move(SDL_Event& event);
        void render(int camX, int camY);
        int getPosX();
        int getPosY();
};

#endif
