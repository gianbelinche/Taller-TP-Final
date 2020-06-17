#ifndef __HEALER_H__
#define __HEALER_H__

#include <SDL2/SDL.h>
#include "Entity.h"

#define HEALER_PATH "img/healer.png"
#define HEALER_HEIGHT 1 //cambiar
#define HEALER_WIDTH 1 //cambiar
#define HEALER_VERT_SPRITES 4
#define HEALER_HOR_SPRITES 1
#define HEALER_SPEED 0

class Healer : public Entity {
    public:
        Healer(SDL_Renderer *renderer, int anID, int posX, int posY, View aView);
        ~Healer();
};

#endif
