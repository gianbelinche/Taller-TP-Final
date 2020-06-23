#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "SDL2/SDL_events.h"
#include "FilteredImage.h"

/* VELOCIDAD DEL JUGADOR */
#define SPEED 6

/* RUTA A LA IMAGEN DEL JUGADOR */
#define PLAYER_BODY_PATH "img/cuerpoelfo.png"
#define PLAYER_HEAD_PATH "img/cabezaelfo.png"

/* MEDIDAS DEL JUGADOR */
#define BODY_WIDTH 25
#define BODY_HEIGHT 45
#define HEAD_WIDTH 17
#define HEAD_HEIGHT 17

/* CANTIDAD DE CUADROS POR ANIMACIÓN */
#define BODY_ANIMATION_FRAMES 5
#define HEAD_ANIMATION_FRAMES 4

class Player {
    private:
        int speed;
        int posX;
        int posY;
        int bodyFrameX;
        int bodyFrameY;
        int headFrameX;
        FilteredImage bodyImage;
        FilteredImage headImage;
        SDL_Rect bodyClips[BODY_ANIMATION_FRAMES];
        SDL_Rect headClips[HEAD_ANIMATION_FRAMES];

    public:
        Player(SDL_Renderer *aRenderer);
        ~Player();

        Player(const Player &copy) = delete;
        Player(Player&& other);
        Player& operator=(Player&& other);

        void move(SDL_Event& event);
        void render(int camX, int camY);

        int getPosX();
        int getPosY();
};

#endif
