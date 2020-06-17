#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include <SDL2/SDL.h>
#include "Entity.h"

#define ZOMBIE_PATH "img/zombie.png"
#define ZOMBIE_HEIGHT 1 //cambiar
#define ZOMBIE_WIDTH 1 //cambiar
#define ZOMBIE_VERT_SPRITES 1 //cambiar
#define ZOMBIE_HOR_SPRITES 1 //cambiar
#define ZOMBIE_SPEED 1 //cambiar

class Zombie : public Entity {
    public:
        Zombie(SDL_Renderer *renderer, int anID, int posX, int posY, View aView);
        ~Zombie();
};

#endif
