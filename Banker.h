#ifndef __BANKER_H__
#define __BANKER_H__

#include <SDL2/SDL.h>
#include "Entity.h"

#define BANKER_PATH "img/banker.png"
#define BANKER_HEIGHT 1 //cambiar
#define BANKER_WIDTH 1 //cambiar
#define BANKER_VERT_SPRITES 4
#define BANKER_HOR_SPRITES 1
#define BANKER_SPEED 0

class Banker : public Entity {
    public:
        Banker(SDL_Renderer *renderer, int anID, int posX, int posY, View aView);
        ~Banker();
};

#endif