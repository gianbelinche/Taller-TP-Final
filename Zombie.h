#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include <SDL2/SDL.h>
#include "NPC.h"

#define ZOMBIE_PATH "img/zombie.png"
#define ZOMBIE_HEIGHT 45
#define ZOMBIE_WIDTH 25
#define ZOMBIE_VERT_SPRITES 4
#define ZOMBIE_HOR_SPRITES 5
#define ZOMBIE_SPEED 3 //cambiar

class Zombie : public NPC {
    public:
        Zombie(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
               uint16_t posY, View aView);
        ~Zombie();
};

#endif
