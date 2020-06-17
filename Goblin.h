#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include <SDL2/SDL.h>
#include "Entity.h"

#define GOBLIN_PATH "img/goblin.png"
#define GOBLIN_HEIGHT 1 //cambiar
#define GOBLIN_WIDTH 1 //cambiar
#define GOBLIN_VERT_SPRITES 1 //cambiar
#define GOBLIN_HOR_SPRITES 1 //cambiar
#define GOBLIN_SPEED 1 //cambiar

class Goblin : public Entity {
    public:
        Goblin(SDL_Renderer *renderer, int anID, int posX, int posY, View aView);
        ~Goblin();
};

#endif
