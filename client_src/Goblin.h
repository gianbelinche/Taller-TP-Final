#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include <SDL2/SDL.h>
#include "NPC.h"

#define GOBLIN_PATH "img/goblin.png"
#define GOBLIN_HEIGHT 32
#define GOBLIN_WIDTH 24
#define GOBLIN_VERT_SPRITES 4
#define GOBLIN_HOR_SPRITES 8
#define GOBLIN_SPEED 8 //cambiar

class Goblin : public NPC {
    public:
        Goblin(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
               uint16_t posY);
        ~Goblin();

        Goblin(const Goblin& copy) = delete;
        Goblin(Goblin &&other);
        Goblin& operator=(Goblin&& other);
};

#endif
