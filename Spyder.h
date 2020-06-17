#ifndef __SPYDER_H__
#define __SPYDER_H__

#include <SDL2/SDL.h>
#include "Entity.h"

#define SPYDER_PATH "img/spyder.png"
#define SPYDER_HEIGHT 85
#define SPYDER_WIDTH 140
#define SPYDER_VERT_SPRITES 4
#define SPYDER_HOR_SPRITES 1 //cambiar
#define SPYDER_SPEED 3 //cambiar

class Spyder : public Entity {
    public:
        Spyder(SDL_Renderer *renderer, int anID, int posX, int posY, View aView);
        ~Spyder();
};

#endif
