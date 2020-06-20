#ifndef __SPYDER_H__
#define __SPYDER_H__

#include <SDL2/SDL.h>
#include "NPC.h"

#define SPYDER_PATH "img/spyder.png"
#define SPYDER_HEIGHT 26
#define SPYDER_WIDTH 20
#define SPYDER_VERT_SPRITES 4
#define SPYDER_HOR_SPRITES 4
#define SPYDER_SPEED 6 //cambiar

class Spyder : public NPC {
    public:
        Spyder(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
               uint16_t posY, View aView);
        ~Spyder();
};

#endif